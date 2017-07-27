#include "boardgen.h"
#include "board_api.h"
#include "puzzle_mover.h"

static bool check_solve(Board board, const MoveList &ml)
{
    for (auto d : ml) {
        if (!board.null_move(d))
            return false;
    }
    return board.isDone();
}

void test_gen()
{
// 2*2 -> 10*10;

    for (int row=2; row<=10; ++row) {
        for (int col=2; col<=10; ++col) {

            Board b;
            b.resize(row, col);

            int k = 1000;
            while (k-->0) {
                b.gen();

                MoveList ml = PuzzleMover::solve(b);
                bool bt = check_solve(b, ml);
                assert(bt);
            }
            qDebug() << "finish: "<<row<<":"<<col;
        }
    }
}
