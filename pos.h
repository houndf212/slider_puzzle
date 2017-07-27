#ifndef POS_H
#define POS_H
#include <list>
#include <vector>
#include "basic_pos.h"

typedef Basic_Pos<char> Pos;

typedef std::vector<Pos> PosVector;
typedef std::list<Pos> PosList;

#endif // POS_H
