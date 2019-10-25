local Unicode_data_path = "./DerivedCoreProperties.txt"
local output_path = "./src/unicodeid.h"
local header_template_path = "./src/unicodeid_template.h"

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
	local struct_fmt = tab .. "{ " .. code_point_fmt .. ", " .. code_point_fmt .. " }"
	local arrays = setmetatable({}, { __index = table })
	
	local function make_and_print_code_point_ranges(name, ranges)
		for _, v in ipairs { "static const ", type_name, " ", name, "[] = {\n" } do
			arrays:insert(v)
		end
		local array_contents = {}
		for _, range in ipairs(ranges) do
			table.insert(array_contents, (struct_fmt):format(table.unpack(range)))
		end
		arrays:insert(table.concat(array_contents, ",\n"))
		arrays:insert("\n};\n")
	end
	
	local template_file = assert(io.open(header_template_path, "r"))
	local template = template_file:read "a"
	template_file:close()
	
	make_and_print_code_point_ranges("XID_Start", XID_Start)
	arrays:insert "\n"
	make_and_print_code_point_ranges("XID_Continue", XID_Continue)

	local header = template:gsub("__([%a_]-)__", {
		TYPE_NAME = type_name,
		UNICODE_VERSION = Unicode_version,
		ARRAYS = arrays:concat()
	})
	
	return header
end

local output = assert(io.output(output_path))
io.write(print_data())
output:close()
