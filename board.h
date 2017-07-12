#ifndef BOARD_H
#define BOARD_H
#include "matrix.h"

class Board
{
public:
    enum Direction {
        Up,
        Down,
        Left,
        Right,
    };

public:
    Board();
    void gen(int row, int col);

    bool move(Direction d);

    Pos get_null_pos() const { return null_pos; }

    const Matrix& inner_matrix() const;

    void print() const;
    bool isDone() const;
private:
    void init_matrix();
    bool move(int dr, int dc);
    void swap_null(Pos p);
private:
    Matrix m;
    Pos null_pos;
public:
    static constexpr int null_pos_val = 0;
};

#endif // BOARD_H
