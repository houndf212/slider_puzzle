#ifndef POS_H
#define POS_H
#include <QPoint>

class Pos
{
public:
    Pos(int row=0, int col=0) : m_row(row), m_col(col) {}
    int row() const { return m_row; }
    int col() const { return m_col; }
    int& row() { return m_row; }
    int& col() { return m_col; }
    bool equal(const Pos& p) const
    {
        return m_row == p.row() && m_col == p.col();
    }
private:
    int m_row;
    int m_col;
};

#endif // POS_H
