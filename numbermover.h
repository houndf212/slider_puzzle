#ifndef NUMBERMOVER_H
#define NUMBERMOVER_H
#include "moverparam.h"

class NumberMover
{
public:
    // 将0 移动到指定位置，如果成功，board会被修改，否则不会修改
    static bool find_null_to(Pos to, MoverParam *param);

    // warpper for find_moves
    static bool find_value_moves(int val, MoverParam *param);

    static bool find_moves(Pos start, Pos finish, MoverParam *param);
private:
    //核心函数，调用最短路径算法
    static std::pair<PosList, bool>
    core_move_line(Pos start, Pos finish, const BoolMatrix &fixed_matrix);
};

#endif // NUMBERMOVER_H
