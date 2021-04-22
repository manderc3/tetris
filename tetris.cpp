#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include "include/utility.h"
#include "include/tetromino.h"

namespace
{
    enum class GameState
    {
	GenerateTetro,
	EndGame,
	LowerTetro,
	ClearRows
    };

    // The play field is ten blocks wide and fourty blocks high.
    // Only twenty of the vertical blocks are visible to the user
    class PlayField
    {
    public:	
        // utility for printing the ascii representation of the playfield
	void print() const noexcept
	{
	    for (int y = 0; y < 20; y++)
	    {
		for (int x = 0; x < 10; x++)
		{
		    if (char tile = playfield[y * 10 + x]; tile == ' ')
			std::cout << '-';
		    else
			std::cout << tile;
		}
		 
		std::cout << '\n';
	    }
	}

	char at(int x, int y) const noexcept
	{
	    return playfield[y * 10 + x];
	}

	void add_tetro(const Tetromino::Tetromino& tetromino) noexcept
	{
	    for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
		{		    
		    if (char tile = tetromino.t_template[y * 4 + x]; tile != ' ')
		    {
			set_tile(tetromino.pos.x + x, tetromino.pos.y + y, tile);
		    }
		}
	}

	void clear_all() noexcept
	{
	    std::fill(playfield.begin(), playfield.end(), ' ');
	}

	void clear(const std::vector<std::int8_t>& rows)
	{
	    for (const auto row : rows)
		std::fill_n(playfield.begin() + (row * 10), 10, ' ');
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
    };
}

int main()
{
    auto playfield = PlayField();

    // Tetromino::print_tetro_template(Tetromino::i_tetro); std::cout << '\n';
    // Tetromino::print_tetro_template(Tetromino::j_tetro); std::cout << '\n';
    // Tetromino::print_tetro_template(Tetromino::l_tetro); std::cout << '\n';
    // Tetromino::print_tetro_template(Tetromino::s_tetro); std::cout << '\n';
    // Tetromino::print_tetro_template(Tetromino::o_tetro); std::cout << '\n';
    // Tetromino::print_tetro_template(Tetromino::t_tetro); std::cout << '\n';
    // Tetromino::print_tetro_template(Tetromino::z_tetro); std::cout << '\n';
    
    // Seed for random number generator
    std::srand(std::time(nullptr));
    
    for(;;)
    {
	std::cin.ignore();

	// Generate new tetromino
	//auto current_tetro = Tetromino::get_new_tetro(std::rand() % 7, Vec(1, 1));
	auto current_tetro = Tetromino::get_new_tetro(0, Vec(1, 16));

	playfield.add_tetro(current_tetro);
	playfield.clear({17, 19});
	playfield.print();
    }
}
