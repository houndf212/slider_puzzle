#include "boardgen.h"
#include <random>
#include <chrono>
#include "board_api.h"

// TODO  怎么实现一个合理的算法产生一个随机的
// 随机产生一个 排列 只有一半的几率能解 ，那怎么修改不能解的情况， 需要考虑查下资料完成这个功能
void BoardGen::gen(Matrix *board)
{
    using namespace std;
    typedef std::default_random_engine::result_type type_t;
    type_t seed = chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> dist(1, 4);
    std::default_random_engine rng;
    rng.seed(seed);
    int size = board->row_size()*board->col_size();
    int n = std::max( int(rng() % size*10), size*5);
    while(n-->0) {
        int d = dist(rng);
        Pos null_pos = Board_API::get_null_pos(*board);
        switch (d) {
        case 1:
            Board_API::hint_null_move(board, null_pos, Board::Null_Up);
            break;
        case 2:
            Board_API::hint_null_move(board, null_pos, Board::Null_Down);
            break;
        case 3:
            Board_API::hint_null_move(board, null_pos, Board::Null_Left);
            break;
        case 4:
            Board_API::hint_null_move(board, null_pos, Board::Null_Right);
            break;
        default:
            assert(false);
            break;
        }
    }
}
