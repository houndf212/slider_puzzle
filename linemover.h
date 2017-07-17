#ifndef LINEMOVER_H
#define LINEMOVER_H
#include "board.h"
#include "boolmatrix.h"

class LineMover
{
public:
    static MoveVector finish_line(PosList line, Board *board, BoolMatrix *fixed_matrix);
private:
    static bool is_line(const PosList &line)
    {
        return is_left_right(line) || is_down_up(line);
    }
    static bool is_left_right(const PosList &line);

    static bool is_down_up(const PosList &line);
};

#endif // LINEMOVER_H
