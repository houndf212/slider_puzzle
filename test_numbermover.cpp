#include "board.h"
#include "boardgen.h"
#include "boolmatrix.h"
#include "numbermover.h"
#include "moverparam.h"
#include <iostream>
using namespace std;

void test_numbermover()
{
    Board orgin_board;
    orgin_board.gen(5, 5);
    BoardGen::gen(&orgin_board);


    MoverParam param(orgin_board);

    while (true) {
        param.board.print();
        qDebug() << "input command:";
        char c;
        cin >> c;
        switch (c) {
        case 'm':
        {
            int value;
            cin >> value;

            bool path = NumberMover::find_value_moves(value, &param);
            if (path == true) {
                qDebug() << QList<Board::Direction>::fromStdList(param.move_list);
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
            param.fixed_matrix.set_fixed(p);
            param.fixed_matrix.print();
        }
            break;

        case 'w':
            param.board.null_move(Board::Null_Down);
            break;
        case 's':
            param.board.null_move(Board::Null_Up);
            break;
        case 'a':
            param.board.null_move(Board::Null_Right);
            break;
        case 'd':
            param.board.null_move(Board::Null_Left);
            break;
        default:
            break;
        }

    }

}
