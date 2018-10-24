local function check_compile_error(chunk, should_not_have_compile_error)
	local compiled, val, compile_error = pcall(load, chunk)
	
	local success = compile_error == nil
	
	if success ~= should_not_have_compile_error then
		local msg = (success and "succeeded at compiling" or "failed to compile")
			.. " chunk"
		if compile_error then
			msg = msg .. " with error '" .. compile_error .. "'"
		end
		msg = msg .. ":\n" .. tostring(chunk) .. "\n" .. debug.traceback()
		print(msg)
	end
end

local function make_chunk(identifier)
	return ("\z
function %s (...) \
	return ... \
end \
\
%s('Hello', 'world!')"):format(identifier, identifier)
end

-- Hangul syllable gag (U+D573) allowed in an identifier.
check_compile_error(make_chunk "\u{D573}", true)

-- No-break space (U+00A0) not allowed in an identifier.
check_compile_error(make_chunk "\u{A0}", false)

-- Noncharacters such as U+10FFFF not allowed in identifiers.
check_compile_error(make_chunk "\u{10FFFF}", false)