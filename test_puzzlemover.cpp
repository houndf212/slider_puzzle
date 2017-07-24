#include "puzzle_mover.h"
#include "boardgen.h"
#include <QtCore>
#include <iostream>
#include "boardgraph.h"

typedef BoardGraph<int> BG;

static bool check_solve(Board board, const MoveList &ml)
{
    for (auto d : ml) {
        bool b = board.null_move(d);
        assert(b==true);
    }
    return board.isDone();
}

void test_puzzlemover()
{
    QElapsedTimer timer;
    timer.start();
    int i=1;
    while (i-->0) {
        qDebug() << "round: "<<i;
        Board board;
        board.gen(4, 4);
        BoardGen::gen(&board);
//        board.print();
        auto ml = PuzzleMover::solve(board);
        auto mlst = BG::toMatrixList(ml, board.inner_matrix());
        for (const auto &m : mlst) {
            std::cout<<BG::heuristic(m, board.inner_origin_matrix())<<",";
        }
        std::cout<<std::endl;
//        qDebug() <<"move steps: " <<ml.size();
        assert(check_solve(board, ml));
    }
    qDebug() << "slapsed msec: "<<timer.elapsed();
}
