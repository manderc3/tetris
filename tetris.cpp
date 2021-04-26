#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include "include/utility.h"
#include "include/tetromino.h"
#include "include/playfield.h"

namespace
{
    enum class GameState : std::int8_t
    {
	GenerateTetro,
	EndGame,
	LowerTetro,
	TetroLanded,
	CheckRows,
	ClearRows
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

    const auto new_tetro_template = Tetromino::get_tetro_template(std::rand() % 7);
    auto current_tetro = Tetromino::Tetromino(Vec(4, 0 - get_ypos_offset(new_tetro_template) - 1), new_tetro_template);

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
	    //current_tetro = Tetromino::get_new_tetro(std::rand() % 7, Vec(0, 0));
	    game_state = GameState::LowerTetro;
	    break;
	}
	case GameState::LowerTetro:
	{
	    // TODO check for input to determine x pos of movement vector
	    current_tetro.pos += Vec(0, 1);

	    if (playfield.has_landed(current_tetro))
	    {
		// Cannot lower tetro further tetro.
		game_state = GameState::TetroLanded;
	    }
	    
	    break;
	}
	case GameState::TetroLanded:
	{
	    game_state = GameState::CheckRows;
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

	playfield.print(current_tetro);
    }
}
