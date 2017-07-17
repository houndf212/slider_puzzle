#include "edgegraph.h"
#include <assert.h>
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

    typedef int vertex_t;
    typedef int distance_t;
    EdgeGraph<vertex_t, distance_t> g;

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
        distance_t d = lst.at(2).toDouble();

        g.add_edge(v1, v2, d);

//        qDebug() <<g.vertex_size() <<":"<< g.edge_size();
    }

    qDebug() <<g.vertex_size();
    assert(g.vertex_size() == vsize);

//    auto mp = g.dijkstra_shortest_path_all(9808);

    auto p = g.dijkstra_shortest_path(0, 8);
//    qDebug() << QVector<vertex_t>::fromStdVector(p.first);
    qDebug() << "dist: " << p.second;
}
