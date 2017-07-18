#ifndef PUZZLE_MOVER_H
#define PUZZLE_MOVER_H
#include "board.h"

class PuzzleMover
{
public:
    static MoveList solve(const Board& origin_board);
private:
    static std::list<PosList> get_move_lines(const Board &board);
};

#endif // PUZZLE_MOVER_H
