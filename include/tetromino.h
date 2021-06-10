#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <string>
#include <string_view>
#include <vector>

#include "utility.h"
#include "colour.h"

namespace Tetromino
{
    class TetroTemplate
    {
    public:
	TetroTemplate(const Colour colour, std::array<std::string, 4>&& templs);
	TetroTemplate(const TetroTemplate&) = default;
	
	TetroTemplate& operator=(TetroTemplate&& rhs)
	{
	    templ_size = rhs.templ_size;
	    m_templs = std::move(rhs.m_templs);
	    colour = rhs.colour;
	    
	    return *this;
	}
	
	std::string_view operator[](const std::size_t index) const;

	int templ_size;

	Colour colour;

    private:
	std::array<std::string, 4> m_templs;
    };
    
    // The template of all of the available tetrominos in the game.    
    static TetroTemplate i_tetro (Colour::light_blue, { "    IIII        ", "  I   I   I   I ", "        IIII    " , " I   I   I   I  " });
    static TetroTemplate o_tetro (Colour::yellow, { "OO OO    ", "OO OO    ", "OO OO    ", "OO OO    " });
    static TetroTemplate j_tetro (Colour::blue, { "J  JJJ   ", " JJ J  J ", "   JJJ  J", " J  J JJ " });
    static TetroTemplate l_tetro (Colour::orange, { "  LLLL   ", " L  L  LL", "   LLLL  ", "LL  L  L " });
    static TetroTemplate s_tetro (Colour::green, { " SSSS    ", " S  SS  S", "    SSSS ", "S  SS  S " });
    static TetroTemplate t_tetro (Colour::purple, { " T TTT   ", " T  TT T ", "   TTT T ", " T TT  T " });
    static TetroTemplate z_tetro (Colour::red, { "ZZ  ZZ   ", "  Z ZZ Z ", "   ZZ  ZZ", " Z ZZ Z  " });

    class Tetromino
    {
    public:
	Tetromino(const Vec pos, const TetroTemplate& t_template);
	Tetromino(Tetromino&&) = default;

	Tetromino& operator=(Tetromino&& rhs)
	{
	    t_template = std::move(rhs.t_template);
	    pos = rhs.pos;
	    orientation = 0;
	    return *this;
	}
	
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
