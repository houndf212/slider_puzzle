#include "boardrotator.h"


//  1 2
//  3 4
bool BoardRotator::rotate(MoverParam *param, Pos p1, BoardRotator::ClockDirection clock)
{
    assert(param->board.isInBoard(p1));

    Pos p2(p1.row(), p1.col()+1);
    if (!param->board.isInBoard(p2))
        return false;

    Pos p3(p1.row()+1, p1.col());
    if (!param->board.isInBoard(p3))
        return false;

    Pos p4(p2.row()+1, p2.col());
    assert(param->board.isInBoard(p4));

    Pos p0 = param->board.get_null_pos();
    if (p0!=p1 && p0!=p2 && p0!=p3 && p0!=p4)
        return false;

    MoveList move_list;
    if (clock == ClockWise) {
        if (p0 == p1) {
            move_list.check_loop_push_back(Direction::Null_Down);
            move_list.check_loop_push_back(Direction::Null_Right);
            move_list.check_loop_push_back(Direction::Null_Up);
        }
        else if (p0 == p2) {
            move_list.check_loop_push_back(Direction::Null_Left);
            move_list.check_loop_push_back(Direction::Null_Down);
            move_list.check_loop_push_back(Direction::Null_Right);
        }
        else if (p0 == p3) {
            move_list.check_loop_push_back(Direction::Null_Right);
            move_list.check_loop_push_back(Direction::Null_Up);
            move_list.check_loop_push_back(Direction::Null_Left);
        }
        else if (p0 == p4) {
            move_list.check_loop_push_back(Direction::Null_Up);
            move_list.check_loop_push_back(Direction::Null_Left);
            move_list.check_loop_push_back(Direction::Null_Down);
        }
    }
    else {
        if (p0 == p1) {
            move_list.check_loop_push_back(Direction::Null_Right);
            move_list.check_loop_push_back(Direction::Null_Down);
            move_list.check_loop_push_back(Direction::Null_Left);
        }
        else if (p0 == p2) {
            move_list.check_loop_push_back(Direction::Null_Down);
            move_list.check_loop_push_back(Direction::Null_Left);
            move_list.check_loop_push_back(Direction::Null_Up);
        }
        else if (p0 == p3) {
            move_list.check_loop_push_back(Direction::Null_Up);
            move_list.check_loop_push_back(Direction::Null_Right);
            move_list.check_loop_push_back(Direction::Null_Down);
        }
        else if (p0 == p4) {
            move_list.check_loop_push_back(Direction::Null_Left);
            move_list.check_loop_push_back(Direction::Null_Up);
            move_list.check_loop_push_back(Direction::Null_Right);
        }
    }
    for (Direction d: move_list) {
        bool b = param->board.null_move(d);
        assert(b==true);
        Q_UNUSED(b);
        param->move_list.check_loop_push_back(d);
    }
    return true;
}
