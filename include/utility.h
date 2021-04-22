#ifndef UTILITY_H
#define UTILITY_H

struct Vec
{
    constexpr Vec(std::int8_t x, std::int8_t y) : x(x), y(y) {};
    constexpr Vec(const Vec&) = default;
    constexpr Vec(Vec&&) = default;   

    std::int8_t x, y;
};

#endif
