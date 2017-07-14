#ifndef GRAPH_H
#define GRAPH_H
#include <limits>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>

template<class T, class D, class VertexHash = std::hash<T>>
class Graph
{
public:
    typedef T vertex_t;
    typedef D distance_t;
    typedef std::vector<vertex_t> VertexList;
    typedef std::unordered_set<vertex_t, VertexHash> VertexSet;
    typedef std::unordered_map<vertex_t, distance_t, VertexHash> DistanceMap;
    typedef std::unordered_map<vertex_t, vertex_t, VertexHash> VertexMap;
public:
    virtual ~Graph() = default;
protected:
    virtual VertexList vertexes() const = 0;
    virtual VertexList neighbors(vertex_t v1) const = 0;
    virtual distance_t distance(vertex_t v1, vertex_t v2) const = 0;
public:
    std::pair<DistanceMap, VertexMap>
    dijkstra_shortest_path_all(vertex_t start)
    {
        // Find the smallest distance in the already in closed list and push it in -> previous
        DistanceMap distances;
        VertexMap previous;
        VertexList open_list; // Open list
        VertexSet close_list;

        auto comparator = [&distances] (vertex_t left, vertex_t right) {
            return distances[left] > distances[right]; };

        VertexList verts = this->vertexes();
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
            VertexList all_neighbor = this->neighbors(smallest);
            for (vertex_t neighbor : all_neighbor)
            {
                if (close_list.find(neighbor)!=end(close_list))
                    continue;

                distance_t start_dis = distances[smallest];
                distance_t edge_dis = this->distance(smallest, neighbor);
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

    std::pair<VertexList, distance_t>
    dijkstra_shortest_path(vertex_t start, vertex_t finish)
    {
        // Find the smallest distance in the already in closed list and push it in -> previous
        DistanceMap distances;
        VertexMap previous;
        VertexList open_list; // Open list
        VertexSet close_list;
        VertexList path;

        auto comparator = [&distances] (vertex_t left, vertex_t right) {
            return distances[left] > distances[right]; };

        VertexList verts = this->vertexes();
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
            VertexList all_neighbor = this->neighbors(smallest);
            for (vertex_t neighbor : all_neighbor)
            {
                if (close_list.find(neighbor)!=end(close_list))
                    continue;

                distance_t start_dis = distances[smallest];
                distance_t edge_dis = this->distance(smallest, neighbor);
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
        auto cend = previous.end();
        while (it != cend)
        {
            path.push_back(smallest);
            smallest = it->second;
            it = previous.find(smallest);
        }
        std::reverse(begin(path), end(path));
        return path;
    }
};

#endif // GRAPH_H


