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
    bool move_pos(Pos p);

    Pos get_null_pos() const { return null_pos; }

    int pos_value(Pos p) const;
    Pos value_pos(int value) const;

    void print() const;
    bool isDone() const;
private:
    void init_matrix();
    bool move(int dr, int dc);
    void swap_null(Pos p);
private:
    Matrix m;
    //方向通过value 追踪pos位置
    std::vector<Pos> value_index;
    Pos null_pos;
    static constexpr int null_value = 0;
};

#endif // BOARD_H
