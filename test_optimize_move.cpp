#include "board.h"
#include "puzzle_mover.h"
#include "debug_output.h"
#include "boardgraph.h"
#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

void print_diff(const std::list<Matrix> &matrixlist, const Matrix &finish)
{
    for (const auto &m : matrixlist) {
//        print(m);
        cout<<"diff to finish: " << BoardGraph::heuristic(m, finish) <<endl;
    }
}


struct MyDiff
{
    int i;
    int j;
    int n;

    int move_size; // j-i
    int diff;// mi-mj

    Matrix m_i;
    Matrix m_j;
};


struct Comp
{
    bool operator()(const MyDiff &d1, const MyDiff &d2) const
    {
        return d1.move_size - d1.diff < d2.move_size - d2.diff
                || (d1.move_size - d1.diff == d2.move_size - d2.diff && d1.diff < d2.diff);
    }
};

void calc(const std::list<Matrix> &matrixlist, const Matrix &finish)
{
    std::vector<Matrix> mv(begin(matrixlist), end(matrixlist));
    qDebug() << "size: "<<mv.size();

    vector<int> diffs;
    diffs.reserve(mv.size());
    for (const auto &m : mv) {
        diffs.push_back(BoardGraph::heuristic(m, finish));
    }


//    while(diffs.size()>=2) {
//        if (diffs[diffs.size()-2] - diffs[diffs.size()-1]==1)
//            diffs.pop_back();
//        else
//            break;
//    }
    qDebug()<< "size:"<<diffs.size()<<diffs;

    Comp comp;
    priority_queue<MyDiff, std::vector<MyDiff>, Comp> pq(comp);

//    for (int i=0; i<diffs.size()-1; ++i) {
//        for (int j=i+1; j<diffs.size()-1; ++j) {
//            int d = BoardGraph::heuristic(mv[i], mv[j]);
//            if (j-i-d>=4)
//            pq.push({i, j, diffs.size(), j-i, d, mv[i], mv[j]});
//        }
//    }
//    while (!pq.empty()) {
//        MyDiff d = pq.top();
//        pq.pop();
//        qDebug() <<make_pair(make_pair(d.i, d.j), d.n)<< d.move_size << "-" <<d.diff <<"="<<d.move_size-d.diff;

//    }
}

void test_optimize_move()
{
/*
 5  0  2
 1  8  3
 4  7  6
10 11  9
*/
    Board b;
    b.resize(3, 3);
    b.gen();

    Matrix start = b.inner_matrix();
    Matrix finish = b.inner_origin_matrix();
    print(start);

//    MoveList movelist = PuzzleMover::search_solve(b);
//    qDebug() << "best movelist: " <<movelist.size()+1;

    {
        MoveList movelist = PuzzleMover::solve(b);
        std::list<Matrix> matrixlist = BoardGraph::toMatrixList(movelist, start);
        matrixlist.push_front(start);
        calc(matrixlist, finish);
    }

    {
        MoveList movelist = PuzzleMover::search_solve(b);
        std::list<Matrix> matrixlist = BoardGraph::toMatrixList(movelist, start);
        matrixlist.push_front(start);
        calc(matrixlist, finish);
    }
}
