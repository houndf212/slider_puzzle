#include <QApplication>
#include "gamewindow.h"


void run_test()
{
    extern void test_consoleboard();
    extern void test_numbermover();
    extern void test_linemover();
    extern void test_puzzlemover();
    extern void test_matrixgraph();
    extern void testEdgeGraphFile();
    testEdgeGraphFile();
    test_matrixgraph();
//    test_consoleboard();

//    test_numbermover();
//    test_linemover();
//    test_puzzlemover();
}

int main(int argc, char *argv[])
{
//    run_test();
//    return 0;
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
