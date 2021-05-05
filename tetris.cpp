#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <SDL2/SDL.h>

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

    constexpr std::string_view tetro_tile
    {
	"########"
	"?      ?"
	"?######?"
	"?######?"
	"?######?"
	"?######?"
	"?######?"
	"@@@@@@@@"
    };

    enum class Colour : std::int8_t
    {
	light_blue,
	blue,
	orange,
	yellow,
	green,
        purple,
	red,
	grey
    };

    struct RGB
    {
	std::uint8_t r, g, b;
    };

    std::unordered_map<Colour, std::array<RGB, 4>> rgb_mappings
    {
	///////////////////////////      Light       ////      Medium      ////       Base       ////       Dark       ///////
    	{ Colour::light_blue, { { { 0xA3, 0xFB, 0xF0 }, { 0x00, 0xBD, 0xC1 }, { 0x55, 0xC3, 0xC5 }, { 0x00, 0x70, 0x94 } } } },
    	{ Colour::blue,       { { { 0xA3, 0xC7, 0xFB }, { 0x05, 0x4A, 0xC3 }, { 0x63, 0x9A, 0xC5 }, { 0x00, 0x15, 0x95 } } } },
    	{ Colour::orange,     { { { 0xFB, 0xCC, 0xA3 }, { 0xC0, 0x55, 0x00 }, { 0xC4, 0xD7, 0x5A }, { 0x91, 0x20, 0x00 } } } },
    	{ Colour::yellow,     { { { 0xFF, 0xFD, 0xC2 }, { 0xC2, 0xAC, 0x04 }, { 0xC5, 0xC3, 0x6A }, { 0x96, 0x67, 0x00 } } } },
    	{ Colour::green,      { { { 0xDF, 0xFB, 0xA3 }, { 0x00, 0xC8, 0x15 }, { 0x8C, 0xC6, 0x76 }, { 0x00, 0x96, 0x02 } } } },
    	{ Colour::purple,     { { { 0xFB, 0xA3, 0xD7 }, { 0xAE, 0x05, 0xBD }, { 0xDA, 0x67, 0xDC }, { 0x6B, 0x00, 0x95 } } } },
    	{ Colour::red,        { { { 0xFB, 0xA3  0xAF }, { 0xB9, 0x05, 0x05 }, { 0xC5, 0x55  0x59 }, { 0x8E, 0x00, 0x00 } } } },
    	{ Colour::grey,       { { { 0x60, 0x60, 0x60 }, { 0x60, 0x60, 0x60 }, { 0x60, 0x60, 0x60 }, { 0x60, 0x60, 0x60 } } } }
    };    

    void draw_tetro_tile(SDL_Renderer* renderer, const Vec& vec, const Colour colour)
    {
    	const auto& rgb = rgb_mappings.at(colour)[0];

    	SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE); 
	
    	for (int y = 0; y < 8; y++)
    	    for (int x = 0; x < 8; x++)
    		SDL_RenderDrawPoint(renderer, vec.x + x, vec.y + y);
    }
}

int main()
{
    constexpr int window_width = 250;
    constexpr int window_height = 250;

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

    for(;;)
    {
	// input handling
	if (SDL_Event e; SDL_PollEvent(&e)) {
	    if (e.type == SDL_QUIT) {
		break;
	    }

	    if (e.type == SDL_KEYDOWN) {
		switch(e.key.keysym.sym) {
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
	
	// switch (game_state)
	// {
	// case GameState::EndGame:
	// {
	//     // TODO handle end-game
	// }
	  
	// case GameState::GenerateTetro:
	// {
	//     // Generate new tetromino
	//     current_tetro = Tetromino::get_new_tetro();
	//     game_state = GameState::LowerTetro;
	//     break;
	// }
	// case GameState::LowerTetro:
	// {
	//     // TODO check for input to determine x pos of movement vector
	//     current_tetro.pos += Vec(0, 1);

	//     if (playfield.has_landed(current_tetro))
	//     {
	// 	// Cannot lower tetro further tetro.
	// 	game_state = GameState::TetroLanded;
	//     }
	    
	//     break;
	// }
	// case GameState::TetroLanded:
	// {
	//     // Commit current tetro to playfield
	//     playfield.add_tetro(current_tetro);
	//     game_state = GameState::GenerateTetro;
	//     break;
	// }
	// case GameState::ClearRows:
	// {
	//     // TODO - Check for rull rows, clear them, lower higher rows, check again, repeat, then transition to the GenerateTetro state
	//     break;
	// }
	// }

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// TODO rendering stuff goes here
	draw_tetro_tile(renderer, Vec(50, 50), Colour::light_blue);

	SDL_RenderPresent(renderer);
    }
}
