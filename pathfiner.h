#ifndef PATHFINER_H
#define PATHFINER_H
#include<vector>
#include "pos.h"

class PathFiner
{
public:
    static std::vector<Pos> find_path(Pos start, Pos end);
};

#endif // PATHFINER_H
