#ifndef Dijkstra_H
#define Dijkstra_H
#include <limits>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <assert.h>

template<class G>
class Dijkstra
{
public:
    typedef typename G::vertex_t vertex_t;
    typedef typename G::distance_t distance_t;
    typedef typename G::hash_t VertexHash;

    typedef std::vector<vertex_t> VertexVector;
    typedef std::list<vertex_t> VertexList;

    typedef std::unordered_set<vertex_t, VertexHash> VertexSet;
    typedef std::unordered_map<vertex_t, distance_t, VertexHash> DistanceMap;
    typedef std::unordered_map<vertex_t, vertex_t, VertexHash> VertexMap;

    static constexpr distance_t max_distant = std::numeric_limits<distance_t>::max();


    // 返回所有最短路径， 如果不能到达 distanceMap[v] = max
    static std::pair<VertexList, distance_t>
    shortest_path(const G &g, vertex_t start, vertex_t finish)
    {
        return my_dijkstra_shortest_path(g, start, finish);
    }

    //返回从start 到其它点的最短路径， 如果first中没有v，那么v就到达不了
    static std::pair<DistanceMap, VertexMap>
    shortest_path_all(const G &g, vertex_t start)
    {
        return my_dijkstra_shortest_path_all(g, start);
    }

    //从 path_all返回中的 second 查找返回路径，前提是要注意 fisrt，中要包含finish点
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

public:
    // 返回所有最短路径， 如果不能到达 distanceMap[v] = max
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
                distances[vertex] = max_distant;
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

            //必须添加这个跳出，在所有为标记点距离都是max 即是说， 从start 不能达到那些区域
            //反过来说， 这个图，有孤立点的点!
            if (distances[smallest] == max_distant)
                break;

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

    // 返回所有最短路径， 如果不能到达 distance = max
    static std::pair<VertexList, distance_t>
    dijkstra_shortest_path(const G &g, vertex_t start, vertex_t finish)
    {
        // Find the smallest distance in the already in closed list and push it in -> previous
        DistanceMap distances;
        VertexMap previous;
        VertexVector open_list; // Open list
        VertexSet close_list;
        VertexList path;
        distance_t dist = max_distant;

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
                distances[vertex] = max_distant;
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

            //必须添加这个跳出，在所有为标记点距离都是max 即是说， 从start 不能达到那些区域
            //反过来说， 这个图，有孤立点的点!
            if (distances[smallest] == max_distant)
                break;

            if (smallest == finish)
            {
                path = find_path(finish, previous);
                dist = distances[finish];
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

        return std::make_pair(path, dist);
    }

    class PriorityQueue
    {
    public:
        typedef std::pair<distance_t, vertex_t> PQElement;
        bool empty() const { return elements.empty(); }
        void put(vertex_t item, distance_t p) { elements.emplace(p, item); }
        vertex_t get()
        {
            vertex_t smallest = elements.top().second;
            elements.pop();
            return smallest;
        }
    private:
        struct PairGreat
        {
            bool operator()(const PQElement& e1, const PQElement& e2) const
            {
                return e1.first>e2.first;
            }
        };
        std::priority_queue<PQElement, std::vector<PQElement>, PairGreat> elements;
    };

    //返回从start 到其它点的最短路径， 如果distancemap中没有v，那么v就到达不了
    static std::pair<DistanceMap, VertexMap>
    my_dijkstra_shortest_path_all(const G &g, vertex_t start)
    {
        PriorityQueue open_set;
        VertexSet close_set;
        VertexMap came_from;
        DistanceMap cost_so_far;

        open_set.put(start, 0);
//        came_from[start] = start; //我们的算法返回路径中不含有start点
        cost_so_far[start] = 0;

        while (!open_set.empty()) {
            vertex_t smallest = open_set.get();
            close_set.insert(smallest);

            for (const auto &next : g.neighbors(smallest)) {
                if (close_set.find(next) != end(close_set))
                    continue;

                distance_t new_cost = cost_so_far[smallest] + g.distance(smallest, next);
                if (cost_so_far.find(next) == end(cost_so_far) || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    came_from[next] = smallest;
                    open_set.put(next, new_cost);
                }
            }
        }
        return std::make_pair(cost_so_far, came_from);
    }

    // 返回所有最短路径， 如果不能到达 distance = max
    static std::pair<VertexList, distance_t>
    my_dijkstra_shortest_path(const G &g, vertex_t start, vertex_t finish)
    {
        PriorityQueue open_set;
        VertexSet close_set;
        VertexMap came_from;
        DistanceMap cost_so_far;
        VertexList path;
        distance_t dist = max_distant;

        open_set.put(start, 0);
//        came_from[start] = start; //我们的算法返回路径中不含有start点
        cost_so_far[start] = 0;

        while (!open_set.empty()) {
            vertex_t smallest = open_set.get();
            close_set.insert(smallest);

            if (smallest == finish) {
                path = find_path(finish, came_from);
                dist = cost_so_far[finish];
                break;
            }

            for (const auto &next : g.neighbors(smallest)) {
                if (close_set.find(next) != end(close_set))
                    continue;

                distance_t new_cost = cost_so_far[smallest] + g.distance(smallest, next);
                if (cost_so_far.find(next) == end(cost_so_far) || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    came_from[next] = smallest;
                    open_set.put(next, new_cost);
                }
            }
        }
        return std::make_pair(path, dist);
    }
};

#endif // Dijkstra_H


