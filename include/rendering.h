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

    static constexpr std::string_view hud_template
    {
	"####################"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"
	"#          #       #"    
	"####################"
    };

    static constexpr Vec hud_size = Vec(20, 22);

    static constexpr int tile_size = 8;

    void render_tetro_tile(SDL_Renderer* renderer, const Vec& vec, const Colour colour);

    void render_playfield(SDL_Renderer* renderer, const Vec& playfield_pos, const std::string_view& playfield, Tetromino::Tetromino* tetro = nullptr);

    void render_hud(SDL_Renderer* renderer, const Vec& playfield_pos, int level, int score, const Tetromino::Tetromino& next, const std::optional<Tetromino::Tetromino>& reserve);

    void render_tetro(SDL_Renderer* renderer, const Tetromino::TetroTemplate& tetro_template, const Vec& pos, const int orientation);

    void render_text(SDL_Renderer* renderer, const Vec& pos, const std::string_view& text, const Colour colour);
}

#endif
