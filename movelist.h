#ifndef MOVELIST_H
#define MOVELIST_H
#include "board.h"

class MoveList : public std::list<Board::Direction>
{
public:
    void check_loop_push_back(Board::Direction d);
    void check_loop_append(const MoveList& ml);
private:
    //隐藏 父类的函数,只需要一个同名的函数即可
    void push_back();
//    void push_back(Board::Direction d);
//    void push_back(const Board::Direction &d);
//    void push_back(Board::Direction &&d);
};

#endif // MOVELIST_H
