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
    extern void test_astar();
    extern void test_search_board();
    extern void test_optimize_move();
    extern void test_gen();
    extern void test_check_loop();
//    test_check_loop();
//    testEdgeGraphFile();
//    test_matrixgraph();
//    test_consoleboard();

//    test_numbermover();
//    test_linemover();
//    test_puzzlemover();
//    test_astar();
//    test_search_board();
//    test_optimize_move();
//    test_gen();
}

int main(int argc, char *argv[])
{
//    run_test();
//    return 0;
    QApplication a(argc, argv);

    int cc = 100;
    GameWindow w;
    w.show();

    return a.exec();
}
