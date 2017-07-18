#include "movelist.h"

void MoveList::check_loop_push_back(Board::Direction d)
{
    if (!empty() && Board::is_loop(d, back())) {
        pop_back();
    }
    else
        push_back(d);
}

void MoveList::check_loop_append(const MoveList &ml)
{
    for (auto d : ml)
        check_loop_push_back(d);
}
