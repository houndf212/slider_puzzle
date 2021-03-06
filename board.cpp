﻿#include "board.h"
#include "board_api.h"

void Board::clone(const Board &b)
{
    matrix = b.matrix;
    value_index = b.value_index;
    origin_matrix = b.origin_matrix;
}

Board::Board(const Matrix &m)
{
    origin_matrix.reset(new Origin_Matrix(m.row_size(), m.col_size()));
    matrix = m;
    value_index = Board_API::build_index(matrix);
}

void Board::gen()
{
    value_index = Board_API::gen(&matrix);
}

void Board::resize(int row, int col)
{
    origin_matrix.reset(new Origin_Matrix(row, col));
    matrix = origin_matrix->matrix();
    value_index = origin_matrix->index();
}

bool Board::null_move(Direction d)
{
    assert(d != Direction::NotValid);
    Pos null_pos = get_null_pos();
    bool b = Board_API::hint_null_move(&matrix, null_pos, d);
    if (b) {
        //更新索引
        auto val = matrix.get(null_pos);
        std::swap(value_index[Board_API::null_value], value_index[val]);
    }
    return b;
}

Direction Board::test_null_move_to(Pos p) const
{
    assert(matrix.isInMatrix(p));
    return Board_API::direction_to(get_null_pos(), p);
}

Pos Board::get_null_pos() const
{
    assert(value_index.size() > Board_API::null_value+1);
    return value_index[Board_API::null_value];
}

Matrix::value_type Board::pos_value(Pos p) const
{
    return matrix.get(p);
}

Pos Board::value_pos(Matrix::value_type value) const
{
    assert(value_index.size()>size_t(value));
    return value_index[value];
}

Pos Board::origin_pos(Matrix::value_type val) const
{
    assert(origin_matrix);
    return origin_matrix->pos(val);
}

Matrix::value_type Board::origin_value(Pos p) const
{
    assert(origin_matrix);
    return origin_matrix->value(p);
}

bool Board::isDone() const
{
    return Board_API::isDone(matrix);
}

bool Board::can_solve(const MoveList &ml) const
{
    Board board;
    board.clone(*this);
    for (auto d : ml) {
        if (!board.null_move(d))
            return false;
    }
    return board.isDone();
}
