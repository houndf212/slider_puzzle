#include "matrixgraph.h"
#include "matrix.h"

constexpr int ROW = 10;
constexpr int COL = 10;
typedef MatrixGraph<int> MG;
typedef Dijkstra<MG> G;

void test_astar()
{
    BoolMatrix m;
    m.resize(ROW, COL);
    m.set_all_has();

    m.set_not({0, 1});
    m.set_not({1, 1});
    m.set_not({1, 2});
    m.set_not({2, 1});
    m.set_not({3, 1});
    m.print();

    m.set_not({3, 0});

    MG g(m);
    auto p = G::AStart_path(g, Pos(0, 0), Pos(0, 2));
    qDebug() << "path: "<<QList<Pos>::fromStdList(p.first);
    qDebug() << "dist: " << p.second;
}
