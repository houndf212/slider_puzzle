#include "board.h"
#include "boolmatrix.h"
#include "numbermover.h"
#include "moverparam.h"
#include "debug_output.h"
#include <iostream>
using namespace std;

void test_numbermover()
{
    Board orgin_board;
    orgin_board.resize(5, 5);
    orgin_board.gen();


    MoverParam param(orgin_board);

    while (true) {
        print(param.board);
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
                print(param.move_list);
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
            print(param.fixed_matrix);
        }
            break;

        case 'w':
            param.board.null_move(Direction::Null_Down);
            break;
        case 's':
            param.board.null_move(Direction::Null_Up);
            break;
        case 'a':
            param.board.null_move(Direction::Null_Right);
            break;
        case 'd':
            param.board.null_move(Direction::Null_Left);
            break;
        default:
            break;
        }

    }

}
