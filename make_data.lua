local Unicode_data_path = "./DerivedCoreProperties.txt"
local output_path = "./src/unicodeid.h"

local function word_set(str)
	local set = {}
	for word in str:gmatch "%w+" do
		set[word] = true
	end
	return set
end

local function get_data()
	local input = assert(io.open(Unicode_data_path, "rb"))
	local data = input:read "a"
	input:close()
	
	-- Get XID_Start and XID_Continue sections of file (roughly).
	data = data:match "Derived Property: XID_Start(.-)Derived Property: Default_Ignorable_Code_Point"

	local XID_Start, XID_Continue = {}, {}
	local i, j = 0, 0

	local patt = "%f[^\r\n](%x+)%.?%.?(%x*)%s*;%s*([%a_]+)"
	local range
	for code_point1, code_point2, property in data:gmatch(patt) do
		code_point1, code_point2 = tonumber(code_point1, 16), tonumber(code_point2, 16)
		
		local curr_table
		if property == "XID_Start" then
			curr_table = XID_Start
		else
			curr_table = XID_Continue
		end
		
		assert(curr_table, "no table???")
		
		-- If the current code point adjoins the previous code point, expand the
		-- previously added code point range.
		local prev = curr_table[#curr_table]
		if prev and code_point1 - prev[2] == 1 then
			prev[2] = code_point2 or code_point1
		-- Else add a new code point range.
		else
			curr_table[#curr_table + 1] = { code_point1, code_point2 or code_point1 }
		end
	end
	
	return XID_Start, XID_Continue
end

local function print_data()
	local XID_Start, XID_Continue = get_data()
	
	-- Constants to insert into source code:
	local Unicode_version = "11.0"
	local type_name = "code_point_range"
	local tab = "  "
	local max_xdigit = 5
	local code_point_fmt = "0x%0" .. max_xdigit .. "X"
	local struct_fmt = "{ " .. code_point_fmt .. ", " .. code_point_fmt .. " }"
	
	local function make_and_print_code_point_ranges(name, ranges)
		io.write("static const ", type_name, " ", name, "[] = {\n")
		local output = {}
		for _, range in ipairs(ranges) do
			table.insert(output, tab .. (struct_fmt):format(table.unpack(range)))
		end
		io.write(table.concat(output, ",\n"), "\n};\n")
	end
	
	local prescript = ([[
/*
** Parsed from DerivedCoreProperties.txt, version Unicode_version.
** For more information, see https://www.unicode.org/reports/tr31/.
*/

/* #define CHECK_BINARY_SEARCH */
#ifdef CHECK_BINARY_SEARCH
#include <stdio.h>
#endif
#include <stddef.h> /* size_t */

#define MAXUNICODE	0x10FFFF

#define ARRAY_SIZE(array) (sizeof (array) / sizeof ((array)[0]))

#define IN_RANGES(ranges, code_point) \
	is_in_ranges(ranges, ARRAY_SIZE(ranges), (code_point))

#define IS_XID_START(code_point) \
	IN_RANGES(XID_Start, (code_point))

#define IS_XID_CONTINUE(code_point) \
	IN_RANGES(XID_Continue, (code_point))

typedef struct {
	const unsigned int low;
	const unsigned int high;
} type_name;

]]):gsub("\t", tab):gsub("type_name", type_name):gsub("Unicode_version", Unicode_version)
	io.write(prescript)
	
	make_and_print_code_point_ranges("XID_Start", XID_Start)
	io.write "\n"

	make_and_print_code_point_ranges("XID_Continue", XID_Continue)
	
	local postscript = ([[

int is_in_ranges (const code_point_range *const ranges, const size_t length,
                  const unsigned int code_point) {
	size_t low = 0, mid, high = length - 1;
	while (low <= high) {
		mid = (high + low) / 2;
#ifdef CHECK_BINARY_SEARCH
		printf("U+%04X <= U+%04X <= U+%04X? (%d, %d)\n",
			ranges[mid].low, code_point, ranges[mid].high, (int) low, (int) high);
#endif
		if (code_point < ranges[mid].low)
			high = mid - 1;
		else if (code_point <= ranges[mid].high)
			return 1;
		else
			low = mid + 1;
	}
	return 0;
}

static const char *check_utf8_identifier(const char *const ident, const size_t len) {
	size_t i;
	static const unsigned int limits[] = {0xFF, 0x7F, 0x7FF, 0xFFFF};
	for (i = 0; i < len; i++) {
		unsigned int c = ident[i];
		if (c > 0x7F) {
			/* based on utf8_decode in lutf8lib.c */
			unsigned int code_point = 0;
			int count = 0;  /* to count number of continuation bytes */
			while (c & 0x40) {  /* still have continuation bytes? */
				int cc;
				if (++count + i >= len /* have reached end of string */
						|| (cc = ident[i + count], /* read next byte */
						(cc & 0xC0) != 0x80)) { /* not a continuation byte? */
					return "missing continuation byte";
				}
				code_point = (code_point << 6) | (cc & 0x3F);  /* add lower 6 bits from cont. byte */
				c <<= 1;  /* to test next bit */
			}
			code_point |= ((c & 0x7F) << (count * 5));  /* add first byte */
			if (count > 3)
				return "too many continuation bytes";
			else if (code_point > MAXUNICODE)
				return "code point too large";
			else if (code_point <= limits[count])
				return "overlong encoding";
			else if (!(i == 0 ? IS_XID_START(code_point) : IS_XID_CONTINUE(code_point)))
				return "invalid multi-byte character in identifier";
			i += count;  /* skip continuation bytes read */
		}
	}
	return NULL;
}
]]):gsub("\t", tab)
	io.write(postscript)
end

local output = assert(io.output(output_path))
print_data()
output:close()