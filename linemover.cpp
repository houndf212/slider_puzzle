#include "linemover.h"
#include "numbermover.h"
#include "boardrotator.h"

MoveList LineMover::finish_line(PosList line, Board *board, BoolMatrix *fixed_matrix)
{
    assert(line.size() >= 2);
    assert(is_line(line));

    // 特殊处理最后一个情况
    //判断是 下上  还是左右
    bool is_left_right = line.front().row() == line.back().row();
    Pos last = line.back();
    line.pop_back();

    MoveList mlist;
    while (!line.empty()) {
        Pos p = line.front();
        line.pop_front();
        int value = board->origin_value(p);
        auto ret = NumberMover::find_value_moves(value, board, *fixed_matrix);
        assert(ret.second == true);
        movelist_append(&mlist, ret.first);
        fixed_matrix->set_fixed(p);
        board->print();
        fixed_matrix->print();
    }

    int last_value = board->origin_value(last);
    Pos current_last = board->value_pos(last_value);

    // 如果 刚好就在last位置上
    if(current_last == last) {
        fixed_matrix->set_fixed(last);
        return mlist;
    }
    /* 1 0
     * ? 2
     * ? ？
    */
    // 如果刚好 last_value 在 last 下面
    Board::Direction test_d = board->test_null_move_to(current_last);
    if (test_d != Board::NotValid) {
        bool b = board->null_move(test_d);
        assert(b==true);
        mlist.push_back(test_d);
        fixed_matrix->set_fixed(last);
        return mlist;
    }

    Pos p_null;
    Pos p_last;

    Pos p_r_up;
    Pos p_r_down;

    if (is_left_right) {
        p_null = {last.row()+1, last.col()};
        p_last = {last.row()+2, last.col()};

        p_r_up = {last.row(), last.col()-1};
        p_r_down = {last.row()+1, last.col()-1};
    }
    else {
        p_null = {last.row(), last.col()+1};
        p_last = {last.row(), last.col()+2};

        p_r_up = last;
        p_r_down = p_null;
    }

    //移动最后一个到 预定位置的下两格子

    auto ret1 = NumberMover::find_moves(current_last, p_last, board, *fixed_matrix);
    assert(ret1.second == true);
    movelist_append(&mlist, ret1.first);
    fixed_matrix->set_fixed(p_last);

    //移动0 到预定位置的正下方
    auto ret2 = NumberMover::find_null_to(p_null, board, *fixed_matrix);
    assert(ret2.second == true);
    movelist_append(&mlist, ret2.first);
    fixed_matrix->set_unfixed(p_last);


    /* 1 ？
     * ? 0
     * ? 2
    */
    //先正向旋转上面
    auto rm1 = BoardRotator::rotate(board, p_r_up, BoardRotator::ClockWise);
    movelist_append(&mlist, rm1);
    /* ? 1
     * 0 ?
     * ? 2
    */
    //先逆向旋转下面
    auto rm2 = BoardRotator::rotate(board, p_r_down, BoardRotator::AntiClock);
    movelist_append(&mlist, rm2);
    /* ? 1
     * ? 2
     * 0 ?
    */

    // "上"一次
    Board::Direction d1 = is_left_right ? Board::Null_Up : Board::Null_Left;
    assert(d1!=Board::NotValid);
    bool b1 = board->null_move(d1);
    assert(b1==true);
    mlist.push_back(d1);

    /* ? 1
     * 0 2
     * ? ?
    */

    // 旋转一次
    auto rm3 = BoardRotator::rotate(board, p_r_up, BoardRotator::AntiClock);
    movelist_append(&mlist, rm3);
    /* 1 2
     * ? 0
     * ? ?
    */

    fixed_matrix->set_fixed(last);
    return mlist;
}

bool LineMover::is_left_right(const PosList &line)
{
    int row = line.front().row();
    int col = line.front().col();
    for (const Pos &p : line) {
        if (p.row() != row || p.col() !=col)
            return false;

        ++col;
    }
    return true;
}

bool LineMover::is_down_up(const PosList &line)
{
    int row = line.front().row();
    int col = line.front().col();
    for (const Pos &p : line) {
        if (p.col() != col || p.row() !=row)
            return false;

        --row;
    }
    return true;
}
