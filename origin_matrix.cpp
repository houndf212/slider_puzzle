#include "origin_matrix.h"

Origin_Matrix::Origin_Matrix(int row, int col)
{
    assert(row*col < std::numeric_limits<Matrix::value_type>::max());
    m_matrix.resize(row, col);
    m_value_index.resize(row*col+1);

    Matrix::value_type n = Board_API::start_value;
    for (int r=0; r<row; ++r) {
        for (int c=0; c<col; ++c) {
            Pos p(r, c);
            m_matrix.set(p, n);
            m_value_index[n] = p;
            ++n;
        }
    }

    Pos null_pos(m_matrix.row_size() - 1,
                 m_matrix.col_size() - 1);

    m_matrix.set(null_pos, Board_API::null_value);
    m_value_index[Board_API::null_value] = null_pos;
    m_value_index.pop_back();
}
