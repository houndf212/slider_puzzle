#ifndef MOVELIST_H
#define MOVELIST_H
#include "board.h"

class MoveList : public std::list<Board::Direction>
{
public:
    void check_loop_push_back(Board::Direction d);
    void check_loop_append(const MoveList& ml);
private:
    //隐藏 父类的函数
//    void push_back();
};

#endif // MOVELIST_H
