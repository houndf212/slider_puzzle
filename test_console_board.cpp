#include <iostream>
#include "board.h"
#include "boardgen.h"
#include "boardrotator.h"
#include "debug_output.h"
using namespace std;

void test_consoleboard()
{
    Board m;
    m.gen(5, 5);
    BoardGen::gen(&m);
    bool b = true;
    while (b) {
        print(m);
        qDebug() << "input: ";
        char c;
        cin>>c;
        switch (c) {
        case 'w':
            m.null_move(Board::Null_Down);
            break;
        case 's':
            m.null_move(Board::Null_Up);
            break;
        case 'a':
            m.null_move(Board::Null_Right);
            break;
        case 'd':
            m.null_move(Board::Null_Left);
            break;

        default:
            b = false;
            break;
        }
    }
}
