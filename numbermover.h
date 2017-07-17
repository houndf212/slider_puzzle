#ifndef NUMBERMOVER_H
#define NUMBERMOVER_H
#include "board.h"
#include "boolmatrix.h"

class NumberMover
{
public:
    MoveList find_null_move_list(int val, const Board &b, const BoolMatrix &fixedMatrix);
private:
    int value;
    Board board;
    BoolMatrix fixedMatrix;
};

#endif // NUMBERMOVER_H
