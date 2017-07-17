#ifndef NUMBERMOVER_H
#define NUMBERMOVER_H
#include "board.h"

class NumberMover
{
public:
    NumberMover(const Board& b);
    MoveList find_move_list(int val, Pos p);
private:
    Board board;
};

#endif // NUMBERMOVER_H
