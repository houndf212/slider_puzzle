#include <QApplication>
#include <QtCore>
#include "board.h"
#include "boardgen.h"
#include <iostream>
using namespace std;

#include "gamewindow.h"

#include "edgegraph.h"
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
#include <QPoint>
#include "matrixgraph.h"
QDebug operator<<(QDebug d, const Pos &p)
{
    d<<"("<<p.row()<<", "<<p.col()<<")";
    return d;
}

#include "boardrotator.h"
#include "boolmatrix.h"
void testMatrixGraph()
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

void testBoard()
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
            m.null_move(Board::Null_Down);
            break;
        case 's':
            m.null_move(Board::Null_Up);
            break;
        case 'a':
            m.null_move(Board::Null_Right);
            break;
        case 'd':
            m.null_move(Board::Null_Left);
            break;

        case 'r':{
            int row;
            cin >> row;
            int col;
            cin >> col;
            Pos p(row, col);
            auto mlist = BoardRotator::rotate(m, p, BoardRotator::ClockWise);
            for (auto d : mlist)
                m.null_move(d);
        }
            break;

        case 'R':{
            int row;
            cin >> row;
            int col;
            cin >> col;
            Pos p(row, col);
            auto mlist = BoardRotator::rotate(m, p, BoardRotator::AntiClock);
            for (auto d : mlist)
                m.null_move(d);
        }
            break;
        default:
            b = false;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
//    testBoard();
//    return 0;
    testMatrixGraph();
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
