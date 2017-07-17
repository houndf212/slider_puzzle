#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "graph.h"
#include "pos.h"
#include "boolmatrix.h"

struct PosHash
{
    size_t operator()(const Pos &p) const
    {
        constexpr int half = sizeof(p.row())*8/2;
        size_t c = p.row() << half | p.col();
        return std::hash<size_t>()(c);
    }
};

class MatrixGraph : public Graph<Pos, int, PosHash>
{
public:
    MatrixGraph(const BoolMatrix &m) : matrix(m) {}
    // Graph interface
protected:
    virtual VertexVector vertexes() const override;
    virtual VertexVector neighbors(vertex_t v1) const override;
    virtual distance_t distance(vertex_t v1, vertex_t v2) const override;
private:
    const BoolMatrix &matrix;
};

#endif // MATRIXGRAPH_H
