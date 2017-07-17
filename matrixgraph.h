#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "graph.h"
#include "pos.h"
#include "matrix.h"

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
    void resize(int row, int col);
    void clear();
    void setHas(Pos p);
    void setNot(Pos p);
    void print() const;
    // Graph interface
protected:
    virtual VertexList vertexes() const override;
    virtual VertexList neighbors(vertex_t v1) const override;
    virtual distance_t distance(vertex_t v1, vertex_t v2) const override;
private:
    BoolMatrix m;
};

#endif // MATRIXGRAPH_H
