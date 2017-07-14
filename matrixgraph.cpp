#include "matrixgraph.h"

static constexpr int k_has = 1;
static constexpr int k_not = 0;

MatrixGraph::MatrixGraph(int row, int col)
    :m(row, col)
{
    m.fill_all(k_has);
}

void MatrixGraph::resize(int row, int col)
{
    m.resize(row, col);
    m.fill_all(k_has);
}

void MatrixGraph::clear()
{
    m.fill_all(k_has);
}

void MatrixGraph::setHas(Pos p)
{
    m.set(p, k_has);
}

void MatrixGraph::setNot(Pos p)
{
    m.set(p, k_not);
}

void MatrixGraph::print() const
{
    m.print();
}

MatrixGraph::VertexList MatrixGraph::vertexes() const
{
    VertexList vec;
    for (int row = 0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            vec.push_back(Pos(row, col));
        }
    }
    return vec;
}

MatrixGraph::VertexList MatrixGraph::neighbors(Graph::vertex_t v1) const
{
    VertexList vec;
    auto func = [&] (Pos p) {
        if (m.isInMatrix(p) && m.get(p) == k_has)
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
    assert(m.get(v1) == k_has);
    assert(m.get(v2) == k_has);
    return 1;
}

