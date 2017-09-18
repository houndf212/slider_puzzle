#include "linemover.h"
#include "numbermover.h"
#include "boardrotator.h"

#ifndef NDEBUG
static bool check_number(Pos p, const Board &board)
{
    return board.origin_value(p) == board.pos_value(p);
}
#endif

bool LineMover::finish_line(PosList line, MoverParam *param)
{
    assert(line.size() >= 2);
    assert(check_is_line(line));

    // 特殊处理最后一个情况
    //判断是 下上  还是左右
    bool left_right = line.front().row() == line.back().row();
    Pos last = line.back();
    line.pop_back();

    while (!line.empty()) {
        Pos p = line.front();
        line.pop_front();
        int value = param->board.origin_value(p);
        bool ret = NumberMover::find_value_moves(value, param);
        if (ret == true) {
            param->fixed_matrix.set_fixed(p);
            assert(check_number(p, param->board));
        }
        else {
            return false;
        }
    }
    bool b = move_line_end(last, param, left_right);
    if (b==true) {
        param->fixed_matrix.set_fixed(last);
        assert(check_number(last, param->board));
    }
    return b;
}

bool LineMover::move_line_end(Pos last, MoverParam *param, bool left_right)
{
    int last_value = param->board.origin_value(last);
    Pos current_last = param->board.value_pos(last_value);

    // 如果 刚好就在last位置上
    if(current_last == last) {
        return true;
    }
    /* 1 0
     * ? 2
     * ? ？
    */
    // 如果 0 在last "并且" 刚好 last_value 在 last "下"面
    // 备注： 这只是下面的一种特殊情况, 这里快速处理
    Pos down_last = last;
    if (left_right)
        down_last.row()++;
    else
        down_last.col()++;

    if (param->board.get_null_pos() == last && current_last == down_last) {
        Direction d = param->board.test_null_move_to(current_last);
        assert(d != Direction::NotValid);
        bool b = param->board.null_move(d);
        assert(b==true);
        Q_UNUSED(b);
        param->move_list.check_loop_push_back(d);
        return true;
    }
    //非特殊情况
    Pos p_null = last;
    Pos p_last = last;

    Pos p_r_up = last;
    Pos p_r_down = last;

    if (left_right) {
        p_last.row()+=2;

        p_r_up.col()--;

        p_r_down.row()++;
        p_r_down.col()--;
    }
    else {
        p_last.col()+=2;

//        p_r_up = last;
        p_r_down.col()++;
    }

    //1这里可能产生 ‘循环’
    // 1 ? 2   1 ? 2    1 0 2    1 2 0  旋转上面第一步   1 0 2   1 ? 2   1 ? 2
    // ? ? 0 ->? 0 ? -> ? ? ? -> ? ? ?  ------------>  ? ? ? ->? 0 ? ->? ? 0
    // ? ? 3   ? ? 3    ? ? 3    ? ? 3                 ? ? 3   ? ? 3   ? ? 3
    //2 循环很可能是递归的，找到一个循环需要处理下一个循环
    //3 妈的，经过验证除了这里有循环其他地方也会产生循环，
    //  用自定义movelist来解决！！！不在乎这点性能了！！！反正能够解出来！！

    //移动最后一个到 预定位置的下两格子
    bool ret1 = NumberMover::find_moves(current_last, p_last, param);
    if(ret1 != true)
        return false;

    //移动0 到last位置
    // 临时固定p_last点
    {
        temp_fixer auto_unfixer(p_last, param->fixed_matrix);
        bool ret2 = NumberMover::find_null_to(p_null, param);
        //    auto_unfixer.unfix(); //析构函数主动调用
        if (ret2 != true)
            return false;
    }

    /* 1 0
     * ? ?
     * ? 2
    */
    //上面 正向旋转
    bool rm1 = BoardRotator::rotate(param, p_r_up, BoardRotator::ClockWise);
    if (rm1!=true)
        return false;

    /* ? 1
     * ? 0
     * ? 2
    */
    //下面 逆向旋转
    bool rm2 = BoardRotator::rotate(param, p_r_down, BoardRotator::AntiClock);
    if (rm2!=true)
        return false;

    /* ? 1
     * 0 2
     * ? ?
    */

    //上面 逆向旋转
    bool rm3 = BoardRotator::rotate(param, p_r_up, BoardRotator::AntiClock);
    if (rm3!=true)
        return false;

    /* 1 2
     * ? 0
     * ? ?
    */
    return true;
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
