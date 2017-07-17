#ifndef NUMBERMOVER_H
#define NUMBERMOVER_H
#include "board.h"
#include "boolmatrix.h"

class NumberMover
{
public:
    NumberMover(const Board &b, const BoolMatrix &fixed);
    std::pair<PosList, bool> get_move_line(int val) const;
    std::pair<PosList, bool> get_null_move_path(Pos to, Pos fixedPos) const;
    std::pair<MoveList, bool> get_all_null_move_path(int val) const;
private:
    const Board &board;
    const BoolMatrix &fixed_matrix;
private:
    static std::pair<PosList, bool>
    find_value_move_line(Pos start, Pos finish, const BoolMatrix &fixed_matrix);
};

#endif // NUMBERMOVER_H
