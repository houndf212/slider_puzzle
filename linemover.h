#ifndef LINEMOVER_H
#define LINEMOVER_H
#include "moverparam.h"

class LineMover
{
public:
    static bool finish_line(PosList line, MoverParam *param);
private:
    static bool move_line_end(Pos last, MoverParam *param, bool left_right);
    static bool check_is_line(const PosList &line)
    {
        return is_left_right(line) || is_down_up(line);
    }
    static bool is_left_right(const PosList &line);

    static bool is_down_up(const PosList &line);
};

#endif // LINEMOVER_H
