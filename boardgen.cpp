#include "boardgen.h"
#include <random>
#include <chrono>

void BoardGen::gen(Board *board)
{
    using namespace std;
    typedef std::default_random_engine::result_type type_t;
    type_t seed = chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> dist(1, 4);
    std::default_random_engine rng;
    rng.seed(seed);
    int n = rng() % 1000;
    while(n-->0) {
        int d = dist(rng);
        switch (d) {
        case 1:
            board->move(Board::Null_Up);
            break;
        case 2:
            board->move(Board::Null_Down);
            break;
        case 3:
            board->move(Board::Null_Left);
            break;
        case 4:
            board->move(Board::Null_Right);
            break;
        default:
            assert(false);
            break;
        }
    }
}
