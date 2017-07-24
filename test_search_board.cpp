#include "board.h"
#include "boardgen.h"
#include "puzzle_mover.h"
#include "debug_output.h"
#include <list>
#include <set>
#include "dijkstra.h"
#include "boardgraph.h"
#include <iostream>

typedef std::pair<Matrix, MoveList> MatrixPair;
typedef std::list<MatrixPair> MatrixList;

struct Comp
{
    bool operator()(const MatrixPair& mp1, const MatrixPair& mp2) const
    {
        return mp1.first < mp2.first;
    }
};

typedef std::set<MatrixPair, Comp> MatrixSet;

//测试用搜索方法来计算移动结果

bool check_matrix_board()
{
    Board b;
    b.gen(3, 3);
    BoardGen::gen(&b);
    auto path1 = PuzzleMover::solve(b);

    Board b2(b.inner_matrix());
    auto path2 = PuzzleMover::solve(b2);



    auto path = path1;
    MatrixSet s;
    s.emplace(b.inner_matrix(), path);
    assert(s.size() == 1);
    s.emplace(b.inner_matrix(), path);
    assert(s.size() == 1);
    path.check_loop_push_back(Board::Null_Down);
    s.emplace(b.inner_matrix(), path);
    assert(s.size() == 1);

    return path1 == path2;
}

void print(const MatrixPair &p)
{
    print(p.first);
    print(p.second);
}

void print(const MatrixList &lst)
{
    for (const auto &l : lst) {
        print(l);
    }
}

MatrixList next(const MatrixPair &mp)
{
    MatrixList lst;

    auto func = [&](Board::Direction d)
    {
        Board b(mp.first);
        if (b.null_move(d)) {
            MoveList ms = mp.second;
            ms.check_loop_push_back(d);
            lst.emplace_back(b.inner_matrix(), ms);
        }
    };

    func(Board::Null_Down);
    func(Board::Null_Up);
    func(Board::Null_Right);
    func(Board::Null_Left);

    return lst;
}

MatrixList next_children(const MatrixSet &s, const MatrixPair &m)
{
    MatrixList lst;
    MatrixList childs = next(m);
    for (const auto& c : childs) {
        if (s.find(c)==end(s))
            lst.push_back(c);
    }
    return lst;
}

void can_reach(MatrixSet &s, const MatrixPair &m, const Matrix &g) throw (MatrixPair)
{
    qDebug() << "s size: " << s.size();
    if (g.equal(m.first))
        throw m;

    MatrixList children = next_children(s, m);
    for (const auto &c : children) {
            s.insert(c);
            can_reach(s, c, g);
    }
}

bool depth_first_seach(const Matrix &start, const Matrix &goal)
{
    print(start);
    print(goal);
    MatrixPair sp(start, MoveList());
    MatrixSet s;
    s.insert(sp);
    try {
        MatrixList children = next_children(s, sp);
        for (const auto &c : children) {
                s.insert(c);
                can_reach(s, c, goal);
                qDebug() << "reach one line end";
        }
        return false;
    }
    catch (const MatrixPair & p) {
        qDebug() << "move size: " << p.second.size();
        print(p.second);
        return true;
    }
}


void test_next()
{
    Board b;
    b.gen(3, 3);
    BoardGen::gen(&b);
    MatrixPair m = std::make_pair(b.inner_matrix(), MoveList());
    MatrixList nexts = next(m);
    print(m);
    print(nexts);
}

void test_next_children()
{
    Board b;
    b.gen(2, 2);
    BoardGen::gen(&b);
    MatrixPair m = std::make_pair(b.inner_matrix(), MoveList());
    MatrixSet s;
    s.insert(m);
    print(m);
    MatrixList llst1 = next_children(s, m);
    qDebug() << "1 lst child size: " << llst1.size();

    for (const auto & l : llst1) {
        s.insert(l);
        MatrixList llst2 = next_children(s, l);
        qDebug() << "2 lst child size: " << llst2.size();
    }
}

void test_search_board()
{
//    assert(check_matrix_board());
    Board b;
    b.gen(3, 3);
    BoardGen::gen(&b);

    typedef BoardGraph<int> BG;
    typedef Dijkstra<BG> G;

    BG g;
    auto p = G::AStart_path(g, b.inner_matrix(), b.inner_origin_matrix());
    print(b.inner_matrix());
    std::cout<<"###"<<std::endl;
    for (const auto & m : p.first) {
        print(m);
    }
    std::cout << p.second <<std::endl;
}


