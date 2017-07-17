#include "matrixgraph.h"

MatrixGraph::VertexVector MatrixGraph::vertexes() const
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

MatrixGraph::VertexVector MatrixGraph::neighbors(Graph::vertex_t v1) const
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

MatrixGraph::distance_t MatrixGraph::distance(Graph::vertex_t v1, Graph::vertex_t v2) const
{
    assert(matrix.has(v1));
    assert(matrix.has(v2));
    return 1;
}

