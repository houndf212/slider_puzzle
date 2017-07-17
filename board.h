#ifndef BOARD_H
#define BOARD_H
#include "matrix.h"

class Board
{
public:
    enum Direction
    {
        NotValid,
        Up,
        Down,
        Left,
        Right,
        Null_Up = Down,
        Null_Down = Up,
        Null_Left = Right,
        Null_Right = Left,
    };
public:
    void gen(int row, int col);

    bool null_move(Direction d);

    Direction test_null_move_to(Pos p) const;

    Pos get_null_pos() const { return null_pos; }

    int pos_value(Pos p) const;
    Pos value_pos(int value) const;

    void print() const;
    bool isDone() const;

    bool isInBoard(Pos p) const { return matrix.isInMatrix(p); }
private:
    void init_matrix();
    bool inner_null_move(int dr, int dc);
    void swap_null(Pos p);
private:
    Matrix matrix;
    //完成时的矩阵
    Matrix origin_matrix;
    //方向通过value 追踪pos位置
    std::vector<Pos> value_index;
    Pos null_pos;
    static constexpr int null_value = 0;
};

typedef std::vector<Board::Direction> MoveList;

#endif // BOARD_H
