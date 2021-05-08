#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <cassert>
#include <functional>
#include <vector>
#include "utility.h"

class PlayField
{
public:	
    // utility for printing the ascii representation of the playfield
    void print(const Tetromino::Tetromino& tetro) const noexcept
    {
	// take a copy of the playfield and apply the current tetromino on top
	std::string playfield_copy(playfield.data());

	for (int y = 0; y < 4; y++)
	    for (int x = 0; x < 4; x++)
		if (char tile = tetro.t_template[y * 4 + x]; tile != ' ' && tetro.pos.y + y >= 0)
		    playfield_copy[(tetro.pos.y + y) * 10 + tetro.pos.x + x] = tile;
	
	for (int y = 0; y < 20; y++)
	{
	    for (int x = 0; x < 10; x++)
	    {
		if (char tile = playfield_copy[y * 10 + x]; tile == ' ')
		    std::cout << '-';
		else
		{
		    std::cout << tile;
		}
	    }
		 
	    std::cout << '\n';
	}
    }

    char at(int x, int y) const noexcept
    {
	return playfield[y * 10 + x];
    }

    void add_tetro(const Tetromino::Tetromino& tetro) noexcept
    {
	for (int y = 0; y < 4; y++)
	    for (int x = 0; x < 4; x++)
	    {		    
		if (char tile = tetro.t_template[y * 4 + x]; tile != ' ')
		{
		    set_tile(tetro.pos.x + x, tetro.pos.y + y, tile);
		}
	    }
    }

    bool can_move(const Tetromino::Tetromino& tetro, const Direction direction) const noexcept
    {
	auto vel = [] (const Direction direction, const Direction option_a, const Direction option_b)
	{
	    if (direction == option_a) return -1;
	    if (direction == option_b) return  1;

	    return 0;
	};
	
	const int x_vel = vel(direction, Direction::Left, Direction::Right);
	const int y_vel = direction == Direction::Down ? 1 : 0;

	const auto new_pos = Vec(tetro.pos.x + x_vel, tetro.pos.y + y_vel);

	for (int y = 0; y < 4; y++)
	    for (int x = 0; x < 4; x++)
		if (tetro.t_template[y * 4 + x] != ' ')
		{
		    int x_offset = new_pos.x + x, y_offset = new_pos.y + y;

		    if (x_offset >= 10 || x_offset <= 0 || y_offset >= 20 || playfield[y_offset * 10 + x_offset] != ' ')
			return false;
		}

	return true;
    }

    void clear_all() noexcept
    {
	std::fill(playfield.begin(), playfield.end(), ' ');
    }

    void clear(const std::vector<int>& rows)
    {
	for (const auto row : rows)
	    std::fill_n(playfield.begin() + (row * 10), 10, ' ');
    }

    void lower_tetros()
    {
	
    }

    std::string_view get_playfield() const
    {
	return playfield.c_str();
    }

    std::vector<int> get_full_rows() const
    {
	return get_rows([] (const char tile) { return tile == ' '; });
    }

    std::vector<int> get_empty_rows() const
    {
	return get_rows([] (const char tile) { return tile != ' '; });
    }

private:
    std::string playfield
    {		
	"          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    };

    void set_tile(int x, int y, char val) noexcept
    {
	playfield[y * 10 + x] = val;
    }

    std::vector<int> get_rows(const std::function<bool(char)>& predicate) const
    {
	std::vector<int> rows;
	
	for (int y = 0; y < 20; y++)
	{
	    bool satisfied = true;

	    for (int x = 0; x < 10; x++)
       		if (predicate(playfield[y * 10 + x]))
		{
		    satisfied = false;
		    break;		    
		}

	    if (satisfied)
		rows.push_back(y);
	}

	return rows;
    }
};


#endif
