#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <SDL2/SDL.h>

#include "include/utility.h"
#include "include/tetromino.h"
#include "include/playfield.h"
#include "include/colour.h"
#include "include/rendering.h"

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

    bool duration_elapsed(const std::chrono::time_point<std::chrono::steady_clock>& epoch, int duration)
    {
	using namespace std::chrono;
  
	return duration_cast<milliseconds>(steady_clock::now() - epoch).count() > duration;
    }
}

int main()
{
    constexpr int window_width = 300;
    constexpr int window_height = 300;
    constexpr auto playfield_pos = Vec(32, 32);

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cerr << "SDL Error: " << SDL_GetError();
    }

    auto window = SDL_CreateWindow("Tetris",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   window_width,
                                   window_height,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Required for scaling
    SDL_RenderSetLogicalSize(renderer, window_width, window_height);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    auto playfield = PlayField();

    // Seed for random number generator
    // TODO use the newer random library
    std::srand(std::time(nullptr));

    auto game_state = GameState::LowerTetro;
    auto current_tetro = Tetromino::get_new_tetro();

    auto frame_epoch = std::chrono::steady_clock::now();
    
    for(;;)
    {
	// input handling
	if (SDL_Event e; SDL_PollEvent(&e))
	{
	    if (e.type == SDL_QUIT)
	    {
		break;
	    }

	    if (e.type == SDL_KEYDOWN)
	    {
		switch(e.key.keysym.sym)
		{
		case SDLK_UP:
		    break;
		case SDLK_DOWN:
		    break;
		case SDLK_LEFT:
		    break;
		case SDLK_RIGHT:
		    break;
		}
	    }
	}

	if (duration_elapsed(frame_epoch, 1000 / 60))
	{
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
		game_state = GameState::GenerateTetro;
		break;
	    }
	    case GameState::ClearRows:
	    {
		// TODO - Check for rull rows, clear them, lower higher rows, check again, repeat, then transition to the GenerateTetro state
		break;
	    }
	    }

	    frame_epoch = std::chrono::steady_clock::now();
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

    // 	constexpr std::string_view test
    // 	{
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // 	    "          "
    // "L         "
    // "L     OO  "
    // "LL    OO  "
    // "   I   TTT"
    // "   I  SST "
    // "   I SS   "
    // "   I      "
    // "       J  "
    // "ZZ     J  "
    // " ZZ   JJ  "		
//	};

	render_playfield(renderer, playfield_pos, playfield.get_playfield());

	SDL_RenderPresent(renderer);
    }
}
