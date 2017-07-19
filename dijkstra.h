#ifndef Dijkstra_H
#define Dijkstra_H
#include <limits>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <assert.h>

template<class T, class D, class VertexHash = std::hash<T>>
class Dijkstra
{
public:
    typedef T vertex_t;
    typedef D distance_t;

    typedef std::vector<vertex_t> VertexVector;
    typedef std::list<vertex_t> VertexList;

    typedef std::unordered_set<vertex_t, VertexHash> VertexSet;
    typedef std::unordered_map<vertex_t, distance_t, VertexHash> DistanceMap;
    typedef std::unordered_map<vertex_t, vertex_t, VertexHash> VertexMap;

    static constexpr distance_t max_distant = std::numeric_limits<distance_t>::max();

    template<class G>
    static std::pair<DistanceMap, VertexMap>
    dijkstra_shortest_path_all(const G &g, vertex_t start)
    {
        // Find the smallest distance in the already in closed list and push it in -> previous
        DistanceMap distances;
        VertexMap previous;
        VertexVector open_list; // Open list
        VertexSet close_list;

        auto comparator = [&distances] (vertex_t left, vertex_t right) {
            return distances[left] > distances[right]; };

        VertexVector verts = g.vertexes();
        assert(std::find(begin(verts), end(verts), start)!=end(verts));

        for (vertex_t vertex : verts)
        {
            if (vertex == start)
            {
                distances[vertex] = 0;
            }
            else
            {
                distances[vertex] = std::numeric_limits<distance_t>::max();
            }

            open_list.push_back(vertex);
            push_heap(begin(open_list), end(open_list), comparator);
        }

        while (!open_list.empty())
        {
            pop_heap(begin(open_list), end(open_list), comparator);
            vertex_t smallest = open_list.back();
            open_list.pop_back();
            close_list.insert(smallest);

            bool isHeapModify = false;
            VertexVector all_neighbor = g.neighbors(smallest);
            for (vertex_t neighbor : all_neighbor)
            {
                if (close_list.find(neighbor)!=end(close_list))
                    continue;

                distance_t start_dis = distances[smallest];
                distance_t edge_dis = g.distance(smallest, neighbor);
                distance_t alt =  start_dis + edge_dis ;
                if (alt < distances[neighbor])
                {
                    distances[neighbor] = alt;
                    previous[neighbor] = smallest;
                    isHeapModify = true;
                }
            }
            if (isHeapModify)
                make_heap(begin(open_list), end(open_list), comparator);
        }
        return std::make_pair(distances, previous);
    }

    template<class G>
    static std::pair<VertexList, distance_t>
    dijkstra_shortest_path(const G &g, vertex_t start, vertex_t finish)
    {
        // Find the smallest distance in the already in closed list and push it in -> previous
        DistanceMap distances;
        VertexMap previous;
        VertexVector open_list; // Open list
        VertexSet close_list;
        VertexList path;

        auto comparator = [&distances] (vertex_t left, vertex_t right) {
            return distances[left] > distances[right]; };

        VertexVector verts = g.vertexes();
        assert(std::find(begin(verts), end(verts), start)!=end(verts));
        assert(std::find(begin(verts), end(verts), finish)!=end(verts));

        for (vertex_t vertex : verts)
        {
            if (vertex == start)
            {
                distances[vertex] = 0;
            }
            else
            {
                distances[vertex] = std::numeric_limits<distance_t>::max();
            }

            open_list.push_back(vertex);
            push_heap(begin(open_list), end(open_list), comparator);
        }

        while (!open_list.empty())
        {
            pop_heap(begin(open_list), end(open_list), comparator);
            vertex_t smallest = open_list.back();
            open_list.pop_back();
            close_list.insert(smallest);

            if (smallest == finish)
            {
                path = find_path(finish, previous);
                break;
            }

            if (distances[smallest] == std::numeric_limits<distance_t>::max())
            {
                break;
            }

            bool isHeapModify = false;
            VertexVector all_neighbor = g.neighbors(smallest);
            for (vertex_t neighbor : all_neighbor)
            {
                if (close_list.find(neighbor)!=end(close_list))
                    continue;

                distance_t start_dis = distances[smallest];
                distance_t edge_dis = g.distance(smallest, neighbor);
                distance_t alt =  start_dis + edge_dis ;
                if (alt < distances[neighbor])
                {
                    distances[neighbor] = alt;
                    previous[neighbor] = smallest;
                    isHeapModify = true;
                }
            }
            if (isHeapModify)
                make_heap(begin(open_list), end(open_list), comparator);
        }

        return std::make_pair(path, distances[finish]);
    }

    static VertexList find_path(vertex_t finish, const VertexMap &previous)
    {
        VertexList path;
        vertex_t smallest = finish;
        auto it = previous.find(smallest);
        auto cend = end(previous);
        while (it != cend)
        {
            path.push_back(smallest);
            smallest = it->second;
            it = previous.find(smallest);
        }
        path.reverse();
        return path;
    }
};

#endif // Dijkstra_H


