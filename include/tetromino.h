#ifndef TETROMINO_H
#define TETROMINO_H

#include "utility.h"

namespace Tetromino
{
    using TetroTemplate = std::string_view;

    // The template of all of the available tetrominos in the game.
    // The shape is defined by specifying the coordinates of each block.
    static constexpr TetroTemplate i_tetro { "I   I   I   I   " };
    static constexpr TetroTemplate j_tetro { "     J   J  JJ  " };
    static constexpr TetroTemplate l_tetro { "    L   L   LL  " };
    static constexpr TetroTemplate s_tetro { "         SS SS  " };
    static constexpr TetroTemplate o_tetro { "        OO  00  " };
    static constexpr TetroTemplate t_tetro { "        TTT  T  " };
    static constexpr TetroTemplate z_tetro { "        ZZ   ZZ " };

    // Debug function
    void print_tetro_template(const TetroTemplate& t)
    {
	auto f = [](const char tile) { return tile == ' ' ? '-' : tile; };
	
	for (unsigned i = 0; i < t.size(); i += 4)
	{
	    std::cout << f(t[i]) << f(t[i + 1]) << f(t[i + 2]) << f(t[i + 3]) << '\n';  
	}
    }

    struct Tetromino
    {
	Tetromino(const Vec pos, const TetroTemplate& t_template) : pos(pos), t_template(t_template) {};

	Vec pos;
	const TetroTemplate& t_template;
    };

    Tetromino get_new_tetro(const int type, Vec&& pos)
    {
	auto which = [] (const char* val) { std::cout << "Added a " << val; };
	switch(type)
	{
	case 0: /*which("i_tetro");*/ return Tetromino(std::move(pos), i_tetro);
	case 1: /*which("j_tetro");*/ return Tetromino(std::move(pos), j_tetro);
    	case 2: /*which("l_tetro");*/ return Tetromino(std::move(pos), l_tetro);
    	case 3: /*which("o_tetro");*/ return Tetromino(std::move(pos), o_tetro);
      	case 4: /*which("s_tetro");*/ return Tetromino(std::move(pos), s_tetro);
       	case 5: /*which("t_tetro");*/ return Tetromino(std::move(pos), t_tetro);
       	case 6: /*which("z_tetro");*/ return Tetromino(std::move(pos), z_tetro);
	default:                      return Tetromino(std::move(pos), z_tetro);
	}
    }
}

#endif
