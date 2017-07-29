#ifndef BOARD_H
#define BOARD_H
#include "matrix.h"
#include "movelist.h"

class Board
{
public:
    Board() = default;

    Board(const Board &) = delete;
    Board &operator=(const Board &) = delete;
    void clone(const Board &b);

    Board(const Matrix &m);

    void gen();
    void resize(int row, int col);

    bool null_move(Direction d);

    Direction test_null_move_to(Pos p) const;

    Pos get_null_pos() const;

    Matrix::value_type pos_value(Pos p) const;
    Pos value_pos(Matrix::value_type value) const;

    Pos origin_pos(Matrix::value_type val) const;
    Matrix::value_type origin_value(Pos p) const;

    bool isDone() const;

    bool can_solve(const MoveList &ml) const;

    bool isInBoard(Pos p) const { return matrix.isInMatrix(p); }
    int row_size() const { return matrix.row_size(); }
    int col_size() const { return matrix.col_size(); }

    const Matrix &inner_matrix() const { return matrix; }
    const Matrix &inner_origin_matrix() const { return origin_matrix; }
private:
    Matrix matrix;
    //方向通过value 追踪pos位置
    std::vector<Pos> value_index;

    //完成时的矩阵
    Matrix origin_matrix;
    //完成时应该的位置
    std::vector<Pos> origin_value_index;
};

#include "movelist.h"

#endif // BOARD_H
