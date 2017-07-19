#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "dijkstra.h"
#include "pos.h"
#include "boolmatrix.h"

template<class D>
class MatrixGraph
{
    struct PosHash
    {
        size_t operator()(const Pos &p) const
        {
            constexpr int half = sizeof(p.row())*8/2;
            size_t c = p.row() << half | p.col();
            return std::hash<size_t>()(c);
        }
    };
public:
    typedef Pos vertex_t;
    typedef D distance_t;
    typedef PosHash hash_t;
    typedef std::vector<Pos> VertexVector;
public:
    MatrixGraph(const BoolMatrix &m) : matrix(m) {}
    // Graph interface

    VertexVector vertexes() const
    {
        VertexVector vec;
        for (int row = 0; row<matrix.row_size(); ++row) {
            for (int col=0; col<matrix.col_size(); ++col) {
                Pos p(row, col);
                if (matrix.has(p)) {
                    vec.push_back(p);
                }
            }
        }
        return vec;
    }
    VertexVector neighbors(vertex_t v1) const
    {
        VertexVector vec;
        auto func = [&] (Pos p) {
            if (matrix.isInMatrix(p) && matrix.has(p))
                vec.push_back(p);
        };
        func({v1.row()+1, v1.col()});
        func({v1.row()-1, v1.col()});
        func({v1.row(), v1.col()+1});
        func({v1.row(), v1.col()-1});
        return vec;
    }
    distance_t distance(vertex_t v1, vertex_t v2) const
    {
        assert(matrix.has(v1));
        assert(matrix.has(v2));
        return 1;
    }
private:
    const BoolMatrix &matrix;
};

#endif // MATRIXGRAPH_H
