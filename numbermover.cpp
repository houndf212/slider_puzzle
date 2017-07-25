#include "numbermover.h"
#include "matrixgraph.h"

bool NumberMover::find_null_to(Pos to, MoverParam *param)
{
    Pos null_start = param->board.get_null_pos();
    auto null_line = core_move_line(null_start, to, param->fixed_matrix);
    if (null_line.second == false)
        return false;

    for (const Pos &p : null_line.first) {
        Board::Direction d = param->board.test_null_move_to(p);
        assert(d!=Board::NotValid);
        bool b = param->board.null_move(d);
        assert(b == true);
        param->move_list.check_loop_push_back(d);
    }
    return true;
}

bool NumberMover::find_value_moves(int val, MoverParam *param)
{
    //第一步  找到 从 要移动的点到移动位置的点 的路径
    Pos start = param->board.value_pos(val);
    Pos finish = param->board.origin_pos(val);
    return find_moves(start, finish, param);
}

bool NumberMover::find_moves(Pos start, Pos finish, MoverParam *param)
{
    assert(start!=param->board.get_null_pos());
    auto line = core_move_line(start, finish, param->fixed_matrix);

    if (line.second == false)
        return false;

    PosList path = line.first;
    while(!path.empty()) {
        // 第二步 找到 0 到路径中的点的路径
        Pos to = path.front();
        path.pop_front();

        temp_fixer auto_unfixer(start, param->fixed_matrix);
        //第三步  移动 0 到指定位置
        bool null_line = find_null_to(to, param);
//        auto_unfixer.unfix(); //析构函数主动调用
        if (null_line == true) {
            // 第四步 交换 0和点
            Board::Direction d = param->board.test_null_move_to(start);
            assert(d!=Board::NotValid);
            bool b = param->board.null_move(d);
            assert(b==true);
            param->move_list.check_loop_push_back(d);
            start = to;
        }
        else {
            return false;
        }
    }
    return true;
}

std::pair<PosList, bool> NumberMover::core_move_line(Pos start, Pos finish, const BoolMatrix &fixed_matrix)
{
    if (start == finish)
        return std::make_pair(PosList(), true);

    typedef MatrixGraph MG;
    typedef Dijkstra<MG> G;

    MG g(fixed_matrix);
//    auto p = G::shortest_path(g, start, finish);
    auto p = G::AStart_path(g, start, finish);
    bool isReach = p.second != G::max_distant;
    return std::make_pair(p.first, isReach);
}
