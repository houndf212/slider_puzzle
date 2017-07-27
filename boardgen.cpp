#include "boardgen.h"
#include <random>
#include <chrono>
#include "board_api.h"

// 计算逆序对
static int count_inversion(const std::vector<Matrix::value_type> &vec)
{
    int count = 0;
    for(int i=0; i<vec.size()-1; ++i) {
        for(int j=i+1; j<vec.size(); ++j) {
            if(vec[i]>vec[j])
                count++;
        }
    }
    return count;
}

void BoardGen::gen(Matrix *board)
{
    using namespace std;
    typedef std::default_random_engine::result_type type_t;
    type_t seed = chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng;
    rng.seed(seed);

    auto frng = [&rng](int n) {
        return rng() % n;
    };

    int size = board->row_size()*board->col_size();
    std::vector<Matrix::value_type> vec(size-1, 0);
    //0 放最后，计算逆序对的时候不计算最后一个
    std::iota(begin(vec), end(vec), 1);

    std::random_shuffle(begin(vec), end(vec), frng);

    int inversion = count_inversion(vec);

    //如果逆序对个数为奇数，那么交换第一和第二
    if (inversion % 2 != 0)
        std::swap(vec[0], vec[1]);

    //0始终放在最后
    vec.push_back(Board_API::null_value);

    int index = 0;
    for (int row=0; row<board->row_size(); ++row) {
        for (int col=0; col<board->col_size(); ++col) {
            board->set(Pos(row, col), vec[index++]);
        }
    }
}
