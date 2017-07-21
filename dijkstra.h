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
        return ucs_dijkstra_shortest_path(g, start, finish);
    }

    //返回从start 到其它点的最短路径， 如果first中没有v，那么v就到达不了
    static std::pair<DistanceMap, VertexMap>
    shortest_path_all(const G &g, vertex_t start)
    {
        return ucs_dijkstra_shortest_path_all(g, start);
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

/// from wiki
///Practical optimizations and infinite graphs[edit]
///In common presentations of Dijkstra's algorithm, initially all nodes are entered into the priority queue.
/// This is, however, not necessary: the algorithm can start with a priority queue that contains only one item,
/// and insert new items as they are discovered (instead of doing a decrease-key, check whether the key is in the queue;
/// if it is, decrease its key, otherwise insert it).[3]:198 This variant has the same worst-case bounds as the common variant, but maintains a smaller priority queue in practice, speeding up the queue operations.[4]

///Moreover, not inserting all nodes in a graph makes it possible to extend the algorithm to find the shortest path from a single source to the closest of a set of target nodes on infinite graphs or those too large to represent in memory.
/// The resulting algorithm is called uniform-cost search (UCS) in the artificial intelligence literature[4][11][12] and can be expressed in pseudocode as
/*  procedure UniformCostSearch(Graph, start, goal)
    node ← start
    cost ← 0
    frontier ← priority queue containing node only
    explored ← empty set
    do
      if frontier is empty
        return failure
      node ← frontier.pop()
      if node is goal
        return solution
      explored.add(node)
      for each of node's neighbors n
        if n is not in explored or frontier
            frontier.add(n)
        else if n is in frontier with higher cost
            replace existing node with n

            */
    //返回从start 到其它点的最短路径， 如果distancemap中没有v，那么v就到达不了
    static std::pair<DistanceMap, VertexMap>
    ucs_dijkstra_shortest_path_all(const G &g, vertex_t start)
    {
        VertexVector open_set; //为搜索的，与确定过相连的集合
        VertexSet close_set; //确定最短路径的集合
        DistanceMap cost_so_far; //用来标记已经知道的路径（不一定是最短的）
        VertexMap came_from; //记录最短路径的前继

        auto comparator = [&cost_so_far] (vertex_t left, vertex_t right) {
            return cost_so_far[left] > cost_so_far[right]; };

        open_set.push_back(start);
        std::push_heap(begin(open_set), end(open_set), comparator);
        cost_so_far[start] = 0;
//        came_from[start] = start; //我们的算法返回路径中不含有start点

        while (!open_set.empty()) {
            std::pop_heap(begin(open_set), end(open_set), comparator);
            vertex_t smallest = open_set.back();
            open_set.pop_back();

            close_set.insert(smallest);

            for (const auto &next : g.neighbors(smallest)) {
                if (close_set.find(next) != end(close_set))
                    continue;

                distance_t new_cost = cost_so_far[smallest] + g.distance(smallest, next);
                if (cost_so_far.find(next) == end(cost_so_far) || new_cost < cost_so_far[next]) {
                    cost_so_far[next] = new_cost;
                    came_from[next] = smallest;
                    open_set.push_back(next);
                    std::push_heap(begin(open_set), end(open_set), comparator);
                }
            }
        }
        return std::make_pair(cost_so_far, came_from);
    }

    // 返回所有最短路径， 如果不能到达 distance = max
    static std::pair<VertexList, distance_t>
    ucs_dijkstra_shortest_path(const G &g, vertex_t start, vertex_t finish)
    {
        VertexVector open_set; //为搜索的，与确定过相连的集合
        VertexSet close_set; //确定最短路径的集合
        DistanceMap cost_so_far; //用来标记已经知道的路径（不一定是最短的）
        VertexMap came_from; //记录最短路径的前继

        VertexList path;
        distance_t dist = max_distant;


        auto comparator = [&cost_so_far] (vertex_t left, vertex_t right) {
            return cost_so_far[left] > cost_so_far[right]; };

        open_set.push_back(start);
        std::push_heap(begin(open_set), end(open_set), comparator);
        cost_so_far[start] = 0;
//        came_from[start] = start; //我们的算法返回路径中不含有start点

        while (!open_set.empty()) {
            std::pop_heap(begin(open_set), end(open_set), comparator);
            vertex_t smallest = open_set.back();
            open_set.pop_back();

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
                    open_set.push_back(next);
                    std::push_heap(begin(open_set), end(open_set), comparator);
                }
            }
        }
        return std::make_pair(path, dist);
    }
};

#endif // Dijkstra_H


