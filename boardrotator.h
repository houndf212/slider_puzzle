#ifndef BOARDROTATOR_H
#define BOARDROTATOR_H
#include "board.h"
#include <vector>

typedef std::vector<Board::Direction> MoveList;

class BoardRotator
{
public:
    enum ClockDirection
    {
        ClockWise,
        AntiClock,
    };
public:
/*
 *  1 1
 *  1 0
 *
 *  1. p 对应的左上角点位，
 *  2. 相应四个位置必须含有null
 *
 *
*/
    static MoveList rotate(Board &b, Pos p1, ClockDirection clock);
};

#endif // BOARDROTATOR_H