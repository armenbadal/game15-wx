#ifndef __GAME15_H__
#define __GAME15_H__

#include <vector>

/**/
class Game15 {
public:
    struct Cell {
        size_t r; // row
        size_t c; // column
    };

    struct Step {
        Cell from;
        Cell to;
    };

public:
    Game15();

    size_t side() const;
    int field(size_t r, size_t c) const;
    void play(size_t r, size_t c);
    int step() const;
    bool isOver() const;

private:
    void swap(size_t ra, size_t ca, size_t rb, size_t cb);

private:
    const int _side = 4;
    std::vector<std::vector<int>> _field;
    int _step = 0;
};

#endif // __GAME15_H__
