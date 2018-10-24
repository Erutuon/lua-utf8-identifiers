local function assert_compile(chunk, should_compile)
	local success, val = pcall(load, chunk)
	
	if success then
		success = pcall(val)
	end
	
	if success ~= should_compile then
		local msg = (should_compile and "failed to compile" or "succeeded at compiling")
			.. " chunk"
		if not success then
			msg = msg .. " with error '" .. val .. "'"
		end
		msg = msg .. ":\n" .. tostring(chunk)
		print(msg)
	end
end

-- Hangul syllable gag (U+D573) allowed in an identifier.
assert_compile("\z
function \u{D573} (...) \
	return ... \
end \
\
\u{D573}('Hello', 'world!')", true)

-- No-break space (U+00A0) not allowed in an identifier.
assert_compile("\z
function \u{A0} (...) \
	return ... \
end \
\
\u{A0}('Hello', 'world!')", false)