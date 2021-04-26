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
	ClearRows
    };
}

int main()
{
    auto playfield = PlayField();

    // Seed for random number generator
    // TODO use the newer random library
    std::srand(std::time(nullptr));

    auto game_state = GameState::LowerTetro;
    auto current_tetro = Tetromino::get_new_tetro();

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
	    current_tetro = Tetromino::get_new_tetro();
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
	    // Commit current tetro to playfield
	    playfield.add_tetro(current_tetro);
	    game_state = GameState::ClearRows;
	    break;
	}
	case GameState::ClearRows:
	{
	    // TODO - Check for rull rows, clear them, lower higher rows, check again, repeat, then transition to the GenerateTetro state
	    break;
	}
	}

	playfield.print(current_tetro);
    }
}
