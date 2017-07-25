#include "matrixgraph.h"
#include "matrix.h"
#include "debug_output.h"

constexpr int ROW = 10;
constexpr int COL = 10;
typedef MatrixGraph MG;
typedef Dijkstra<MG> G;

void print_path(const std::pair<G::VertexList, G::distance_t>& p)
{
    Matrix m;
    m.resize(ROW, COL);
    m.fill_all(0);
    for (auto pos : p.first) {
        m.set(pos, 1);
    }
    print(m);
    print(p.first);
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
    print(m);
}


void test_matrixgraph()
{
    BoolMatrix m;
    m.resize(ROW, COL);
    m.set_all_has();

    m.set_not({1, 6});
    m.set_not({2, 6});
    m.set_not({2, 7});
    m.set_not({3, 7});
    m.set_not({4, 7});
    m.set_not({5, 7});
    m.set_not({6, 7});
    m.set_not({6, 6});
    m.set_not({6, 5});
    print(m);

    MG g(m);
    qDebug() << G::max_distant;
    Pos start(4, 0);
    Pos end(4, 9);
    auto p = G::dijkstra_shortest_path(g, start, end);
    auto pall = G::dijkstra_shortest_path_all(g, start);

    print_path(p);
    print_all(pall);


    auto mp = G::shortest_path(g, start, end);
    auto mpall = G::shortest_path_all(g, start);

    print_path(mp);
    print_all(mpall);

    auto ap = G::AStart_path(g, start, end);
    print_path(ap);
}
