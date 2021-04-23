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
    enum class GameState : std::int8_t
    {
	GenerateTetro,
	EndGame,
	LowerTetro,
	CheckRows,
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
    // TODO use the newer random library
    std::srand(std::time(nullptr));

    auto game_state = GameState::LowerTetro;
    auto current_tetro = Tetromino::get_new_tetro(std::rand() % 7, Vec(1, 1));

    for(;;)
    {
	std::cin.ignore();

	switch (game_state)
	{
	case GameState::EndGame:
	{
	    // TODO handle end-game
	}
	  
	case GameState::GenerateTetro:
	{
	    // Generate new tetromino
	    current_tetro = Tetromino::get_new_tetro(std::rand() % 7, Vec(1, 1));
	    game_state = GameState::LowerTetro;
	    break;
	}
	case GameState::LowerTetro:
	{
	    // TODO - Check if it is possible to lower the tetro, if it isn't the tetro has landed and we need to
	    //        move to the CheckFullRows state. Otherwise lower the tetro and remain in that state.
	    //        LowerTetro is the general state also, user input is also check to move left and right.
	    current_tetro.pos += Vec(1, 0);
	    break;
	}
	case GameState::CheckRows:
	{
	    // TODO - CheckFullRows and if any are found, transition to the ClearRows state. Otherwise,
	    //        transition to the GenerateTetro state.
	    break;
	}
	case GameState::ClearRows:
	{
	    // TODO - Identify full rows, clear them, then transition to the GenerateTetro state
	    break;
	}
	}

	playfield.add_tetro(current_tetro);
	playfield.clear({17, 19});
	playfield.print();
    }
}
