#include "board.h"
#include "board_api.h"
#include "boardgen.h"

Board::Board(const Matrix &m)
{
    std::tie(origin_matrix, origin_value_index) = Board_API::build_origin(m.row_size(), m.col_size());
    matrix = m;
    value_index = Board_API::build_index(matrix);
    null_pos = value_index.at(null_value);
}

void Board::gen()
{
    BoardGen::gen(&matrix);
    value_index = Board_API::build_index(matrix);
    null_pos = value_index[null_value];
}

void Board::resize(int row, int col)
{
    std::tie(origin_matrix, origin_value_index) = Board_API::build_origin(row, col);
    matrix = origin_matrix;
    value_index = origin_value_index;
    null_pos = value_index.at(null_value);
}

bool Board::null_move(Direction d)
{
    bool b = Board_API::hint_null_move(&matrix, null_pos, d);
    if (b) {
        Pos old_null = null_pos;
        Board_API::move(&null_pos, d);
        assert(matrix.get(null_pos) == null_value);
        //更新索引
        value_index[null_value] = null_pos;
        value_index[matrix.get(old_null)] = old_null;
    }
    return b;
}

Direction Board::test_null_move_to(Pos p) const
{
    return Board_API::hint_test_null_move_to(matrix, null_pos, p);
}

int Board::pos_value(Pos p) const
{
    return matrix.get(p);
}

Pos Board::value_pos(int value) const
{
    return value_index.at(value);
}

Pos Board::origin_pos(int val) const
{
    return origin_value_index.at(val);
}

int Board::origin_value(Pos p) const
{
    return origin_matrix.get(p);
}

bool Board::isDone() const
{
    return Board_API::isDone(matrix);
}
