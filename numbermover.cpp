#include "numbermover.h"
MoveList NumberMover::find_null_move_list(int val, const Board &b)
{
    value = val;
    board = b;
}

MatrixGraph NumberMover::get_the_graph(Pos to, int row, int col)
{
    MatrixGraph g;
    g.resize(row, col);
}
