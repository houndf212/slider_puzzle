#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "dijkstra.h"
#include "boolmatrix.h"

class MatrixGraph
{
    struct PosHash
    {
        size_t operator()(const Pos &p) const;
    };
public:
    typedef Pos vertex_t;
    typedef int distance_t;
    typedef PosHash hash_t;
    typedef std::vector<Pos> VertexVector;
public:
    MatrixGraph(const BoolMatrix &m) : matrix(m) {}
    // Graph interface

    distance_t heuristic(vertex_t v1, vertex_t v2) const;

    VertexVector vertexes() const;
    VertexVector neighbors(vertex_t v1) const;
    distance_t distance(vertex_t v1, vertex_t v2) const;
private:
    const BoolMatrix &matrix;
};

#endif // MATRIXGRAPH_H
