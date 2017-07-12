#include <QApplication>
#include <QtCore>
#include "board.h"
#include "boardgen.h"
#include <iostream>
using namespace std;

#include "gamewindow.h"

void test()
{
    Board m;
    m.gen(5, 5);
    BoardGen::gen(&m);
    bool b = true;
    while (b) {
        m.print();
        qDebug() << "input: ";
        char c;
        cin>>c;
        switch (c) {
        case 'w':
            m.move(Board::Up);
            break;
        case 's':
            m.move(Board::Down);
            break;
        case 'a':
            m.move(Board::Left);
            break;
        case 'd':
            m.move(Board::Right);
            break;
        default:
            b = false;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
