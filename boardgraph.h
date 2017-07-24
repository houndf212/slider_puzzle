#ifndef BOARDGRAPH_H
#define BOARDGRAPH_H
#include <string>
#include "matrix.h"
#include "board.h"
#include "debug_output.h"

struct BoardHash
{
    bool operator()(const Matrix& m) const
    {
        std::string str;
        for (int row=0; row<m.row_size(); ++row) {
            for (int col=0; col<m.col_size(); ++col) {
                Pos p(row, col);
                int v = m.get(p);
                str+=std::to_string(v);
            }
        }
        return std::hash<std::string>()(str);
    }
};

template <class D>
class BoardGraph
{
public:
    typedef Matrix vertex_t;
    typedef D distance_t;
    typedef BoardHash hash_t;

    typedef std::vector<Matrix> VertexVector;
    typedef std::list<Matrix> VertexList;

    static MoveList toMoveList(const VertexList& lst)
    {
        MoveList ms;
        auto it = lst.begin();
        Board b1(*it);
        for (it++; it!=end(lst); ++it) {
            Board b2(*it);
            Pos p2 = b2.get_null_pos();
            auto d = b1.test_null_move_to(p2);
            assert(d!=Board::NotValid);
            b1.null_move(d);
            ms.check_loop_push_back(d);
        }
        return ms;
    }
    static VertexList toMatrixList(const MoveList& mlst, const Matrix &start)
    {
        VertexList vl;
        Board b(start);
        for (auto d : mlst) {
            bool bt = b.null_move(d);
            assert(bt);
            vl.push_back(b.inner_matrix());
        }
        return vl;
    }

    static VertexVector neighbors(const vertex_t &m)
    {
        VertexVector lst;

        auto func = [&](Board::Direction d)
        {
            Board b(m);
            if (b.null_move(d)) {
                lst.push_back(b.inner_matrix());
            }
        };

        func(Board::Null_Down);
        func(Board::Null_Up);
        func(Board::Null_Right);
        func(Board::Null_Left);

        return lst;
    }

    static distance_t distance(const vertex_t &v1, const vertex_t &v2)
    {
        Q_UNUSED(v1);
        Q_UNUSED(v2);
        assert(check_move(v1, v2));
        return 1;
    }

    static distance_t heuristic(const vertex_t &v1, const vertex_t &v2)
    {
        distance_t dist = 0;
        const Board board(v2);
        assert(board.isDone());
        for (int row=0; row<v1.row_size(); ++row) {
            for (int col=0; col<v1.col_size(); ++col) {
                Pos p(row, col);
                int v = v1.get(p);
                if (v==0) continue;
                Pos f = board.origin_pos(v);
                dist += std::abs(p.row()-f.row()) + std::abs(p.col()-f.col());
            }
        }
        return dist;
    }
private:
    static bool check_move(const vertex_t &v1, const vertex_t &v2)
    {
        Board b1(v1);
        Board b2(v2);
        Pos p1 = b1.get_null_pos();
        return b2.test_null_move_to(p1) != Board::NotValid;
    }
};

#endif // BOARDGRAPH_H
