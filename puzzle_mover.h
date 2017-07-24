#ifndef PUZZLE_MOVER_H
#define PUZZLE_MOVER_H
#include "moverparam.h"

class PuzzleMover
{
public:
    static MoveList search_solve(const Board& b);
    static MoveList solve(const Board& origin_board);
private:
    static bool check_solve(MoverParam* param);
    static std::list<PosList> get_move_lines(const Board &board);
    static bool check_loop(const MoveList &mlst);
};

#endif // PUZZLE_MOVER_H
