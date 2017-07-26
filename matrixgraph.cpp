#include "matrixgraph.h"

size_t MatrixGraph::PosHash::operator()(const Pos &p) const
{
    constexpr int half = sizeof(p.row())*8/2;
    static_assert(half==16, "");
    size_t c = p.row() << half | p.col();
    return std::hash<size_t>()(c);
}

MatrixGraph::distance_t MatrixGraph::heuristic(MatrixGraph::vertex_t v1, MatrixGraph::vertex_t v2) const
{
    return std::abs(v1.row()-v1.row()) + std::abs(v1.col()-v2.col());
}

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

MatrixGraph::VertexVector MatrixGraph::neighbors(MatrixGraph::vertex_t v1) const
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

MatrixGraph::distance_t MatrixGraph::distance(MatrixGraph::vertex_t v1, MatrixGraph::vertex_t v2) const
{
    Q_UNUSED(v1);
    Q_UNUSED(v2);
    assert(matrix.has(v1));
    assert(matrix.has(v2));
    return 1;
}
