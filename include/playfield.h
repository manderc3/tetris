#ifndef PLAYFIELD_H
#define PLAYFIELD_H

class PlayField
{
public:	
    // utility for printing the ascii representation of the playfield
    void print(const Tetromino::Tetromino& tetro) const noexcept
    {
	// take a copy of the playfield and apply the current tetromino on top
	std::string playfield_copy(playfield.data());
	
	for (int y = 0; y < 20; y++)
	{
	    for (int x = 0; x < 10; x++)
	    {
		if (char tile = playfield_copy[y * 10 + x]; tile == ' ')
		    std::cout << '-';
		else
		{
		    std::cout << tile;
		}
	    }
		 
	    std::cout << '\n';
	}
    }

    char at(int x, int y) const noexcept
    {
	return playfield[y * 10 + x];
    }

    void add_tetro(const Tetromino::Tetromino& tetro) noexcept
    {
	for (int y = 0; y < 4; y++)
	    for (int x = 0; x < 4; x++)
	    {		    
		if (char tile = tetro.t_template[y * 4 + x]; tile != ' ')
		{
		    set_tile(tetro.pos.x + x, tetro.pos.y + y, tile);
		}
	    }
    }

    bool has_landed(const Tetromino::Tetromino& tetro) noexcept
    {
	/* for (int y = 0; y < 4; y++) */
	/*     for (int x = 0; x < 4; x++) */
	/*     {		     */
	/* 	if (char tile = tetro.t_template[y * 4 + x]; tile != ' ') */
	/* 	{ */
	/* 	    if (y == 4 || tetro.t_template[(y + 1) * 4 + x) == ' ') */
	/* 	    { */
	/* 		// current dealing with a section of the tetromino that can collide */
			
	/* 	    } */
	/* 	    set_tile(tetro.pos.x + x, tetro.pos.y + y, tile); */
	/* 	} */
	/*     }	 */

	return true;
    }

    void clear_all() noexcept
    {
	std::fill(playfield.begin(), playfield.end(), ' ');
    }

    void clear(const std::vector<std::int8_t>& rows)
    {
	for (const auto row : rows)
	    std::fill_n(playfield.begin() + (row * 10), 10, ' ');
    }

private:
    std::string playfield
    {		
	"          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    "          "
	    };

    void set_tile(int x, int y, char val) noexcept
    {
	playfield[y * 10 + x] = val;
    }	
};


#endif
