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

    // alias api
    void set_all_unfixed() { fill_all(K_Unfixed); }
    void set_fixed(Pos p) { assert(!fixed(p)); set(p, K_Fixed); }
    bool fixed(Pos p) const { return get(p) == K_Fixed; }
private:
    static constexpr bool k_Has = true;
    static constexpr bool K_Not = false;

    static constexpr bool K_Fixed = K_Not;
    static constexpr bool K_Unfixed = k_Has;
};

#endif // BOOLMATRIX_H
