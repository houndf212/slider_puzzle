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
    MatrixGraph g(m);

    auto p = g.dijkstra_shortest_path({0, 0}, {0, 2});
    qDebug() << QVector<Pos>::fromStdVector(p.first);
    qDebug() << "dist: " << p.second;
}
