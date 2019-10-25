-- These are defined below.
local check_compile, make_identifier_test, check_identifier_validity

local tests = {
	-- false as second value indicates the identifier is invalid.

	-- Characters allowed in identifiers:
	-- Hangul syllables (here, Hangugeo, the name of the Korean
	-- language)
	{ "\u{D55C}\u{AD6D}\u{C5B4}", true },
	-- decomposed (NFD) version of the same
	{ "\u{1112}\u{1161}\u{11AB}\u{1100}\u{116E}\u{11A8}\u{110B}\u{1165}", true },
	
	-- Characters not allowed in identifiers at all:
	-- no-break space
	{ "\u{A0}", false },
	-- en dash, curly single and double quotation marks
	{ "\u{2013}", false },
	{ "\u{2018}", false },
	{ "\u{2019}", false },
	{ "\u{201C}", false },
	{ "\u{201D}", false },
	-- noncharacters
	{ "\u{10FFFF}", false },
	
	-- Characters only allowed after first character.
	-- combining acute accent
	{ "\u{301}", false },
	{ "a\u{301}", true },
	
	-- middle dot (U+0xB7)
	{ "·", false },
	{ "col·lecció", true },
	
	-- Invalid UTF-8
	{ "\x80", false }, -- lone continuation byte
	{ "\xC0\x80", false }, -- overlong encoding
	{ "\xE1\x80", false }, -- missing continuation byte
	
	-- bytes not used in UTF-8 at all
	{ "\xC0", false },
	{ "\xC1", false },
}

-- Add testcases for 0xF5 to 0xFF.
for i = 0x5, 0xF do
	table.insert(tests, { string.char(0xF0 + i), false })
end

local function run_tests()
	local count = setmetatable({}, {
		__index = function (self, k)
			self[k] = 0
			return 0
		end})
	
	for _, test in ipairs(tests) do
		local result = check_identifier_validity(table.unpack(test))
		count[result] = count[result] + 1
	end
	
	print(("%d success%s, %d failure%s")
		:format(count[true],  count[true] == 1  and "" or "es",
				count[false], count[false] == 1 and "" or "s"))
end

function check_compile(chunk, should_not_have_compile_error)
	local compiled, val, compile_error = pcall(load, chunk)
	
	local no_compile_error = compile_error == nil
	
	if no_compile_error ~= should_not_have_compile_error then
		local msg = (no_compile_error and "succeeded at compiling" or "failed to compile")
			.. " chunk"
		if compile_error then
			msg = msg .. " with error '" .. compile_error .. "'"
		end
		if utf8.len(chunk) then -- If valid UTF-8, escape Unicode characters.
			chunk = chunk:gsub(
				utf8.charpattern,
				function (char)
					local codepoint = utf8.codepoint(char)
					if codepoint > 0x7F then
						return ("\\u{%X}"):format(codepoint)
					end
				end)
		end
		msg = msg .. ":\n" .. tostring(chunk) .. "\n" .. debug.traceback()
		print(msg)
	end
	
	return no_compile_error == should_not_have_compile_error
end

function make_identifier_test(identifier)
	return ("%s = 1 return %s"):format(identifier, identifier)
end

function check_identifier_validity(identifier, valid)
	return check_compile(make_identifier_test(identifier), valid)
end

run_tests()

check_compile("π = math.pi φ = (1 + math.sqrt(5)) / 2", true)

return check_identifier_validity
