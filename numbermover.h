#ifndef NUMBERMOVER_H
#define NUMBERMOVER_H
#include "board.h"
#include "matrixgraph.h"

class NumberMover
{
public:
    MoveList find_null_move_list(int val, const Board &b);
    static MatrixGraph get_the_graph(Pos to, int row, int col);
private:
    int value;
    Board board;
};

#endif // NUMBERMOVER_H
