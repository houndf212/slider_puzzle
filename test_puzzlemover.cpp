#include "puzzle_mover.h"
#include "boardgen.h"

void test_puzzlemover()
{
    Board board;
    board.gen(10, 10);
    BoardGen::gen(&board);

    PuzzleMover::solve(board);
}
