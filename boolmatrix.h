#ifndef BOOLMATRIX_H
#define BOOLMATRIX_H
#include "resizable_matrix.h"

class BoolMatrix : public Resizable_Matrix<bool>
{
public:
    BoolMatrix() = default;
    // use to matrixgraph
    void set_all_has() { fill_all(k_Has); }
    void set_not(Pos p) { set(p, K_Not); }
    bool has(Pos p) const { return get(p) == k_Has; }

    // alias api
    void set_all_unfixed() { fill_all(K_Unfixed); }
    void set_fixed(Pos p) { assert(!fixed(p)); set(p, K_Fixed); }
    bool fixed(Pos p) const { return get(p) == K_Fixed; }
private:
    friend class temp_fixer;
    void set_unfixed(Pos p) { assert(fixed(p)); set(p, K_Unfixed); }
    BoolMatrix(const BoolMatrix&) = delete;
    BoolMatrix(BoolMatrix&&) = delete;
    BoolMatrix& operator=(const BoolMatrix& ) = delete;
    BoolMatrix& operator=(BoolMatrix&& ) = delete;
private:
    static constexpr bool k_Has = true;
    static constexpr bool K_Not = false;

    static constexpr bool K_Fixed = K_Not;
    static constexpr bool K_Unfixed = k_Has;
};

//临时锁定pos，减少 boolmatrix的复制
class temp_fixer
{
public:
    temp_fixer(const Pos &p, BoolMatrix& fixed)
        :m_p(p), fixed_matrix(fixed)
    {
        assert(!fixed_matrix.fixed(p));
        fixed_matrix.set_fixed(m_p);
    }
    void unfix() const
    {
        if (fixed_matrix.fixed(m_p))
            fixed_matrix.set_unfixed(m_p);
    }
    ~temp_fixer()
    {
        unfix();
    }
private:
    const Pos m_p;
    BoolMatrix& fixed_matrix;
};

#endif // BOOLMATRIX_H
