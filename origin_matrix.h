#ifndef ORIGIN_MATRIX_H
#define ORIGIN_MATRIX_H
#include "matrix.h"
#include "board_api.h"

class Origin_Matrix
{
public:
    Origin_Matrix() = delete;
    Origin_Matrix(const Origin_Matrix &) = delete;
    Origin_Matrix &operator=(const Origin_Matrix &) = delete;

    Origin_Matrix(int row, int col);
    Matrix::value_type value(Pos p) const;
    Pos pos(Matrix::value_type val) const;
    const Matrix &matrix() const { return m_matrix; }
    const PosVector &index() const { return m_value_index; }
private:
    Matrix m_matrix;
    PosVector m_value_index;
};

inline Matrix::value_type Origin_Matrix::value(Pos p) const
{
    return m_matrix.get(p);
}

inline Pos Origin_Matrix::pos(Matrix::value_type val) const
{
    assert(0<=val && size_t(val)<m_value_index.size());
    return m_value_index[val];
}

#endif // ORIGIN_MATRIX_H
