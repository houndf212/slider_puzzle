#include "board.h"
#include <QtCore>

Board::Board()
    :m(3, 3)
{
    gen(3, 3);
}

void Board::gen(int row, int col)
{
    m.resize(row, col);
    value_index.resize(row*col+1);
    init_matrix();
}

bool Board::move(Board::Direction d)
{
    switch (d) {
    case Down:
        return move(-1, 0);
        break;
    case Up:
        return move(1, 0);
        break;
    case Right:
        return move(0, -1);
        break;
    case Left:
        return move(0, 1);
        break;
    default:
        assert(false);
        break;
    }
    assert(false);
    return false;
}

bool Board::move_pos(Pos p)
{
    assert(m.isInMatrix(p));
    int drow = p.row() - null_pos.row();
    int dcol = p.col() - null_pos.col();

    if ((drow == 0 && (dcol == 1 || dcol == -1)) ||
            (dcol == 0 && (drow == 1 || drow == -1))) {
            move(drow, dcol);
            return true;
    }
    return false;
}

int Board::pos_value(Pos p) const
{
    return m.get(p);
}

Pos Board::value_pos(int value) const
{
    assert(0<=value && value<int(value_index.size()));
    return value_index[value];
}

void Board::print() const
{
    return m.print();
}

bool Board::isDone() const
{
    int n=1;
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            int val = m.get(Pos(row, col));
            // null must at n=row*col also the end
            if (val!=n++ && val!=null_value) {
                return false;
            }
        }
    }
    return true;
}

void Board::init_matrix()
{
    int n = 1;
    int row = m.row_size();
    int col = m.col_size();
    for (int r=0; r<row; ++r) {
        for (int c=0; c<col; ++c) {
            Pos p(r, c);
            m.set(p, n);
            value_index[n] = p;
            ++n;
        }
    }

    null_pos.row() = row - 1;
    null_pos.col() = col - 1;
    m.set(null_pos, null_value);
}

bool Board::move(int dr, int dc)
{
    Pos p = null_pos;
    p.row() += dr;
    p.col() += dc;

    if (!m.isInMatrix(p))
        return false;

    swap_null(p);
    return true;
}

void Board::swap_null(Pos p)
{
    int v = m.get(p);
    int nll = m.get(null_pos);
    m.set(null_pos, v);
    value_index[v] = null_pos;
    m.set(p, nll);
    value_index[nll] = p;
    null_pos = p;
    qDebug() << isDone();
}
