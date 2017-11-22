#include "boardgraph.h"
#include "board_api.h"

size_t BoardGraph::MatrixHash::operator()(const Matrix &m) const
{
    return std::hash<std::string>()(BoardGraph::toString(m));
}

std::string BoardGraph::toString(const Matrix &m)
{
    std::string str;
    str.reserve(m.row_size()*m.col_size());
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            auto v = m.get(p);
            str.push_back(v);
        }
    }
    return str;
}

MoveList BoardGraph::toMoveList(const BoardGraph::VertexList &lst, const Matrix &start)
{
    MoveList ms;
    Matrix b1(start);
    for (auto it=begin(lst); it!=end(lst); ++it) {
        const Matrix &b2(*it);
        Direction d = Board_API::get_direction(b1, b2);
        assert(d!=Direction::NotValid);
        ms.check_loop_push_back(d);
        b1 = b2;
    }
    return ms;
}

BoardGraph::VertexList BoardGraph::toMatrixList(const MoveList &mlst, const Matrix &start)
{
    VertexList vl;
    Matrix b = start;
    Pos null_pos = Board_API::get_null_pos(b);
    for (auto d : mlst) {
        bool bt = Board_API::hint_null_move(&b, null_pos, d);
        assert(bt);
        Q_UNUSED(bt);
        Board_API::move(&null_pos, d);
        vl.push_back(b);
    }
    return vl;
}

BoardGraph::VertexVector BoardGraph::neighbors(const BoardGraph::vertex_t &m)
{
    VertexVector lst;
    Pos nil = Board_API::get_null_pos(m);
    auto func = [&](Direction d)
    {
        Matrix b = m;
        if (Board_API::hint_null_move(&b, nil, d)) {
            lst.push_back(b);
        }
    };

    func(Direction::Null_Down);
    func(Direction::Null_Up);
    func(Direction::Null_Right);
    func(Direction::Null_Left);

    return lst;
}

BoardGraph::distance_t BoardGraph::distance(const BoardGraph::vertex_t &v1, const BoardGraph::vertex_t &v2)
{
    Q_UNUSED(v1);
    Q_UNUSED(v2);
    assert(Board_API::check_next(v1, v2));
    return 1;
}

BoardGraph::distance_t BoardGraph::heuristic(const BoardGraph::vertex_t &v1, const BoardGraph::vertex_t &v2)
{

    assert(v1.row_size() == v2.row_size());
    assert(v1.col_size() == v2.col_size());
//    assert(Board_API::isDone(v2));

    std::vector<Pos> index1, index2;
    index1.resize(v1.row_size()*v1.col_size());
    index2.resize(index1.size());
    //cal index
    for (int row=0; row<v1.row_size(); ++row) {
        for (int col=0; col<v1.col_size(); ++col) {
            Pos p(row, col);
            auto val1 = v1.get(p);
            auto val2 = v2.get(p);
            index1[val1] = p;
            index2[val2] = p;
        }
    }

    distance_t dist = 0;
    // skip null value = 0;
    for (size_t i=1; i<index1.size(); ++i) {
        dist+=Manhattan_Distance(index1[i], index2[i]);
    }
    return dist;
}
