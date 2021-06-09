#ifndef _GLYPH_MAP_H_
#define _GLYPH_MAP_H_

#include <unordered_map>

#include "glyphs.h"

namespace Glyphs
{
    std::unordered_map<char, char*> glyph_map
    {
	{'A', _A },
	{'B', _B },
	{'C', _C },
	{'D', _D },
	{'E', _E },
	{'F', _F },
	{'G', _G },
	{'H', _H },
	{'I', _I },
	{'J', _J },
	{'K', _K },
	{'L', _L },
	{'M', _M },
	{'N', _N },
	{'O', _O },
	{'P', _P },
	{'Q', _Q },
	{'R', _R },
	{'S', _S },
	{'T', _T },
	{'U', _U },
	{'V', _V },
	{'W', _W },
	{'X', _X },
	{'Y', _Y },
	{'Z', _Z },
	{'0', _0 },
	{'1', _1 },
	{'2', _2 },
	{'3', _3 },
	{'4', _4 },
	{'5', _5 },
	{'6', _6 },
	{'7', _7 },
	{'8', _8 },
	{'9', _9 },							    
    };
}

#endif

