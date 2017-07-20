#include "matrixgraph.h"

void test_matrixgraph()
{
    BoolMatrix m;
    m.resize(10, 10);
    m.set_all_has();

    m.set_not({0, 1});
    m.set_not({1, 1});
    m.set_not({1, 2});
    m.set_not({2, 1});
    m.set_not({3, 1});
    m.print();

    typedef MatrixGraph<int> MG;
    typedef Dijkstra<MG> G;
    MG g(m);
    auto p = G::dijkstra_shortest_path(g, Pos(0, 0), Pos(0, 2));
    auto p1 = G::dijkstra_shortest_path_all(g, Pos(0,0));
//    qDebug() << QVector<Pos>::fromStdVector(p.first);
    qDebug() << "dist: " << p.second;
}
