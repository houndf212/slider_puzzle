#include "boardrotator.h"


//  1 2
//  3 4
MoveList BoardRotator::rotate(Board *board, Pos p1, BoardRotator::ClockDirection clock)
{
    assert(board->isInBoard(p1));
    MoveList mlist;

    Pos p2(p1.row(), p1.col()+1);
    if (!board->isInBoard(p2))
        return mlist;

    Pos p3(p1.row()+1, p1.col());
    if (!board->isInBoard(p3))
        return mlist;

    Pos p4(p2.row()+1, p2.col());
    assert(board->isInBoard(p4));

    Pos p0 = board->get_null_pos();

    if (clock == ClockWise) {
        if (p0 == p1) {
            mlist.check_loop_push_back(Board::Null_Down);
            mlist.check_loop_push_back(Board::Null_Right);
            mlist.check_loop_push_back(Board::Null_Up);
        }
        else if (p0 == p2) {
            mlist.check_loop_push_back(Board::Null_Left);
            mlist.check_loop_push_back(Board::Null_Down);
            mlist.check_loop_push_back(Board::Null_Right);
        }
        else if (p0 == p3) {
            mlist.check_loop_push_back(Board::Null_Right);
            mlist.check_loop_push_back(Board::Null_Up);
            mlist.check_loop_push_back(Board::Null_Left);
        }
        else if (p0 == p4) {
            mlist.check_loop_push_back(Board::Null_Up);
            mlist.check_loop_push_back(Board::Null_Left);
            mlist.check_loop_push_back(Board::Null_Down);
        }
    }
    else {
        if (p0 == p1) {
            mlist.check_loop_push_back(Board::Null_Right);
            mlist.check_loop_push_back(Board::Null_Down);
            mlist.check_loop_push_back(Board::Null_Left);
        }
        else if (p0 == p2) {
            mlist.check_loop_push_back(Board::Null_Down);
            mlist.check_loop_push_back(Board::Null_Left);
            mlist.check_loop_push_back(Board::Null_Up);
        }
        else if (p0 == p3) {
            mlist.check_loop_push_back(Board::Null_Up);
            mlist.check_loop_push_back(Board::Null_Right);
            mlist.check_loop_push_back(Board::Null_Down);
        }
        else if (p0 == p4) {
            mlist.check_loop_push_back(Board::Null_Left);
            mlist.check_loop_push_back(Board::Null_Up);
            mlist.check_loop_push_back(Board::Null_Right);
        }
    }
    for (Board::Direction d: mlist) {
        bool b = board->null_move(d);
        assert(b==true);
    }
    return mlist;
}
