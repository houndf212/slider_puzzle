#ifndef EDGEGRAPH_H
#define EDGEGRAPH_H
#include "graph.h"
#include <unordered_set>

template<class vertex_t>
struct IntegerPairHash
{
    size_t operator()(const std::pair<vertex_t, vertex_t> &e) const
    {
        constexpr int half = sizeof(vertex_t)*8/2;
        vertex_t c = e.first << half | e.second;
        return std::hash<vertex_t>()(c);
    }
};

template<class vertex_t, class distance_t, class PairHash = IntegerPairHash<vertex_t>>
class EdgeGraph : public Graph<vertex_t, distance_t>
{
    typedef std::pair<vertex_t, vertex_t> Edge;
public:
    size_t vertex_size() const { return m_vertexes.size(); }
    size_t edge_size() const { return m_dist.size(); }
    bool add_edge(vertex_t v1, vertex_t v2, distance_t weight)
    {
        vertex_t min = std::min(v1, v2);
        vertex_t max = std::max(v1, v2);

        std::pair<vertex_t, vertex_t> p(min, max);

        if (m_dist.find(p) != m_dist.end())
            return false;

        m_dist[p] = weight;

        m_vertexes.insert(v1);
        m_vertexes.insert(v2);

        m_neighbors[v1].push_back(v2);
        m_neighbors[v2].push_back(v1);

        return true;
    }
    // Graph interface
protected:
    // keyword typename is need!
    using typename Graph<vertex_t, distance_t>::VertexVector;
    VertexVector vertexes() const override
    {
        return {begin(m_vertexes), end(m_vertexes)};
    }
    VertexVector neighbors(vertex_t v) const override
    {
        assert(is_vertex_in_graph(v));

        auto it = m_neighbors.find(v);
        assert(it != end(m_neighbors));
        return it->second;
    }
    distance_t distance(vertex_t v1, vertex_t v2) const override
    {
        vertex_t min = std::min(v1, v2);
        vertex_t max = std::max(v1, v2);
        auto it = m_dist.find(std::make_pair(min, max));
        assert(it!=m_dist.end());
        return it->second;
    }
private:
    bool is_vertex_in_graph(vertex_t v) const
    {
        return m_vertexes.find(v) != m_vertexes.end();
    }
private:
    std::unordered_set<vertex_t> m_vertexes;
    std::unordered_map<vertex_t, std::vector<vertex_t>> m_neighbors;
    std::unordered_map<Edge, distance_t, PairHash> m_dist;
};

#endif // EDGEGRAPH_H
