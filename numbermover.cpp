#include "numbermover.h"
#include "matrixgraph.h"

std::pair<MoveList, bool> NumberMover::find_null_to(Pos to, Board *board, const BoolMatrix &fixed)
{
    Pos null_start = board->get_null_pos();
    auto null_line = find_move_line(null_start, to, fixed);
    if (null_line.second == false)
        return std::make_pair(MoveList(), false);

    MoveList mlist;
    for (const Pos &p : null_line.first) {
        Board::Direction d = board->test_null_move_to(p);
        assert(d!=Board::NotValid);
        bool b = board->null_move(d);
        assert(b == true);
        mlist.push_back(d);
    }
    return std::make_pair(mlist, true);
}

std::pair<MoveList, bool>
NumberMover::find_value_moves(int val, Board *board, const BoolMatrix &fixed_matrix)
{
    //第一步  找到 从 要移动的点到移动位置的点 的路径
    Pos start = board->value_pos(val);
    Pos finish = board->origin_pos(val);
    return find_moves(start, finish, board, fixed_matrix);
}

std::pair<MoveList, bool>
NumberMover::find_moves(Pos start, Pos finish, Board *board, const BoolMatrix &fixed_matrix)
{
    assert(!start.equal(board->get_null_pos()));
    auto line = find_move_line(start, finish, fixed_matrix);

    if (line.second == false)
        return std::make_pair(MoveList(), false);

    MoveList mlist;

    PosList path(begin(line.first), end(line.first));
    while(!path.empty()) {
        // 第二步 找到 0 到路径中的点的路径
        Pos to = path.front();
        path.pop_front();

        BoolMatrix fixed = fixed_matrix;
        fixed.set_fixed(start);

        //第三步  移动 0 到指定位置
        auto null_line = find_null_to(to, board, fixed);
        if (null_line.second == true) {
            std::copy(begin(null_line.first), end(null_line.first), std::back_inserter(mlist));
            // 第四步 交换 0和点
            Board::Direction d = board->test_null_move_to(start);
            assert(d!=Board::NotValid);
            bool b = board->null_move(d);
            assert(b==true);
            mlist.push_back(d);
            start = to;
        }
        else {
            return std::make_pair(MoveList(), false);
        }
    }
    return std::make_pair(mlist, true);
}

std::pair<PosList, bool> NumberMover::find_move_line(Pos start, Pos finish, const BoolMatrix &fixed_matrix)
{
    if (start == finish)
        return std::make_pair(PosList(), true);

    MatrixGraph g(fixed_matrix);
    auto p = g.dijkstra_shortest_path(start, finish);
    bool isReach = p.second != g.max_distant;
    return std::make_pair(p.first, isReach);
}
