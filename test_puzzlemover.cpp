#include "puzzle_mover.h"
#include "boardgen.h"

bool check_solve(Board board, const MoveList &ml)
{
    for (auto d : ml) {
        bool b = board.null_move(d);
        assert(b==true);
    }
    return board.isDone();
}

void test_puzzlemover()
{
    int i=1;
    while (true) {
        qDebug() << "round: "<<i++;
        Board board;
        board.gen(5, 5);
        BoardGen::gen(&board);
//        board.print();
        auto ml = PuzzleMover::solve(board);
        qDebug() <<"move steps: " <<ml.size();
        assert(check_solve(board, ml));
    }
}
