#include "../include/utility.h"

int get_ypos_offset(const std::string_view& t_template)
{
    auto row_empty = [&t_template] (const int row)
    {
	for (int x = 0; x < 4; x++)
	{
	    if (t_template[row * 4 + x] != ' ')
		return false;
	}

	return true;
    };

    int offset = 0;
    for(; row_empty(offset); offset++)
    {	
    }

    return offset;
}
