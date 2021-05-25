#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include <string_view>
#include <vector>

#include "utility.h"

namespace Tetromino
{
    class TetroTemplate
    {
    public:
	template<typename... T>
	constexpr TetroTemplate(T... ts) : templs{ts...}
	{
	    for (templ_size = 2; templ_size < 10; templ_size++)
		if (templs[0].length() / templ_size == templ_size)
		    break;
	}

	constexpr std::string_view operator[](const std::size_t index) const
	{
	    return templs[index];
	}

	std::size_t templ_size;

    private:
	std::array<std::string_view, 4> templs;
    };
    
    // The template of all of the available tetrominos in the game.    
    constexpr TetroTemplate i_tetro ( "    IIII        ", "  I   I   I   I ", "        IIII    " , " I   I   I   I  " );
    constexpr TetroTemplate o_tetro ( " OO  OO     ", " OO  OO     ", " OO  OO     ", " OO  OO     " );
    constexpr TetroTemplate j_tetro ( "J  JJJ   ", "J  JJJ   ", "J  JJJ   ", "J  JJJ   " ); 
    constexpr TetroTemplate l_tetro ( "  LLLL   ", " L  L  LL", "   LLLL  ", "LL  L  L " ); 
    constexpr TetroTemplate s_tetro ( " SSSS    ", " S  SS  S", "    SSSS ", "S  SS  S " ); 
    constexpr TetroTemplate t_tetro ( " T TTT   ", " T  TT T ", "   TTT T ", " T TT  T " ); 
    constexpr TetroTemplate z_tetro ( "ZZ  ZZ   ", "  Z ZZ Z ", "   ZZ  ZZ", " Z ZZ Z  " ); 
    
    class Tetromino
    {
    public:
	Tetromino(const Vec pos, TetroTemplate t_template) : pos(pos), t_template(t_template) {};

	Tetromino& operator=(Tetromino&&) = default;
	
	Vec pos;
	TetroTemplate t_template;

	void rotate() { orientation = (orientation + 1) % 4; }
	
	std::size_t current_orientation() const { return orientation; }
	std::size_t next_orientation() const { return (orientation + 1) % 4; }
	
    private:
	std::size_t orientation { 0 };
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

    Tetromino get_new_tetro()
    {
	const auto new_tetro_template = get_tetro_template(std::rand() % 7);
	return Tetromino(Vec(4, 0 - get_ypos_offset(new_tetro_template[0]) - 1), new_tetro_template);
    }
}

#endif
