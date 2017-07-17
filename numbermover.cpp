#include "numbermover.h"
#include "matrixgraph.h"

NumberMover::NumberMover(const Board &b, const BoolMatrix &fixed)
    :board(b), fixed_matrix(fixed)
{

}

std::pair<PosList, bool> NumberMover::get_move_line(int val) const
{
    Pos start = board.value_pos(val);
    Pos finish = board.origin_pos(val);
    return find_value_move_line(start, finish, fixed_matrix);
}

std::pair<PosList, bool> NumberMover::get_null_move_path(Pos to, Pos fixedPos) const
{
    Pos null_start = board.get_null_pos();
    BoolMatrix fixed = fixed_matrix;
    fixed.set_fixed(fixedPos);
    return find_value_move_line(null_start, to, fixed);
}

std::pair<MoveList, bool> NumberMover::get_all_null_move_path(int val) const
{
    Board board = this->board;

    //第一步  知道 从 要移动的点到移动位置的点 的路径
    Pos start = board.value_pos(val);
    Pos finish = board.origin_pos(val);
    auto line = find_value_move_line(start, finish, fixed_matrix);

    if (line.second == false)
        return std::make_pair(MoveList(), false);

    MoveList mlist;

    PosQueue path;
    for (const Pos &p : line.first) {
        path.push(p);
    }
    while(!path.empty()) {
        // 第二步 找到 0 到路径中的点的路径
        Pos to = path.front();
        path.pop();

        Pos null_start = board.get_null_pos();
        BoolMatrix fixed = fixed_matrix;
        fixed.set_fixed(start);
        auto null_line = find_value_move_line(null_start, to, fixed);
        if (null_line.second == true) {
            //第三步  移动 0 到指定位置
            for (const Pos &p : null_line.first) {
                Board::Direction d = board.test_null_move_to(p);
                bool b = board.null_move(d);
                assert(b == true);
                mlist.push_back(d);
            }
            // 第四步 交换 0和点
            Board::Direction d = board.test_null_move_to(start);
            bool b = board.null_move(d);
            assert(b==true);
            start = to;
        }
        else {
            return std::make_pair(MoveList(), false);
        }
    }
    return std::make_pair(mlist, true);
}

std::pair<PosList, bool> NumberMover::find_value_move_line(Pos start, Pos finish, const BoolMatrix &fixed_matrix)
{
    if (start == finish)
        return std::make_pair(PosList(), true);

    MatrixGraph g(fixed_matrix);
    auto p = g.dijkstra_shortest_path(start, finish);
    bool isReach = p.second != g.max_distant;
    return std::make_pair(p.first, isReach);
}
