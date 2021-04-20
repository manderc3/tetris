#include <array>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string_view>
#include <vector>

namespace
{
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

    private:
	std::array<char, 40 * 10> playfield; 
    };

    std::vector<Tetromino> tetrominoes;    
} 

int main()
{
    auto playfield = PlayField();
    
    // Seed for random number generator
    std::srand(std::time(nullptr));
    
    for(;;)
    {
	std::cin.ignore();
	
	// generate a random number between 0-6 inclusive to determine which tetromino to genrate
	auto r = std::rand() % 7;

	auto which = [] (const char* val) { std::cout << "Added a " << val; };
	switch(r)
	{
	case 0: which("i_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
	case 1: which("j_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
    	case 2: which("l_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
    	case 3: which("o_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
      	case 4: which("s_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
       	case 5: which("t_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
       	case 6: which("z_tetro"); tetrominoes.emplace_back(Vec(10, 10), i_tetro); break;
	}
    }
}
