#ifndef NINESOLVER_H
#define NINESOLVER_H

#include <vector>

/*  zero is 9
 *  then  from left to right
 *  from up to done
 *
 *  ======
 *  2 3 1
 *  4 5 6
 *  8 7
 *  ======
 *   equal "2 3 1 4 5 6 8 7 0"
 */
class NineSolver
{
public:
    NineSolver();

    ~NineSolver();

    void buildAllStatus();

    bool solve(const uint8_t *curStatus) const;
private:

    void *m_statusData;
};


#endif // NINESOLVER_H
