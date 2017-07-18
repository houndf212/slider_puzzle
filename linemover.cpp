#include "linemover.h"
#include "numbermover.h"
#include "boardrotator.h"

static bool check_number(Pos p, const Board &board)
{
    return board.origin_value(p) == board.pos_value(p);
}

MoveList LineMover::finish_line(PosList line, Board *board, BoolMatrix *fixed_matrix)
{
    assert(line.size() >= 2);
    assert(is_line(line));

    // 特殊处理最后一个情况
    //判断是 下上  还是左右
    bool left_right = line.front().row() == line.back().row();
    Pos last = line.back();
    line.pop_back();

    MoveList mlist;
    while (!line.empty()) {
        Pos p = line.front();
        line.pop_front();
        int value = board->origin_value(p);
        auto ret = NumberMover::find_value_moves(value, board, *fixed_matrix);
        assert(ret.second == true);
        mlist.check_loop_append(ret.first);
        fixed_matrix->set_fixed(p);
        assert(check_number(p, *board));
//        board->print();
//        fixed_matrix->print();
    }
    move_line_end(last, board, fixed_matrix, &mlist, left_right);
    return mlist;
}

void LineMover::move_line_end(Pos last, Board *board, BoolMatrix *fixed_matrix, MoveList* mlist, bool left_right)
{
    int last_value = board->origin_value(last);
    Pos current_last = board->value_pos(last_value);

    // 如果 刚好就在last位置上
    if(current_last == last) {
        fixed_matrix->set_fixed(last);
        assert(check_number(last, *board));
        return;
    }
    /* 1 0
     * ? 2
     * ? ？
    */
    // 如果 0 在last "并且" 刚好 last_value 在 last "下"面
    // 备注： 这只是下面的一种特殊情况, 这里快速处理
    if (board->get_null_pos() == last) {
        Board::Direction test_d = board->test_null_move_to(current_last);
        if (test_d != Board::NotValid) {
            bool b = board->null_move(test_d);
            assert(b==true);
            mlist->check_loop_push_back(test_d);
            fixed_matrix->set_fixed(last);
            assert(check_number(last, *board));
            return;
        }
    }
    //非特殊情况
    Pos p_null = last;
    Pos p_last;

    Pos p_r_up;
    Pos p_r_down;

    if (left_right) {
        p_last = {last.row()+2, last.col()};

        p_r_up = {last.row(), last.col()-1};
        p_r_down = {last.row()+1, last.col()-1};
    }
    else {
        p_last = {last.row(), last.col()+2};

        p_r_up = last;
        p_r_down = {last.row(), last.col()+1};
    }

    //1这里可能产生 ‘循环’
    // 1 ? 2   1 ? 2    1 0 2    1 2 0  旋转上面第一步   1 0 2   1 ? 2   1 ? 2
    // ? ? 0 ->? 0 ? -> ? ? ? -> ? ? ?  ------------>  ? ? ? ->? 0 ? ->? ? 0
    // ? ? 3   ? ? 3    ? ? 3    ? ? 3                 ? ? 3   ? ? 3   ? ? 3
    //2 循环很可能是递归的，找到一个循环需要处理下一个循环
    //3 妈的，经过验证除了这里有循环其他地方也会产生循环，
    //  用自定义movelist来解决！！！不在乎这点性能了！！！反正能够解出来！！

    //移动最后一个到 预定位置的下两格子
    auto ret1 = NumberMover::find_moves(current_last, p_last, board, *fixed_matrix);
    assert(ret1.second == true);
    mlist->check_loop_append(ret1.first);
    fixed_matrix->set_fixed(p_last);


    //移动0 到last位置
    auto ret2 = NumberMover::find_null_to(p_null, board, *fixed_matrix);
    assert(ret2.second == true);
    mlist->check_loop_append(ret2.first);
    fixed_matrix->set_unfixed(p_last);

    /* 1 0
     * ? ?
     * ? 2
    */
    //上面 正向旋转
    auto rm1 = BoardRotator::rotate(board, p_r_up, BoardRotator::ClockWise);
    mlist->check_loop_append(rm1);

    /* ? 1
     * ? 0
     * ? 2
    */
    //下面 逆向旋转
    auto rm2 = BoardRotator::rotate(board, p_r_down, BoardRotator::AntiClock);
    mlist->check_loop_append(rm2);
    /* ? 1
     * 0 2
     * ? ?
    */

    //上面 逆向旋转
    auto rm3 = BoardRotator::rotate(board, p_r_up, BoardRotator::AntiClock);
    mlist->check_loop_append(rm3);
    /* 1 2
     * ? 0
     * ? ?
    */

    fixed_matrix->set_fixed(last);
    assert(check_number(last, *board));
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
