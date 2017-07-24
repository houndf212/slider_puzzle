#include "board.h"
#include <QtCore>

Board::Board(const Matrix &m)
{
    build_origin(m.row_size(), m.col_size());
    matrix = m;
    value_index.resize(matrix.row_size()*matrix.col_size());

    for (int row=0; row<matrix.row_size(); ++row) {
        for (int col=0; col<matrix.col_size(); ++col) {
            Pos p(row, col);
            int val = matrix.get(p);
            value_index[val] = p;
        }
    }
    null_pos = value_index.at(null_value);
}

void Board::gen(int row, int col)
{
    init_matrix(row, col);
}

bool Board::null_move(Board::Direction d)
{
    switch (d) {
    case Null_Up:
        return inner_null_move(-1, 0);
        break;
    case Null_Down:
        return inner_null_move(1, 0);
        break;
    case Null_Left:
        return inner_null_move(0, -1);
        break;
    case Null_Right:
        return inner_null_move(0, 1);
        break;
    default:
        assert(false);
        break;
    }
    assert(false);
    return false;
}

Board::Direction Board::test_null_move_to(Pos p) const
{
    assert(matrix.isInMatrix(p));
    int drow = p.row() - null_pos.row();
    int dcol = p.col() - null_pos.col();
    if (drow == 0) {
        if (dcol == 1)
            return Null_Right;
        else if (dcol == -1)
            return Null_Left;
    }
    else if (dcol == 0) {
        if (drow == 1)
            return Null_Down;
        else if (drow == -1)
            return Null_Up;
    }
    return NotValid;
}

int Board::pos_value(Pos p) const
{
    return matrix.get(p);
}

Pos Board::value_pos(int value) const
{
    assert(0<=value && value<int(value_index.size()));
    return value_index[value];
}

Pos Board::origin_pos(int val) const
{
    assert(0<=val && val<int(origin_value_index.size()));
    return origin_value_index[val];
}

int Board::origin_value(Pos p) const
{
    return origin_matrix.get(p);
}

bool Board::isDone() const
{
    return matrix.equal(origin_matrix);
}

void Board::init_matrix(int row, int col)
{
    build_origin(row, col);
    matrix = origin_matrix;
    value_index = origin_value_index;
}

bool Board::inner_null_move(int dr, int dc)
{
    assert(dr==0 || dc==0);
    assert(dr==1 || dr==-1 || dc==1 || dc==-1);
    Pos p = null_pos;
    p.row() += dr;
    p.col() += dc;

    if (!matrix.isInMatrix(p))
        return false;

    swap_null(p);
    return true;
}

void Board::swap_null(Pos p)
{
    int v = matrix.get(p);
    assert(matrix.get(null_pos)==null_value);
    matrix.set(null_pos, v);
    value_index[v] = null_pos;
    matrix.set(p, null_value);
    value_index[null_value] = p;
    null_pos = p;
}

void Board::build_origin(int row, int col)
{
    origin_matrix.resize(row, col);
    origin_value_index.resize(row*col+1);
    int n = 1;
    for (int r=0; r<row; ++r) {
        for (int c=0; c<col; ++c) {
            Pos p(r, c);
            origin_matrix.set(p, n);
            origin_value_index[n] = p;
            ++n;
        }
    }

    null_pos.row() = origin_matrix.row_size() - 1;
    null_pos.col() = origin_matrix.col_size() - 1;

    origin_matrix.set(null_pos, null_value);
    origin_value_index[null_value] = null_pos;
}
