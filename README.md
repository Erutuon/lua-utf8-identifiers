# lua-utf8-identifiers

This is a version of Lua that allows UTF-8 identifiers. Not all Unicode code points are allowed; the set of allowed codepoints more or less follows the rules given in [UAX #31 Unicode Identifier and Pattern Syntax](https://www.unicode.org/reports/tr31/#D1).

At the moment [tclUniData.c](https://github.com/tcltk/tcl/blob/master/generic/tclUniData.c) (based on Unicode version 11.0) is used to determine the allowed characters, but as this contains more information than is needed (letter case&ndash;related stuff), I should come up with something else.
