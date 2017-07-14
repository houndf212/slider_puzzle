#include <QApplication>
#include <QtCore>
#include "board.h"
#include "boardgen.h"
#include <iostream>
using namespace std;

#include "gamewindow.h"

#include "edgegraph.h"

void testEdgeGraph()
{
    typedef int vertex_t;
    typedef double distance_t;
    EdgeGraph<vertex_t, distance_t> g;

    g.add_edge(1, 2, 7.1);
    g.add_edge(1, 3, 9);
    g.add_edge(1, 6, 14);

    g.add_edge(2, 3, 10);
    g.add_edge(2, 4, 15);

    g.add_edge(3, 4, 11);
    g.add_edge(3, 6, 2.1);

    g.add_edge(4, 5, 6);

    g.add_edge(5, 6, 9);

    auto mp = g.dijkstra_shortest_path_all(1);

    auto p = g.dijkstra_shortest_path(1, 5);
    qDebug() << QVector<int>::fromStdVector(p.first);
    qDebug() << "dist: " << p.second;
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
    qDebug() << QVector<vertex_t>::fromStdVector(p.first);
    qDebug() << "dist: " << p.second;
}

void test()
{
    Board m;
    m.gen(5, 5);
    BoardGen::gen(&m);
    bool b = true;
    while (b) {
        m.print();
        qDebug() << "input: ";
        char c;
        cin>>c;
        switch (c) {
        case 'w':
            m.move(Board::Up);
            break;
        case 's':
            m.move(Board::Down);
            break;
        case 'a':
            m.move(Board::Left);
            break;
        case 'd':
            m.move(Board::Right);
            break;
        default:
            b = false;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    testEdgeGraphFile();
    return 0;
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
