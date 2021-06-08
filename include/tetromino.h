#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <string>
#include <string_view>
#include <vector>

#include "utility.h"

namespace Tetromino
{
    class TetroTemplate
    {
    public:
	TetroTemplate(std::array<std::string, 4>&& init);

	std::string_view operator[](const std::size_t index) const;

	int templ_size;

    private:
	std::array<std::string, 4> templs;
    };
    
    // The template of all of the available tetrominos in the game.    
    static TetroTemplate i_tetro ({ "    IIII        ", "  I   I   I   I ", "        IIII    " , " I   I   I   I  " });
    static TetroTemplate o_tetro ({ "OO OO    ", "OO OO    ", "OO OO    ", "OO OO    " });
    static TetroTemplate j_tetro ({ "J  JJJ   ", " JJ J  J ", "   JJJ  J", " J  J JJ " });
    static TetroTemplate l_tetro ({ "  LLLL   ", " L  L  LL", "   LLLL  ", "LL  L  L " });
    static TetroTemplate s_tetro ({ " SSSS    ", " S  SS  S", "    SSSS ", "S  SS  S " });
    static TetroTemplate t_tetro ({ " T TTT   ", " T  TT T ", "   TTT T ", " T TT  T " });
    static TetroTemplate z_tetro ({ "ZZ  ZZ   ", "  Z ZZ Z ", "   ZZ  ZZ", " Z ZZ Z  " });

    class Tetromino
    {
    public:
	Tetromino(const Vec pos, const TetroTemplate& t_template);

	Tetromino& operator=(Tetromino&&) = default;
	
	Vec pos;
	TetroTemplate t_template;

	void rotate();
	
	std::size_t current_orientation() const;
	std::size_t next_orientation() const;
	
    private:
	std::size_t orientation { 0 };
    };

    TetroTemplate get_tetro_template(const int type);

    Tetromino get_new_tetro();
}

#endif
