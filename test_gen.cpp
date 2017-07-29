#include "board_api.h"
#include "puzzle_mover.h"

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
                assert(b.can_solve(ml));
            }
            qDebug() << "finish: "<<row<<":"<<col;
        }
    }
}
