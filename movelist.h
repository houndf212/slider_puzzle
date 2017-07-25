#ifndef MOVELIST_H
#define MOVELIST_H
#include <list>
#include "movedirection.h"

class MoveList : public std::list<Direction>
{
public:
    void check_loop_push_back(Direction d);
    void check_loop_append(const MoveList& ml);
private:
    //隐藏 父类的函数,只需要一个同名的函数即可
    void push_back();
//    void push_back(Direction d);
//    void push_back(const Direction &d);
//    void push_back(Direction &&d);
};

#endif // MOVELIST_H
