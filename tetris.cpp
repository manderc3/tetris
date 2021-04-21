#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string_view>
#include <vector>

namespace
{
    enum class GameState
    {
	GenerateTetro,
	EndGame,
	LowerTetro,
	ClearRows
    };
    
    struct Vec
    {
	constexpr Vec(std::int8_t x, std::int8_t y) : x(x), y(y) {};
	constexpr Vec(const Vec&) = default;
	constexpr Vec(Vec&&) = default;   

	std::int8_t x, y;
    };

    using TetroTemplate = std::string_view;

    // The template of all of the available tetrominos in the game.
    // The shape is defined by specifying the coordinates of each block.
    static constexpr TetroTemplate i_tetro { "  I    I    I    I  " };
    static constexpr TetroTemplate j_tetro { "       J    J   JJ  " };
    static constexpr TetroTemplate l_tetro { "       L    L    LL " };
    static constexpr TetroTemplate s_tetro { "           SS  SS   " };
    static constexpr TetroTemplate o_tetro { "          OO   00   " };
    static constexpr TetroTemplate t_tetro { "           TTT   T  " };
    static constexpr TetroTemplate z_tetro { "          ZZ    ZZ  " };

    // Debug function
    void print_tetro_template(const TetroTemplate& t)
    {
	auto f = [](const char tile) { return tile == ' ' ? '-' : tile; };
	
	for (unsigned i = 0; i < t.size(); i += 5)
	{
	    std::cout << f(t[i]) << f(t[i + 1]) << f(t[i + 2]) << f(t[i + 3]) << f(t[i + 4]) << '\n';  
	}
    }

    struct Tetromino
    {
	Tetromino(const Vec pos, const TetroTemplate& t_template) : pos(pos), t_template(t_template) {};

	Vec pos;
	const TetroTemplate& t_template;
    };

    Tetromino get_new_tetro(const int type, Vec&& pos)
    {
	auto which = [] (const char* val) { std::cout << "Added a " << val; };
	switch(type)
	{
	case 0: which("i_tetro"); return Tetromino(std::move(pos), i_tetro);
	case 1: which("j_tetro"); return Tetromino(std::move(pos), j_tetro);
    	case 2: which("l_tetro"); return Tetromino(std::move(pos), l_tetro);
    	case 3: which("o_tetro"); return Tetromino(std::move(pos), o_tetro);
      	case 4: which("s_tetro"); return Tetromino(std::move(pos), s_tetro);
       	case 5: which("t_tetro"); return Tetromino(std::move(pos), t_tetro);
       	case 6: which("z_tetro"); return Tetromino(std::move(pos), z_tetro);
	default:                  return Tetromino(std::move(pos), z_tetro);
	}
    }

    // The play field is ten blocks wide and fourty blocks high.
    // Only twenty of the vertical blocks are visible to the user
    class PlayField
    {
    public:	
        // utility for printing the ascii representation of the playfield
	void print() const noexcept
	{
	    for (int y = 0; y < 40; y++)
	    {
		for (int x = 0; x < 10; x++)
		    std::cout << playfield[y * 10 + x];
		std::cout << '\n';
	    }
	}

	char at(int x, int y) const noexcept
	{
	    return playfield[y * 10 + x];
	}

	void add_tetro(const Tetromino& tetromino) noexcept
	{
	    for (int y = 0; y < 5; y++)
		for (int x = 0; x < 5; x++)
		{		    
		    if (char tile = tetromino.t_template[y * 5 + x]; tile != ' ')
		    {
			set_tile(tetromino.pos.x + (y * 5) + x, y, tile);
		    }
		}
	}	

    private:
	std::string_view playfield
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
	};

	void set_tile(int x, int y, char val) noexcept
	{
	    //playfield[y * 10 + x] = val;
	}	
    };
}

int main()
{
    auto playfield = PlayField();

    // print_tetro_template(i_tetro); std::cout << '\n';
    // print_tetro_template(j_tetro); std::cout << '\n';
    // print_tetro_template(l_tetro); std::cout << '\n';
    // print_tetro_template(s_tetro); std::cout << '\n';
    // print_tetro_template(o_tetro); std::cout << '\n';
    // print_tetro_template(t_tetro); std::cout << '\n';
    // print_tetro_template(z_tetro); std::cout << '\n';
    
    // Seed for random number generator
    std::srand(std::time(nullptr));
    
    for(;;)
    {
	std::cin.ignore();

	// Generate new tetromino
	auto current_tetro = get_new_tetro(std::rand() % 7, Vec(10, 10));
    }
}