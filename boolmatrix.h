#ifndef BOOLMATRIX_H
#define BOOLMATRIX_H
#include "resizable_matrix.h"

class BoolMatrix : public Resizable_Matrix<bool>
{
public:
    // use to matrixgraph
    void set_all_has() { fill_all(k_Has); }
    void set_not(Pos p) { set(p, K_Not); }
    bool has(Pos p) const { return get(p) == k_Has; }
private:
    static constexpr bool k_Has = true;
    static constexpr bool K_Not = false;
};

#endif // BOOLMATRIX_H
