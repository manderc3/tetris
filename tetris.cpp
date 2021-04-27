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
	"#      @"
	"#      @"
	"#      @"
	"#      @"
	"#      @"
	"#      @"
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
	red
    };

    struct RGB
    {
	std::uint8_t r, g, b;
    };

    std::unordered_map<Colour, RGB> rgb_mappings
    {
	{ Colour::light_blue, { 0x00, 0xFF, 0xFF } },
	{ Colour::blue,       { 0x00, 0x00, 0xFF } },
	{ Colour::orange,     { 0xFF, 0x80, 0x00 } },
	{ Colour::yellow,     { 0xFF, 0xFF, 0x00 } },
	{ Colour::green,      { 0x00, 0xCC, 0x00 } },
	{ Colour::purple,     { 0xFF, 0x00, 0xFF } },
	{ Colour::red,        { 0xFF, 0x00, 0x00 } },	    
    };    

    void draw_tetro_tile(SDL_Renderer* renderer, const Vec& vec, const Colour colour)
    {
	const auto& rgb = rgb_mappings.at(colour);

	SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, SDL_ALPHA_OPAQUE); 
	
	for (int y = 0; y < 8; y++)
	    for (int x = 0; x < 8; x++)
	    {
		SDL_RenderDrawPoint(renderer, vec.x + x, vec.y + y);		
	    }
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
