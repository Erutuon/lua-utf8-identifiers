local Unicode_data_path = './UnicodeData.txt'
local output_path = './src/unicodeid.h'

local function word_set(str)
	local set = {}
	for word in str:gmatch '%w+' do
		set[word] = true
	end
	return set
end

local function get_data(code_point_limit)
	local input = assert(io.input(Unicode_data_path))
	code_point_limit = code_point_limit or 0x10FFFF

	-- https://www.unicode.org/reports/tr31/#D1
	local Id_Start_General_Categories, Id_Continue_not_Id_Start_General_Categories
		= word_set 'Lu Ll Lt Lm Lo Nl', word_set 'Mc Mn Nd Pc'

	local Id_Start, Id_Continue_not_Id_Start = {}, {}
	local i, j = 0, 0

	-- Number of fields: 15
	local patt = '([^;]*);([^;]*);([^;]*)' .. (';[^;]*'):rep(12)
	local range
	for line in io.lines() do
		local code_point, name_or_label, general_category = line:match(patt)
		if not code_point then
			print("pattern didn't match " .. tostring(line))
		end
		
		code_point = tonumber(code_point, 16)
		
		if code_point > code_point_limit then
			print(("U+%04X"):format(code_point) .. " over limit")
			break
		end
		
		local value_to_insert
		if name_or_label:sub(1, 1) == '<' and name_or_label:find ', ' then
			print(name_or_label)
			if name_or_label:find 'First' then
				range = {}
				range[1] = code_point
			elseif name_or_label:find 'Last' then
				range[2] = code_point
				value_to_insert = range
			end
		else
			value_to_insert = code_point
		end
		
		if value_to_insert then
			if Id_Start_General_Categories[general_category] then
				i = i + 1
				Id_Start[i] = value_to_insert
			elseif Id_Continue_not_Id_Start_General_Categories[general_category] then
				j = j + 1
				Id_Continue_not_Id_Start[j] = value_to_insert
			end
		end
	end
	
	input:close()
	
	return Id_Start, Id_Continue_not_Id_Start
end

local function list_to_ranges(list)
	assert(type(list) == "table")
	
	local ranges = {}
	table.sort(
		list,
		function (a, b)
			if type(a) == "table" then
				a = a[1]
			end
			if type(b) == "table" then
				b = b[1]
			end
			return a < b
		end)
	local i = 1
	local length = #list
	while i <= length do
		local first_codepoint = list[i]
		local prev = list[i]
		while true do
			i = i + 1
			if type(prev) == "table" then
				table.insert(ranges, prev)
				break
			end
			local cur = list[i]
			if cur and type(cur) ~= "table" and cur - prev == 1 then
				prev = cur
			else
				table.insert(ranges, { first_codepoint, prev })
				break
			end
		end
	end
	return ranges
end

local function print_data(code_point_limit)
	local Id_Start, Id_Continue_not_Id_Start = get_data(code_point_limit)
	local type_name = "code_point_range"
	local tab = "  "
	
	local function make_and_print_code_point_ranges(name, list)
		io.write("static const ", type_name, " ", name, "[] = {\n")
		local output = {}
		for _, range in ipairs(list_to_ranges(list)) do
			table.insert(output, tab .. ("{ 0x%04X, 0x%04X }"):format(table.unpack(range)))
		end
		io.write(table.concat(output, ",\n"), "\n};\n")
	end
	
	local prescript = ([[
/*
** based on https://www.unicode.org/reports/tr31/#D1, but Other_ID_Continue
** omitted and no Pattern_Syntax and Pattern_White_Space code points
** defined
*/

#include <stddef.h> /* size_t */

#define ARRAY_SIZE(array) (sizeof (array) / sizeof ((array)[0]))

#define ID_START(code_point) \
	is_in_ranges(Id_Start, ARRAY_SIZE(Id_Start), (code_point))

#define ID_CONTINUE_NOT_START(code_point) \
	is_in_ranges(Id_Continue_not_Id_Start, ARRAY_SIZE(Id_Continue_not_Id_Start), (code_point))

typedef struct {
	const unsigned int low;
	const unsigned int high;
} type_name;

]]):gsub('\t', tab):gsub('type_name', type_name)
	io.write(prescript)
	
	make_and_print_code_point_ranges("Id_Start", Id_Start)
	io.write "\n"

	make_and_print_code_point_ranges("Id_Continue_not_Id_Start", Id_Continue_not_Id_Start)
	
	local postscript = ([[

int is_in_ranges (const code_point_range *ranges, const size_t length,
                  const unsigned int code_point) {
	size_t low = 0, mid, high = length;
	while (low <= high) {
		mid = (high + low) / 2;
		if (code_point < ranges[mid].low)
			high = mid - 1;
		else if (code_point <= ranges[mid].high)
			return 1;
		else
			low = mid + 1;
	}
	return 0;
}]]):gsub('\t', tab)
	io.write(postscript)
end

local output = assert(io.output(output_path))
print_data()
output:close()