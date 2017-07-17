#include <QApplication>
#include "gamewindow.h"


void run_test()
{
    extern void test_consoleboard();
    extern void test_numbermover();
//    test_consoleboard();

    test_numbermover();
}

int main(int argc, char *argv[])
{
    run_test();
    return 0;
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
