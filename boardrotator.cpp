#include "boardrotator.h"


//  1 2
//  3 4
MoveVector BoardRotator::rotate(Board *board, Pos p1, BoardRotator::ClockDirection clock)
{
    MoveVector mlist;
    assert(board->isInBoard(p1));

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
            mlist.push_back(Board::Null_Down);
            mlist.push_back(Board::Null_Right);
            mlist.push_back(Board::Null_Up);
        }
        else if (p0 == p2) {
            mlist.push_back(Board::Null_Left);
            mlist.push_back(Board::Null_Down);
            mlist.push_back(Board::Null_Right);
        }
        else if (p0 == p3) {
            mlist.push_back(Board::Null_Right);
            mlist.push_back(Board::Null_Up);
            mlist.push_back(Board::Null_Left);
        }
        else if (p0 == p4) {
            mlist.push_back(Board::Null_Up);
            mlist.push_back(Board::Null_Left);
            mlist.push_back(Board::Null_Down);
        }
    }
    else {
        if (p0 == p1) {
            mlist.push_back(Board::Null_Right);
            mlist.push_back(Board::Null_Down);
            mlist.push_back(Board::Null_Left);
        }
        else if (p0 == p2) {
            mlist.push_back(Board::Null_Down);
            mlist.push_back(Board::Null_Left);
            mlist.push_back(Board::Null_Up);
        }
        else if (p0 == p3) {
            mlist.push_back(Board::Null_Up);
            mlist.push_back(Board::Null_Right);
            mlist.push_back(Board::Null_Down);
        }
        else if (p0 == p4) {
            mlist.push_back(Board::Null_Left);
            mlist.push_back(Board::Null_Up);
            mlist.push_back(Board::Null_Right);
        }
    }
    for (Board::Direction d: mlist) {
        bool b = board->null_move(d);
        assert(b==true);
    }
    return mlist;
}
