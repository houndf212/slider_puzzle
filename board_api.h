#ifndef BOARD_API_H
#define BOARD_API_H
#include "matrix.h"
#include "movedirection.h"
//这个类来完成board的操作，目的是达到操作最少

class Board_API
{
public:
    static constexpr Matrix::value_type start_value = 1;
    static constexpr Matrix::value_type null_value = 0;

    static PosVector build_index(const Matrix &m);
public:
    static void move(Pos *p, Direction d);

    static PosVector gen(Matrix* board);

    static bool isDone(const Matrix &m);

    static Pos get_null_pos(const Matrix &m);

    static Direction direction_to(Pos from, Pos to);
    static bool hint_null_move(Matrix *m, Pos null_hint, Direction d);

    //用于 boardgraph
    //返回从 m1 到 m2 的移动方向
    static Direction get_direction(const Matrix &m1, const Matrix &m2);
    static bool check_next(const Matrix &m1, const Matrix &m2);
private:
};

#endif // BOARD_API_H
