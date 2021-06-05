#include <cassert>

#include "../include/rendering.h"

void Rendering::render_tetro_tile(SDL_Renderer* renderer, const Vec& vec, const Colour colour)
{
    const auto& rgb = rgb_mappings.at(colour);
	
    for (int y = 0; y < 8; y++)
	for (int x = 0; x < 8; x++)
	{
	    switch(tetro_tile[y * 8 + x])
	    {
	    case ' ': /* light */  SDL_SetRenderDrawColor(renderer, rgb[0].r, rgb[0].g, rgb[0].b, SDL_ALPHA_OPAQUE); break;
	    case '#': /* base */   SDL_SetRenderDrawColor(renderer, rgb[2].r, rgb[2].g, rgb[2].b, SDL_ALPHA_OPAQUE); break;
	    case '?': /* medium */ SDL_SetRenderDrawColor(renderer, rgb[1].r, rgb[1].g, rgb[1].b, SDL_ALPHA_OPAQUE); break;
	    default : /* dark*/    SDL_SetRenderDrawColor(renderer, rgb[3].r, rgb[3].g, rgb[3].b, SDL_ALPHA_OPAQUE); break;
	    }

	    SDL_RenderDrawPoint(renderer, vec.x + x, vec.y + y);
	}
}

void Rendering::render_playfield(SDL_Renderer* renderer, const Vec& playfield_pos, const std::string_view& playfield, Tetromino::Tetromino* tetro)
{
    assert(playfield_pos.x % 8 == 0);
    assert(playfield_pos.y % 8 == 0);

    std::string playfield_copy(playfield);

    if (tetro != nullptr)
    {
    	const auto orientation = tetro->t_template[tetro->current_orientation()];
    	const auto templ_size = tetro->t_template.templ_size;

    	for (int y = 0; y < templ_size; y++)
	    for (int x = 0; x < templ_size; x++)
		if (char tile(orientation[y * templ_size + x]); tile != ' ' && tetro->pos.y + y >= 0)	
		    playfield_copy[(tetro->pos.y + y) * 10 + tetro->pos.x + x] = tile;
    }
    	
    for (int y = 0; y < 20; y++)
    {
	for (int x = 0; x < 10; x++)
	{
	    const auto pos = Vec(playfield_pos.x + (x * tile_size), playfield_pos.y + (y * tile_size));
				     
	    switch(playfield_copy[y * 10 + x])
	    {
	    case 'I': render_tetro_tile(renderer, pos, Colour::light_blue); break;
	    case 'J': render_tetro_tile(renderer, pos, Colour::blue);       break;
	    case 'L': render_tetro_tile(renderer, pos, Colour::orange);     break;
	    case 'S': render_tetro_tile(renderer, pos, Colour::green);      break;
	    case 'O': render_tetro_tile(renderer, pos, Colour::yellow);     break;
	    case 'T': render_tetro_tile(renderer, pos, Colour::purple);     break;
	    case 'Z': render_tetro_tile(renderer, pos, Colour::red);        break;
	    default: break;					    
	    }
	}
    }
}

