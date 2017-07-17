#include "board.h"
#include "boardgen.h"
#include "boolmatrix.h"
#include "numbermover.h"
#include <iostream>
using namespace std;

void test_numbermover()
{
    Board board;
    board.gen(5, 5);
    BoardGen::gen(&board);


    BoolMatrix fixed;
    fixed.resize(5, 5);
    fixed.set_all_unfixed();
    fixed.set_fixed({0, 2});
    fixed.set_fixed({1, 2});
    fixed.set_fixed({2, 2});
    fixed.set_fixed({2, 1});
    fixed.set_fixed({2, 0});

    while (true) {
        board.print();
        qDebug() << "input value:";
        int value;
        cin >> value;
        NumberMover mover(board, fixed);
        auto path = mover.get_move_line(value);
        if (path.second == true) {
            qDebug() << QVector<Pos>::fromStdVector(path.first);
        }
        else {
            qDebug() << "cannot reach!";
        }
    }

}
