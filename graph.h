#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <iostream>

typedef int disance_t;

template<class Vertex>
class Graph
{
    typedef std::vector<Vertex> VertexList;
public:
    virtual ~Graph() = default;
    virtual VertexList vertexes() const = 0;
    virtual VertexList neighbors(Vertex v1) const = 0;
    virtual disance_t distance(Vertex v1, Vertex v2) const = 0;
public:
    static VertexList dijkstra_shortest_path(const Graph&g, Vertex start, Vertex finish)
    {
        using namespace std;
        // Find the smallest distance in the already in closed list and push it in -> previous
        unordered_map<Vertex, disance_t> distances;
        unordered_map<Vertex, Vertex> previous;
        VertexList nodes; // Open list
        VertexList path; // Closed list

        auto comparator = [&] (Vertex left, Vertex right) { return distances[left] > distances[right]; };

        for (const auto& vertex : g.vertexes())
        {
            if (vertex == start)
            {
                distances[vertex] = 0;
            }
            else
            {
                distances[vertex] = numeric_limits<disance_t>::max();
            }

            nodes.push_back(vertex);
            push_heap(begin(nodes), end(nodes), comparator);
        }

        while (!nodes.empty())
        {
            pop_heap(begin(nodes), end(nodes), comparator);
            Vertex smallest = nodes.back();
            nodes.pop_back();

            std::cout << "Open list: ";
            for( auto i = nodes.begin(); i != nodes.end(); ++i)
                std::cout << *i << ' ';
            std::cout << std::endl;

            if (smallest == finish)
            {
                while (previous.find(smallest) != end(previous))
                {
                    path.push_back(smallest);
                    smallest = previous[smallest];
                    std::cout << "Closed list: ";
                    for( auto i = path.begin(); i != path.end(); ++i)
                        std::cout << *i << ' ';
                    std::cout << std::endl;
                }

                break;
            }

            if (distances[smallest] == numeric_limits<int>::max())
            {
                break;
            }

            for (const auto& neighbor : g.neighbors(smallest))
            {
                disance_t alt = distances[smallest] + g.distance(smallest, neighbor);
                if (alt < distances[neighbor])
                {
                    distances[neighbor] = alt;
                    previous[neighbor] = smallest;
                    make_heap(begin(nodes), end(nodes), comparator);
                }
            }
        }

        return path;
    }
};



#endif // GRAPH_H
