#include "board.h"
#include "board_api.h"

Board::Board(const Matrix &m)
{
    std::tie(origin_matrix, origin_value_index) = Board_API::build_origin(m.row_size(), m.col_size());
    matrix = m;
    value_index = Board_API::build_index(matrix);
}

void Board::gen()
{
    value_index = Board_API::gen(&matrix);
}

void Board::resize(int row, int col)
{
    std::tie(origin_matrix, origin_value_index) = Board_API::build_origin(row, col);
    matrix = origin_matrix;
    value_index = origin_value_index;
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
    return value_index.at(Board_API::null_value);
}

Matrix::value_type Board::pos_value(Pos p) const
{
    return matrix.get(p);
}

Pos Board::value_pos(Matrix::value_type value) const
{
    return value_index.at(value);
}

Pos Board::origin_pos(Matrix::value_type val) const
{
    return origin_value_index.at(val);
}

Matrix::value_type Board::origin_value(Pos p) const
{
    return origin_matrix.get(p);
}

bool Board::isDone() const
{
    return Board_API::isDone(matrix);
}
