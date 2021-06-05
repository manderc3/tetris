#ifndef RENDERING_H
#define RENDERING_H

#include <algorithm>
#include <optional>

#include <SDL2/SDL.h>

#include "utility.h"
#include "colour.h"
#include "tetromino.h"

namespace Rendering
{
    static constexpr std::string_view tetro_tile
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

    static constexpr int tile_size = 8;

    void render_tetro_tile(SDL_Renderer* renderer, const Vec& vec, const Colour colour);

    void render_playfield(SDL_Renderer* renderer, const Vec& playfield_pos, const std::string_view& playfield, Tetromino::Tetromino* tetro = nullptr);
}

#endif
