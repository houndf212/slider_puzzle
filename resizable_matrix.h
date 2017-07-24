#ifndef RESIZABLE_MATRIX_H
#define RESIZABLE_MATRIX_H

#include <vector>
#include <assert.h>
#include "pos.h"

#include <QVector>

template <class T>
class Resizable_Matrix
{
public:
    void resize(int row, int col)
    {
        std::vector<T> vec(col, T());
        m = std::vector<std::vector<T>>(row, vec);
        n_row = row;
        n_col = col;
    }

    int row_size() const { return n_row; }
    int col_size() const { return n_col; }

    T get(Pos p) const
    {
        assert(isInMatrix(p));
        return m[p.row()][p.col()];
    }

    void set(Pos p, T val)
    {
        assert(isInMatrix(p));
        m[p.row()][p.col()] = val;
    }

    void fill_all(T val)
    {
        for (auto& v : m)
            std::fill(begin(v), end(v), val);
    }

    bool isInMatrix(Pos p) const
    {
        return 0<=p.row() && p.row()<row_size()
                && 0<=p.col() && p.col()<col_size();
    }

    bool equal(const Resizable_Matrix& m) const
    {
        return row_size() == m.row_size() &&
                col_size() == m.col_size() &&
                this->m == m.m;
    }
    bool less(const Resizable_Matrix& m) const
    {
        assert(row_size() == m.row_size());
        assert(col_size() == m.col_size());
        return this->m < m.m;
    }
private:
    std::vector<std::vector<T>> m;
    int n_row;
    int n_col;
};

template<class T>
bool operator <(const Resizable_Matrix<T>& m1, const Resizable_Matrix<T>& m2)
{
    return m1.less(m2);
}

#endif // RESIZABLE_MATRIX_H
