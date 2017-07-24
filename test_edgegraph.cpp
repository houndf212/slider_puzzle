#include "edgegraph.h"
#include <QtCore>
#include <assert.h>
#include "debug_output.h"

typedef int vertex_t;
typedef int distance_t;
typedef EdgeGraph<vertex_t, distance_t> EG;
typedef Dijkstra<EG> G;

void print_path(const std::pair<G::VertexList, G::distance_t>& p)
{
    qDebug() << "path: ";
    print(p.first);
    qDebug() << "dist: " << p.second;
}

void print_all(const std::pair<G::DistanceMap, G::VertexMap>& p)
{
    for (const auto &v : p.first) {
        auto path = G::find_path(v.first, p.second);
        qDebug() << v.first <<
                    " : "<<v.second <<
                    " : ";
        print(path);
    }
}
void testEdgeGraphFile()
{
    QFile file("../test.txt");
    if (!file.open(QFile::ReadOnly))
        return;

    QTextStream reader(&file);

    QString vstr = reader.readLine();
    size_t vsize = vstr.toInt();

    QString estr = reader.readLine();
    size_t esize = estr.toInt();
    qDebug() <<esize;


    EG g;

    while(!reader.atEnd()) {
        QString line = reader.readLine();
        line = line.trimmed();

        if (line.isEmpty()) break;
        QStringList lst = line.split(QRegularExpression("\\s+"));
        if (lst.size()!=3)
            qDebug() << line;
        assert(lst.size() == 3);
        qDebug() << line;
        vertex_t v1 = lst.at(0).toInt();
        vertex_t v2 = lst.at(1).toInt();
        distance_t d = lst.at(2).toInt();

        g.add_edge(v1, v2, d);

//        qDebug() <<g.vertex_size() <<":"<< g.edge_size();
    }

    qDebug() <<g.vertex_size();
    assert(g.vertex_size() == vsize);

//    auto mp = g.dijkstra_shortest_path_all(9808);

    {
    auto p = G::shortest_path(g, 0, 8);
    auto p1 = G::shortest_path_all(g, 0);
    print_path(p);
    print_all(p1);
    }

    {
    auto p = G::dijkstra_shortest_path(g, 0, 8);
    auto p1 = G::dijkstra_shortest_path_all(g, 0);
    print_path(p);
    print_all(p1);
    }
}
