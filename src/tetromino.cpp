#include "../include/tetromino.h"

Tetromino::TetroTemplate::TetroTemplate(const Colour colour, std::array<std::string, 4>&& templs)
    : colour(colour)
    , m_templs(templs)
{
    for (templ_size = 2; templ_size < 10; templ_size++)
	if (static_cast<int>(m_templs[0].length()) / templ_size == templ_size)
	    break;
}

std::string_view Tetromino::TetroTemplate::operator[](const std::size_t index) const
{
    return m_templs[index];
}

Tetromino::Tetromino::Tetromino(const Vec pos, const TetroTemplate& t_template)
    : pos(pos)
    , t_template(t_template)
{
};

void Tetromino::Tetromino::rotate()
{
    orientation = (orientation + 1) % 4;
}
	
std::size_t Tetromino::Tetromino::current_orientation() const
{
    return orientation;
}

std::size_t Tetromino::Tetromino::next_orientation() const
{
    return (orientation + 1) % 4;
}

Tetromino::TetroTemplate Tetromino::get_tetro_template(const int type)
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

Tetromino::Tetromino Tetromino::get_new_tetro()
{
    const auto new_tetro_template = get_tetro_template(std::rand() % 7);
    return Tetromino(Vec(4, 0 - get_ypos_offset(new_tetro_template[0]) - 1), new_tetro_template);
}
	

