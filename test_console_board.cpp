#include <iostream>
#include "board.h"
#include "boardrotator.h"
#include "debug_output.h"
using namespace std;

void test_consoleboard()
{
    Board m;
    m.resize(5, 5);
    m.gen();
    bool b = true;
    while (b) {
        print(m);
        qDebug() << "input: ";
        char c;
        cin>>c;
        switch (c) {
        case 'w':
            m.null_move(Direction::Null_Down);
            break;
        case 's':
            m.null_move(Direction::Null_Up);
            break;
        case 'a':
            m.null_move(Direction::Null_Right);
            break;
        case 'd':
            m.null_move(Direction::Null_Left);
            break;

        default:
            b = false;
            break;
        }
    }
}
