#ifndef NUMBERMOVER_H
#define NUMBERMOVER_H
#include "board.h"
#include "boolmatrix.h"

class NumberMover
{
public:
    // 将0 移动到指定位置，如果成功，board会被修改，否则不会修改
    static std::pair<MoveList, bool>
    find_null_to(Pos to, Board* board, BoolMatrix fixed);

    static std::pair<MoveList, bool>
    find_moves(int val, Board board, BoolMatrix fixed_matrix);
private:
    static std::pair<PosList, bool>
    find_move_line(Pos start, Pos finish, const BoolMatrix &fixed_matrix);
};

#endif // NUMBERMOVER_H
