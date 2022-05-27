#include "Game15.h"

#include <algorithm>
#include <numeric>
#include <random>


/**/
Game15::Game15()
{
    // prepare field with dummy values
    _field.resize(_side + 2);
    for( int i = 0; i < _field.size(); ++i )
        _field[i] = std::vector<int>(_side + 2, -1);

    // shuffled values on board
    std::vector<int> numbers(_side * _side);
    std::iota(numbers.begin(), numbers.end(), 0);

    std::random_device rd;
    std::mt19937 sf(rd());
    std::shuffle(numbers.begin(), numbers.end(), sf);
    auto zp = std::find(numbers.begin(), numbers.end(), 0);
    std::iter_swap(numbers.end() - 1, zp);

    // transpositions
    bool solvable = false;
    for( auto i = numbers.begin(); i != numbers.end() - 1; ++i )
        for( auto j = i + 1; j < numbers.end(); ++j )
            solvable = !solvable != (*i <= *j);

    if( !solvable )
        std::iter_swap(numbers.begin(), numbers.begin()+1);

    for( int r = 1; r <= _side; ++r )
        for( int c = 1; c <= _side; ++c )
            _field[r][c] = numbers[(r - 1) * _side + (c - 1)];
}


/**/
size_t Game15::side() const
{
    return _side;
}


/**/
int Game15::field(size_t r, size_t c) const
{
    return _field[r+1][c+1];
}


/**/
void Game15::play(size_t r, size_t c)
{
    static const std::vector<std::vector<int>> dirs{
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    ++r; ++c;
    if( _field[r-1][c] == 0 )
        return swap(r, c, r - 1, c);

    if( _field[r+1][c] == 0 )
        return swap(r, c, r + 1, c);

    if( _field[r][c-1] == 0 )
        return swap(r, c, r, c - 1);

    if( _field[r][c+1] == 0 )
        return swap(r, c, r, c + 1);
}


/**/
void Game15::swap(size_t ra, size_t ca, size_t rb, size_t cb)
{
    auto v0 = _field[ra][ca];
    _field[ra][ca] = _field[rb][cb];
    _field[rb][cb] = v0;

    ++_step;
}


/**/
int Game15::step() const
{
    return _step;
}


/**/
bool Game15::isOver() const
{
    static const std::vector<std::vector<int>> win{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    for( int r = 1; r <= _side; ++r )
        for( int c = 1; c <= _side; ++c )
            if( _field[r][c] != win[r-1][c-1] )
                return false;

    return true;
}
