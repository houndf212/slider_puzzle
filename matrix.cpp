#include "matrix.h"
using std::vector;

#include <QtCore>

Matrix::Matrix(int row, int col)
{
    resize(row, col);
}

void Matrix::resize(int row, int col)
{
    vector<int> vec(col, 0);
    m = vector<vector<int>>(row, vec);
    n_row = row;
    n_col = col;
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
    return 0<=p.row() && p.row()<n_row && 0<=p.col() && p.col()<n_col;
}
