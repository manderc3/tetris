#include <array>
#include <iostream>
#include <random>
#include <vector>

namespace
{
    struct Vec
    {
	constexpr Vec(std::int8_t x, std::int8_t y) : x(x), y(y) {};
	constexpr Vec(const Vec&) = default;
	constexpr Vec(Vec&&) = default;   

	std::int8_t x, y;
    };

    using TetroTemplate = std::array<Vec, 4>;

    struct Tetromino
    {
	Tetromino(const Vec pos, TetroTemplate* t_template) : pos(pos), t_template(t_template) {};

	Vec pos;
	TetroTemplate* t_template;
    };

    std::vector<Tetromino> tetrominoes;
}

int main()
{
    // The play field is ten blocks wide and fourty blocks high.
    // Only twenty of the vertical blocks are visible to the user.
    const char play_field[40][10] { ' ' };
    
    // The template of all of the available tetrominos in the game.
    // The shape is defined by specifying the coordinates of each block.
    static constexpr TetroTemplate i_tetro { Vec(0, 0), Vec(0, 1), Vec(0, 2), Vec(0, 3) };
    static constexpr TetroTemplate j_tetro { Vec(1, 0), Vec(1, 1), Vec(1, 2), Vec(0, 2) };
    static constexpr TetroTemplate l_tetro { Vec(0, 0), Vec(0, 1), Vec(0, 2), Vec(1, 2) };
    static constexpr TetroTemplate o_tetro { Vec(0, 0), Vec(0, 1), Vec(1, 0), Vec(1, 1) };
    static constexpr TetroTemplate s_tetro { Vec(0, 1), Vec(1, 1), Vec(0, 1), Vec(0, 2) };
    static constexpr TetroTemplate t_tetro { Vec(1, 0), Vec(0, 1), Vec(1, 1), Vec(2, 1) };
    static constexpr TetroTemplate z_tetro { Vec(0, 0), Vec(1, 0), Vec(1, 1), Vec(2, 1) };

    // TODO: Set up a random number generator to determine what type of tetromino to generate

    
    for(;;)
    {
	
    }
}
