#include "board_api.h"

std::pair<Matrix, PosVector> Board_API::build_origin(int row, int col)
{
    assert(row*col < std::numeric_limits<Matrix::value_type>::max());
    Matrix origin_matrix;
    origin_matrix.resize(row, col);

    PosVector origin_value_index;
    origin_value_index.resize(row*col+1);

    Matrix::value_type n = 1;
    for (int r=0; r<row; ++r) {
        for (int c=0; c<col; ++c) {
            Pos p(r, c);
            origin_matrix.set(p, n);
            origin_value_index[n] = p;
            ++n;
        }
    }

    Pos null_pos(origin_matrix.row_size() - 1,
                 origin_matrix.col_size() - 1);

    origin_matrix.set(null_pos, null_value);
    origin_value_index[null_value] = null_pos;
    origin_value_index.pop_back();
    return std::make_pair(origin_matrix, origin_value_index);
}

PosVector Board_API::build_index(const Matrix &m)
{
    PosVector value_index;
    value_index.resize(m.row_size()*m.col_size());

    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            int val = m.get(p);
            assert(0<=val && size_t(val)<value_index.size());
            value_index[val] = p;
        }
    }
    return value_index;
}

void Board_API::move(Pos *p, Direction d)
{
    switch (d) {
    case Direction::Null_Up:
        p->row()--;
        break;
    case Direction::Null_Down:
        p->row()++;
        break;
    case Direction::Null_Left:
        p->col()--;
        break;
    case Direction::Null_Right:
        p->col()++;
        break;
    default:
        assert(false);
        break;
    }
}

bool Board_API::isDone(const Matrix &m)
{
    int n=0;
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            n++;
            Pos p(row, col);
            int val = m.get(p);
            if (val!=0 && val!=n)
                return false;
        }
    }
    return true;
}

Pos Board_API::get_null_pos(const Matrix &m)
{
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            if (m.get(p) == null_value)
                return p;
        }
    }
    assert(false);
    return Pos(-1, -1);
}

Direction Board_API::direction_to(Pos from, Pos to)
{
    int drow = to.row() - from.row();
    int dcol = to.col() - from.col();
    if (drow == 0) {
        if (dcol == 1)
            return Direction::Null_Right;
        else if (dcol == -1)
            return Direction::Null_Left;
    }
    else if (dcol == 0) {
        if (drow == 1)
            return Direction::Null_Down;
        else if (drow == -1)
            return Direction::Null_Up;
    }
    return Direction::NotValid;
}

bool Board_API::hint_null_move(Matrix *m, Pos null_hint, Direction d)
{
    assert(get_null_pos(*m) == null_hint);
    Pos to = null_hint;
    move(&to, d);
    if (!m->isInMatrix(to))
        return false;

    int val = m->get(to);
    m->set(null_hint, val);
    m->set(to, null_value);
    return true;
}

Direction Board_API::get_direction(const Matrix &m1, const Matrix &m2)
{
    Pos p1 = get_null_pos(m1);

    {
        const Direction &d = Direction::Null_Up;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }

    {
        const Direction &d = Direction::Null_Down;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }

    {
        const Direction &d = Direction::Null_Right;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }

    {
        const Direction &d = Direction::Null_Left;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }
    return Direction::NotValid;
}

bool Board_API::check_next(const Matrix &m1, const Matrix &m2)
{
    return get_direction(m1, m2) != Direction::NotValid;
}
