#include "board.h"
#include "puzzle_mover.h"
#include "debug_output.h"
#include <list>
#include <set>
#include "dijkstra.h"
#include "boardgraph.h"
#include <iostream>
#include "board_api.h"
#include "origin_matrix.h"

using namespace std;


//从观察来看，从一个状态到目的状态，最优解离目的的 heuristic 是逐渐减少的
// 并且 向heuristic减少的数量（向上振幅）不会超过3，也许和 空格按正方形移动4次heuristic增加3有关系（循环）？

//这里写个测试函数

int check_amplitude(const std::list<Matrix> &ms)
{
    std::vector<Matrix> vec(begin(ms), end(ms));
    std::vector<int> intvec;
    intvec.resize(vec.size());
    for (size_t i=0; i<vec.size(); ++i) {
        intvec[i] = BoardGraph::heuristic(vec[i], vec.back());
    }

    std::vector<int> amplitude;
    amplitude.resize(intvec.size());
    amplitude[0] = 0;
    int amp = 0;
    for (size_t i=1; i<intvec.size(); ++i) {
        if (intvec[i] - intvec[i-1] == 1) {
            amp++;
        }
        else {
            assert(intvec[i] - intvec[i-1] == -1);
            amp = 0;
        }
        amplitude[i] = amp;
    }

    int max_amp = *std::max_element(begin(amplitude), end(amplitude));
    return max_amp;
}

void test_search_board()
{
    typedef BoardGraph BG;
    typedef Dijkstra<BG> G;

    BG g;

    Matrix finish = Origin_Matrix(2, 3).matrix();

    G::VertexSet open_set;
    G::VertexSet close_set;

    open_set.insert(finish);

    int all = 0;
    vector<pair<size_t, double>> steps(1, {0,0});
    vector<pair<size_t, double>> amplitude(1, {0,0});

    while (!open_set.empty()) {

        auto it = open_set.begin();
        Matrix m = *it;
        open_set.erase(it);
        close_set.insert(m);

        for (const Matrix &next : BG::neighbors(m)) {
            if (close_set.find(next)!=end(close_set))
                continue;

            open_set.insert(next);
        }

        auto p = G::AStart_path(g, m, finish);
        std::list<Matrix> ms = p.first;

        //总数
        all++;
        qDebug() <<"==========================";
        qDebug() << "size :"<<all;
        // 计算步数
        size_t step = p.first.size();
        if (step > steps.size()-1) {
            steps.resize(step+1);
        }
        steps[step].first++;
        for (size_t i=0; i<steps.size(); ++i) {
            steps[i].second = double(steps[i].first) / all;
        }
        qDebug() << "steps:";
        qDebug() << steps;

        //计算振幅
        ms.push_front(m);
        size_t n = check_amplitude(ms);
        if (n>amplitude.size()-1) {
            amplitude.resize(n+1);
        }

        amplitude[n].first++;
        for (size_t i=0; i<amplitude.size(); ++i) {
            amplitude[i].second = double(amplitude[i].first) / all;
        }
        qDebug() << "amplitude:";
        qDebug() << amplitude;
    }
}


