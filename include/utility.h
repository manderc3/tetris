#ifndef UTILITY_H
#define UTILITY_H

#include <string_view>

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
extern int get_ypos_offset(const std::string_view& t_template);

enum class Direction : std::int8_t
{
    None,
    Left,
    Right,
    Down
};

#endif
