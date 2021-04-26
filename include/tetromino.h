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
	Tetromino(const Vec pos, TetroTemplate t_template) : pos(pos), t_template(t_template) {};

	Tetromino& operator=(Tetromino&&) = default;
	
	Vec pos;
	TetroTemplate t_template;
    };

    TetroTemplate get_tetro_template(const int type)
    {
	switch(type)
	{
	case 0:  return i_tetro;
	case 1:  return j_tetro;
    	case 2:  return l_tetro;
    	case 3:  return o_tetro;
      	case 4:  return s_tetro;
       	case 5:  return t_tetro;
       	case 6:  return z_tetro;
	default: return z_tetro;
	}
    }
}

#endif
