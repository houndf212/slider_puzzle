#include "matrix.h"
using std::vector;

#include <QtCore>

void Matrix::resize(int row, int col)
{
    vector<int> vec(col, 0);
    m = vector<vector<int>>(row, vec);
    n_row = row;
    n_col = col;
}

void Matrix::fill_all(int val)
{
    for (auto& v : m)
        std::fill(begin(v), end(v), val);
}

void Matrix::print() const
{
    // use qvector
    for (const auto& v : m)
    {
        qDebug() << QVector<int>::fromStdVector(v);
    }
    qDebug() << "";
}

bool Matrix::isInMatrix(Pos p) const
{
    return 0<=p.row() && p.row()<row_size() && 0<=p.col() && p.col()<col_size();
}

bool Matrix::equal(const Matrix &m) const
{
    if (row_size() != m.row_size() ||
            col_size() != m.col_size())
        return false;

    for (int row=0; row<row_size(); ++row) {
        for (int col=0; col<col_size(); ++col) {
            Pos p(row, col);
            if (get(p)!=m.get(p)) {
                return false;
            }
        }
    }
    return true;
}
