#include "puzzle_mover.h"
#include <QtCore>

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
        assert(board.can_solve(ml));
    }
    qDebug() << "slapsed msec: "<<timer.elapsed();
}
