#include <array>
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

    using TetroTemplate = std::array<Vec, 4>;

    // The template of all of the available tetrominos in the game.
    // The shape is defined by specifying the coordinates of each block.
    static constexpr TetroTemplate i_tetro { Vec(0, 0), Vec(0, 1), Vec(0, 2), Vec(0, 3) };
    static constexpr TetroTemplate j_tetro { Vec(1, 0), Vec(1, 1), Vec(1, 2), Vec(0, 2) };
    static constexpr TetroTemplate l_tetro { Vec(0, 0), Vec(0, 1), Vec(0, 2), Vec(1, 2) };
    static constexpr TetroTemplate o_tetro { Vec(0, 0), Vec(0, 1), Vec(1, 0), Vec(1, 1) };
    static constexpr TetroTemplate s_tetro { Vec(0, 1), Vec(1, 1), Vec(0, 1), Vec(0, 2) };
    static constexpr TetroTemplate t_tetro { Vec(1, 0), Vec(0, 1), Vec(1, 1), Vec(2, 1) };
    static constexpr TetroTemplate z_tetro { Vec(0, 0), Vec(1, 0), Vec(1, 1), Vec(2, 1) };

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
    // Only twenty of the vertical blocks are visible to the user.
    class PlayField
    {
    public:
	PlayField()
	{
	    std::fill(playfield.begin(), playfield.end(), '#');
	}
	
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

	void add_tetro(Tetromino&& tetromino) noexcept
	{
	    tetrominoes.push_back(std::move(tetromino));
	}	

    private:
	std::array<char, 40 * 10> playfield;
	std::vector<Tetromino> tetrominoes;

	void set(int x, int y, char val) noexcept
	{
	    playfield[y * 10 + x] = val;
	}	
    };
}

int main()
{
    auto playfield = PlayField();

    // Seed for random number generator
    std::srand(std::time(nullptr));
    
    for(;;)
    {
	std::cin.ignore();

	// Generate new tetromino
	auto current_tetro = get_new_tetro(std::rand() % 7, Vec(10, 10));
    }
}
