#include "puzzle_mover.h"
#include "boardgen.h"
#include <QtCore>

static bool check_solve(Board board, const MoveList &ml)
{
    for (auto d : ml) {
        if (!board.null_move(d))
            return false;
    }
    return board.isDone();
}

void test_puzzlemover()
{
    QElapsedTimer timer;
    timer.start();
    int i=100;
    while (i-->0) {
        qDebug() << "round: "<<i;
        Board board;
        board.resize(30, 30);
        board.gen();
//        board.print();
        auto ml = PuzzleMover::solve(board);
//        qDebug() <<"move steps: " <<ml.size();
        assert(check_solve(board, ml));
    }
    qDebug() << "slapsed msec: "<<timer.elapsed();
}
