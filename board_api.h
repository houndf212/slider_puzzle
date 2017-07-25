#ifndef BOARD_API_H
#define BOARD_API_H
#include "matrix.h"
#include "movedirection.h"
//这个类来完成board的操作，目的是达到操作最少

class Board_API
{
public:
    static constexpr int null_value = 0;

    static std::pair<Matrix, PosVector> build_origin(int row, int col);
    static PosVector build_index(const Matrix &m);
public:
    static void move(Pos *p, Direction d);

    static void gen(Matrix* m, int row, int col);

    static bool isDone(const Matrix &m);

    static Pos get_null_pos(const Matrix &m);

    static Direction hint_test_null_move_to(const Matrix &m, Pos null_hint, Pos p);
    static bool hint_null_move(Matrix *m, Pos null_hint, Direction d);

    //用于 boardgraph
    //返回从 m1 到 m2 的移动方向
    static Direction get_direction(const Matrix &m1, const Matrix &m2);
    static bool check_next(const Matrix &m1, const Matrix &m2);
private:
};

#endif // BOARD_API_H
