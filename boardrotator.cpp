#include "boardrotator.h"


//  1 2
//  3 4
MoveList BoardRotator::rotate(Board &b, Pos p1, BoardRotator::ClockDirection clock)
{
    MoveList mlist;
    assert(b.isInBoard(p1));

    Pos p2(p1.row(), p1.col()+1);
    if (!b.isInBoard(p2))
        return mlist;

    Pos p3(p1.row()+1, p1.col());
    if (!b.isInBoard(p3))
        return mlist;

    Pos p4(p2.row()+1, p2.col());
    assert(b.isInBoard(p4));

    Pos p0 = b.get_null_pos();

    if (clock == ClockWise) {
        if (p0 == p1) {
            mlist.push_back(Board::Up);
            mlist.push_back(Board::Left);
            mlist.push_back(Board::Down);
        }
        else if (p0 == p2) {
            mlist.push_back(Board::Right);
            mlist.push_back(Board::Up);
            mlist.push_back(Board::Left);
        }
        else if (p0 == p3) {
            mlist.push_back(Board::Left);
            mlist.push_back(Board::Down);
            mlist.push_back(Board::Right);
        }
        else if (p0 == p4) {
            mlist.push_back(Board::Down);
            mlist.push_back(Board::Right);
            mlist.push_back(Board::Up);
        }
    }
    else {
        if (p0 == p1) {
            mlist.push_back(Board::Left);
            mlist.push_back(Board::Up);
            mlist.push_back(Board::Right);
        }
        else if (p0 == p2) {
            mlist.push_back(Board::Up);
            mlist.push_back(Board::Right);
            mlist.push_back(Board::Down);
        }
        else if (p0 == p3) {
            mlist.push_back(Board::Down);
            mlist.push_back(Board::Left);
            mlist.push_back(Board::Up);
        }
        else if (p0 == p4) {
            mlist.push_back(Board::Right);
            mlist.push_back(Board::Down);
            mlist.push_back(Board::Left);
        }
    }
    return mlist;
}
