#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <assert.h>
#include "pos.h"

class Matrix
{
public:
    Matrix(int row, int col);

    void resize(int row, int col);

    int row_size() const { return n_row; }
    int col_size() const { return n_col; }

    int get(Pos p) const
    {
        assert(isInMatrix(p));
        return m[p.row()][p.col()];
    }

    void set(Pos p, int val)
    {
        assert(isInMatrix(p));
        m[p.row()][p.col()] = val;
    }

    void fill_all(int val);

    void print() const;

    bool isInMatrix(Pos p) const;

    bool equal(const Matrix& m) const;
private:
    std::vector<std::vector<int>> m;
    int n_row;
    int n_col;
};

#endif // MATRIX_H
