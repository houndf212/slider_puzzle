#include "matrixgraph.h"
#include "matrix.h"

constexpr int ROW = 10;
constexpr int COL = 10;
typedef MatrixGraph<int> MG;
typedef Dijkstra<MG> G;

void print_path(const std::pair<G::VertexList, G::distance_t>& p)
{
    qDebug() << "path: "<<QList<Pos>::fromStdList(p.first);
    qDebug() << "dist: " << p.second;
}

void print_all(const std::pair<G::DistanceMap, G::VertexMap>& p)
{
    Matrix m;
    m.resize(ROW, COL);
    m.fill_all(0);
    const auto& dis = p.first;
    for (const auto &pos : dis) {
        m.set(pos.first, pos.second);
    }
    m.print();
}


void test_matrixgraph()
{
    BoolMatrix m;
    m.resize(ROW, COL);
    m.set_all_has();

    m.set_not({0, 1});
    m.set_not({1, 1});
    m.set_not({1, 2});
    m.set_not({2, 1});
    m.set_not({3, 1});
//    m.print();

//    m.set_not({3, 0});

    MG g(m);
    qDebug() << G::max_distant;
//    auto p = G::dijkstra_shortest_path(g, Pos(0, 0), Pos(0, 2));
//    auto pall = G::dijkstra_shortest_path_all(g, Pos(0,0));

//    print_path(p);
//    print_all(pall);


    auto mp = G::shortest_path(g, Pos(0, 0), Pos(0, 2));
    auto mpall = G::shortest_path_all(g, Pos(0,0));

    print_path(mp);
    print_all(mpall);
}
