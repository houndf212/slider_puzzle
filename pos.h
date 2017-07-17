#ifndef POS_H
#define POS_H
#include <vector>
#include <queue>

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
        return row() == p.row() && col() == p.col();
    }
private:
    int m_row;
    int m_col;
};

inline bool operator==(const Pos &p1, const Pos &p2)
{
    return p1.equal(p2);
}

inline QDebug operator<<(QDebug d, const Pos &p)
{
    d<<"("<<p.row()<<", "<<p.col()<<")";
    return d;
}

typedef std::vector<Pos> PosList;
typedef std::queue<Pos> PosQueue;

#endif // POS_H
