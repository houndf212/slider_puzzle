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
//    fixed.set_fixed({0, 2});
//    fixed.set_fixed({1, 2});
//    fixed.set_fixed({2, 2});
//    fixed.set_fixed({2, 1});
//    fixed.set_fixed({2, 0});

    while (true) {
        board.print();
        qDebug() << "input command:";
        char c;
        cin >> c;
        switch (c) {
        case 'm':
        {
            int value;
            cin >> value;

            auto path = NumberMover::find_value_moves(value, &board, fixed);
            if (path.second == true) {
                qDebug() << QList<Board::Direction>::fromStdList(path.first);
            }
            else {
                qDebug() << "cannot reach!";
            }
        }
            break;
        case 'f':
        {
            int row, col;
            cin >> row >> col;
            Pos p(row, col);
            fixed.set_fixed(p);
            fixed.print();
        }
            break;

        case 'w':
            board.null_move(Board::Null_Down);
            break;
        case 's':
            board.null_move(Board::Null_Up);
            break;
        case 'a':
            board.null_move(Board::Null_Right);
            break;
        case 'd':
            board.null_move(Board::Null_Left);
            break;
        default:
            break;
        }

    }

}
