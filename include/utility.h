#ifndef UTILITY_H
#define UTILITY_H

struct Vec
{
    constexpr Vec(std::int8_t x, std::int8_t y) : x(x), y(y) {};
    constexpr Vec(const Vec&) = default;
    constexpr Vec(Vec&&) = default;
    
    constexpr Vec& operator = (Vec&&) = default;
    constexpr Vec& operator = (const Vec&) = default;
    
    template<typename T>
    constexpr auto operator += (const T&& rhs) { x += rhs.x; y += rhs.y; };

    template<typename T>
    constexpr auto operator -= (const T&& rhs) { x -= rhs.x; y -= rhs.y; };

    std::int8_t x, y;
};

#endif
