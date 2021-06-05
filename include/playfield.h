#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <functional>
#include <vector>

#include "utility.h"
#include "tetromino.h"

class PlayField
{
public:
    // used for debugging
    void print() const noexcept;
    
    char at(int x, int y) const noexcept;

    void add_tetro(const Tetromino::Tetromino& tetro) noexcept;

    bool can_move(const Tetromino::Tetromino& tetro, const Direction direction) const noexcept;

    bool can_rotate(const Tetromino::Tetromino& current) const;

    void clear_all() noexcept;

    void clear(const std::vector<int>& rows);

    void compress();

    std::string_view get_playfield() const;

    std::vector<int> get_full_rows() const;

    std::vector<int> get_empty_rows() const;

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

    void set_tile(int x, int y, char val) noexcept;
    
    std::vector<int> get_rows(const std::function<bool(char)>& predicate) const;
};

#endif
