#ifndef BOARDGRAPH_H
#define BOARDGRAPH_H
#include <string>
#include "matrix.h"
#include "board.h"
#include "debug_output.h"

class BoardGraph
{
    struct MatrixHash
    {
        size_t operator()(const Matrix &m) const;
    };
public:
    typedef Matrix vertex_t;
    typedef int distance_t;
    typedef MatrixHash hash_t;

    typedef std::vector<Matrix> VertexVector;
    typedef std::list<Matrix> VertexList;

    static std::string toString(const Matrix &m);

    static MoveList toMoveList(const VertexList& lst, const Matrix &start);
    static VertexList toMatrixList(const MoveList& mlst, const Matrix &start);

    static VertexVector neighbors(const vertex_t &m);
    static distance_t distance(const vertex_t &v1, const vertex_t &v2);
    static distance_t heuristic(const vertex_t &v1, const vertex_t &v2);
};

#endif // BOARDGRAPH_H
