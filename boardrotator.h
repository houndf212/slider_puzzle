﻿#ifndef BOARDROTATOR_H
#define BOARDROTATOR_H
#include "moverparam.h"

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
    static bool rotate(MoverParam *param, Pos p1, ClockDirection clock);
};

#endif // BOARDROTATOR_H
