#include "numbermover.h"
MoveList NumberMover::find_null_move_list(int val, const Board &b, const BoolMatrix &fixed)
{
    value = val;
    board = b;
    fixedMatrix = fixed;
}

