#include "movelist.h"

void MoveList::check_loop_push_back(Direction d)
{
    if (!empty() && is_reverse(d, back()))
        pop_back();
    else
        std::list<Direction>::push_back(d);
}

void MoveList::check_loop_append(const MoveList &ml)
{
    for (auto d : ml)
        check_loop_push_back(d);
}
