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

    template<typename T>
    bool duration_elapsed(const std::chrono::time_point<std::chrono::steady_clock>& epoch, const int duration)
    {
	using namespace std::chrono;
  
	return duration_cast<T>(steady_clock::now() - epoch).count() > duration;
    }

    bool apply_booster = false;

    // booster is applied temporarily to the game_speed variable when the player presses down
    constexpr std::int8_t booster = 5;
    
    // the speed of which the tetrominoes fall. the higher the number, the faster the descent
    std::int8_t game_speed = 20;

    // count down
    std::int8_t descent_delay = game_speed;

    constexpr int frame_rate = 60;

    constexpr int window_width = 300;
    
    constexpr int window_height = 300;
    
    constexpr auto playfield_pos = Vec(32, 32);

    // time between increment of game speed
    constexpr auto speed_interval = std::chrono::minutes(1);
}

int main()
{
    Direction input_direction = Direction::None;

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

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Required for scaling
    SDL_RenderSetLogicalSize(renderer, window_width, window_height);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    auto playfield = PlayField();

    // Seed for random number generator
    // TODO use the newer random library
    std::srand(std::time(nullptr));

    auto game_state = GameState::LowerTetro;
    auto current_tetro = Tetromino::get_new_tetro();
    bool render_current_tetro = true;
    
    auto frame_epoch = std::chrono::steady_clock::now();

    // the last time the speed increased (or the beginning of the game if the speed has yet to increase)
    auto speed_epoch = std::chrono::steady_clock::now();
    
    for(;;)
    {
	// input handling
	if (SDL_Event e; SDL_PollEvent(&e))
	{
	    if (e.type == SDL_QUIT)
	    {
		break;
	    }

	    else if (e.type == SDL_KEYUP || e.type == SDL_KEYDOWN)
            {
                auto key_state = SDL_GetKeyboardState(nullptr);

		// downward movement input event		
		apply_booster = key_state[SDL_SCANCODE_DOWN];
		
		// sideways movement input events
                if (key_state[SDL_SCANCODE_LEFT])
		{
		    input_direction = Direction::Left;

		}
		else if (key_state[SDL_SCANCODE_RIGHT])
		{
		    input_direction = Direction::Right;
		}		
		else
		{
		    input_direction = Direction::None;
		}

		// rotation input event
		if (key_state[SDL_SCANCODE_A] && playfield.can_rotate(current_tetro))
		{
		    current_tetro.rotate();
		}
            }
	}

	if (duration_elapsed<std::chrono::minutes>(speed_epoch, 0.1) && game_speed > 0)
	{
	    game_speed -= 2;
	    speed_epoch = std::chrono::steady_clock::now();
	}

	if (duration_elapsed<std::chrono::milliseconds>(frame_epoch, 1000 / frame_rate))
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

		// Ensure current_tetro will be rendered
		render_current_tetro = true;
		break;
	    }
	    case GameState::LowerTetro:
	    {
		if (descent_delay == 0 || apply_booster)
		{
		    // lower the tetromino
		    current_tetro.pos += Vec(0, 1);
		    
		    descent_delay = game_speed;
		}
		else		    
		{
		    --descent_delay;
		}

		// Check if the player has attempted to move the tetro to either side
		switch(input_direction)
		{
		case Direction::Left:
		    if (playfield.can_move(current_tetro, Direction::Left))
			current_tetro.pos += Vec(-1, 0);
		    break;
		case Direction::Right:
    		    if (playfield.can_move(current_tetro, Direction::Right))
			current_tetro.pos += Vec(1, 0);
		    break;
		default:
		    // No movement
		    break;
		}

		if (!playfield.can_move(current_tetro, Direction::Down))
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

		// do not render current tetro until a new tetro has been generated
		render_current_tetro = false;
		break;
	    }
	    case GameState::ClearRows:
	    {
		// Keep entering this state until no full rows are detected
		if (auto full_rows = playfield.get_full_rows(); full_rows.empty())
		{
		    game_state = GameState::GenerateTetro;
		}
		else
		{
		    playfield.clear(full_rows);
		    playfield.compress();
		}

		break;
	    }
	    }

	    frame_epoch = std::chrono::steady_clock::now();
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	if (render_current_tetro)
	{
	    Rendering::render_playfield(renderer, playfield_pos, playfield.get_playfield(), &current_tetro);
	}
	else
	{
	    Rendering::render_playfield(renderer, playfield_pos, playfield.get_playfield());
	}

	SDL_RenderPresent(renderer);
    }
}
