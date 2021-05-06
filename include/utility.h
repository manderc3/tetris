#ifndef UTILITY_H
#define UTILITY_H

struct Vec
{
    constexpr Vec(int x, int y) : x(x), y(y) {};
    constexpr Vec(const Vec&) = default;
    constexpr Vec(Vec&&) = default;
    
    constexpr Vec& operator = (Vec&&) = default;
    constexpr Vec& operator = (const Vec&) = default;
    
    template<typename T>
    constexpr auto operator += (const T&& rhs) { x += rhs.x; y += rhs.y; };

    template<typename T>
    constexpr auto operator -= (const T&& rhs) { x -= rhs.x; y -= rhs.y; };

    int x, y;
};

// Based on the given tetro template, determine an offset to adjust the ypos by to ensure that the tetromino appears at the top.
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

#endif
