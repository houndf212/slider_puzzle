#ifndef MOVERPARAM_H
#define MOVERPARAM_H
#include "board.h"
#include "boolmatrix.h"

class MoverParam
{
public:
    MoverParam(const Board &b);
    Board board;
    BoolMatrix fixed_matrix;
    MoveList move_list;
};

#endif // MOVERPARAM_H
