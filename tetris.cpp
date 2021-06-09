#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>
#include <map>

#include <SDL2/SDL.h>

#include "include/utility.h"
#include "include/tetromino.h"
#include "include/playfield.h"
#include "include/colour.h"
#include "include/rendering.h"
#include "include/timer.h"

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

    // when player presses down the tetromino descends at maximum velocity
    bool apply_booster = false;
    
    constexpr int frame_rate = 60;

    constexpr int window_width = 300;
    
    constexpr int window_height = 300;
    
    constexpr auto playfield_pos = Vec(64, 64);
  
    // mappings between game level and descent    
    const std::unordered_map<std::int8_t, std::int8_t> game_speeds
    {
	{1, 20},
	{2, 16},
	{3, 12},
	{4,  8},
	{5,  4},
	{6,  0},    
    };

    auto land_delay_timer = Time::Timer<std::chrono::seconds>(1);

    auto gradual_velocity_timer = Time::Timer<std::chrono::milliseconds>(100);
    
    Vec get_new_horizontal_pos(const PlayField& playfield, const Tetromino::Tetromino& current_tetro, Direction direction)
    {
	// Check if the player has attempted to move the tetro to either side
	switch(direction)
	{
	case Direction::Left:
	    if (playfield.can_move(current_tetro, Direction::Left))
		return Vec(-1, 0);
	    break;
	case Direction::Right:
	    if (playfield.can_move(current_tetro, Direction::Right))
		return Vec(1, 0);
	    break;
	default:
	    break;
	}

	return Vec(0, 0);
    }
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

    std::int8_t current_level = 1;
    std::int8_t descent_delay = game_speeds.at(current_level);
    
    auto game_state = GameState::LowerTetro;
    auto current_tetro = Tetromino::get_new_tetro();
    bool render_current_tetro = true;

    auto frame_timer = Time::Timer<std::chrono::milliseconds>(1000 / frame_rate);

    // the last time the speed increased (or the beginning of the game if the speed has yet to increase)
    auto speed_timer = Time::Timer<std::chrono::minutes>(1);

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
		    gradual_velocity_timer.begin();
		    
		    input_direction = Direction::Left;

		}
		else if (key_state[SDL_SCANCODE_RIGHT])
		{
		    gradual_velocity_timer.begin();
		    
		    input_direction = Direction::Right;
		}		
		else
		{
		    gradual_velocity_timer.stop();
		    
		    input_direction = Direction::None;
		}

		// rotation input event
		if (key_state[SDL_SCANCODE_A] && playfield.can_rotate(current_tetro))
		{
		    current_tetro.rotate();
		}
            }
	}

	if (speed_timer.duration_elapsed() && current_level < 6)
	{
	    speed_timer.begin();
	    current_level++;
	}

	if (frame_timer.duration_elapsed())
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
		if (!playfield.can_move(current_tetro, Direction::Down))
		{
		    // Cannot lower tetro any further.
		    game_state = GameState::TetroLanded;
		}
		else
		{
		    if (descent_delay == 0 || apply_booster)
		    {
			// lower the tetromino
			current_tetro.pos += Vec(0, 1);
		    
			descent_delay = game_speeds.at(current_level);
		    }
		    else		    
		    {
			--descent_delay;
		    }		
		}

		current_tetro.pos += get_new_horizontal_pos(playfield, current_tetro, input_direction);		
	    
		break;
	    }
	    case GameState::TetroLanded:
	    {
		if (!land_delay_timer.has_started())
		{
		    land_delay_timer.begin();
		}
		
		if (land_delay_timer.has_started())
		{
		    if (land_delay_timer.duration_elapsed())
		    {
			// Commit current tetro to playfield
			playfield.add_tetro(current_tetro);
			game_state = GameState::ClearRows;

			// do not render current tetro until a new tetro has been generated
			render_current_tetro = false;

			// unset the following flag if a tetromino lands in the future
			land_delay_timer.stop();
			break;
		    }
		    else
		    {
			// Duration not elapsed, allow player the opportunity to move tetromino
			current_tetro.pos += get_new_horizontal_pos(playfield, current_tetro, input_direction);

			if (playfield.can_move(current_tetro, Direction::Down))
			{
			    game_state = GameState::LowerTetro;
			}			
		    }
		}

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

	    frame_timer.begin();
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	Rendering::render_hud(renderer, playfield_pos, 0, 0, current_tetro, current_tetro);
	
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
