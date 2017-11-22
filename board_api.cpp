#include "board_api.h"
#include <random>
#include <chrono>

PosVector Board_API::build_index(const Matrix &m)
{
    PosVector value_index;
    value_index.resize(m.row_size()*m.col_size()+start_value-1);

    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            auto val = m.get(p);
            assert(0<=val && static_cast<size_t>(val)<value_index.size());
            value_index[val] = p;
        }
    }
    return value_index;
}

void Board_API::move(Pos *p, Direction d)
{
    switch (d) {
    case Direction::Null_Up:
        p->row()--;
        break;
    case Direction::Null_Down:
        p->row()++;
        break;
    case Direction::Null_Left:
        p->col()--;
        break;
    case Direction::Null_Right:
        p->col()++;
        break;
    default:
        assert(false);
        break;
    }
}

// 计算逆序对
static int count_inversion(const std::vector<Matrix::value_type> &vec)
{
    int count = 0;
    for(size_t i=0; i<vec.size()-1; ++i) {
        for(size_t j=i+1; j<vec.size(); ++j) {
            if(vec[i]>vec[j])
                count++;
        }
    }
    return count;
}

PosVector Board_API::gen(Matrix *board)
{
    using namespace std;
    typedef std::default_random_engine::result_type type_t;
    type_t seed = chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng;
    rng.seed(seed);

    int size = board->row_size()*board->col_size();
    std::vector<Matrix::value_type> vec(size-1, 0);
    //0 放最后，计算逆序对的时候不计算最后一个
    std::iota(begin(vec), end(vec), Board_API::start_value);

    std::shuffle(begin(vec), end(vec), rng);

    int inversion = count_inversion(vec);

    //如果逆序对个数为奇数，那么交换第一和第二
    if (inversion % 2 != 0)
        std::swap(vec[0], vec[1]);

    //0始终放在最后
    vec.push_back(Matrix::value_type(Board_API::null_value));

    PosVector index_vec;
    index_vec.resize(vec.size());
    int index = 0;
    for (int row=0; row<board->row_size(); ++row) {
        for (int col=0; col<board->col_size(); ++col) {
            Pos p(row, col);
            auto v = vec[index];
            board->set(p, v);
            index_vec[v] = p;
            ++index;
        }
    }
    return index_vec;
}

bool Board_API::isDone(const Matrix &m)
{
    Matrix::value_type n = start_value;
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            auto val = m.get(p);
            if (val!=0 && val!=n)
                return false;
            ++n;
        }
    }
    return true;
}

Pos Board_API::get_null_pos(const Matrix &m)
{
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            if (m.get(p) == null_value)
                return p;
        }
    }
    assert(false);
    return Pos(-1, -1);
}

Direction Board_API::direction_to(Pos from, Pos to)
{
    int drow = to.row() - from.row();
    int dcol = to.col() - from.col();
    if (drow == 0) {
        if (dcol == 1)
            return Direction::Null_Right;
        else if (dcol == -1)
            return Direction::Null_Left;
    }
    else if (dcol == 0) {
        if (drow == 1)
            return Direction::Null_Down;
        else if (drow == -1)
            return Direction::Null_Up;
    }
    return Direction::NotValid;
}

bool Board_API::hint_null_move(Matrix *m, Pos null_hint, Direction d)
{
    assert(get_null_pos(*m) == null_hint);
    Pos to = null_hint;
    move(&to, d);
    if (!m->isInMatrix(to))
        return false;

    auto val = m->get(to);
    m->set(null_hint, val);
    m->set(to, null_value);
    return true;
}

Direction Board_API::get_direction(const Matrix &m1, const Matrix &m2)
{
    Pos p1 = get_null_pos(m1);

    {
        const Direction &d = Direction::Null_Up;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }

    {
        const Direction &d = Direction::Null_Down;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }

    {
        const Direction &d = Direction::Null_Right;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }

    {
        const Direction &d = Direction::Null_Left;
        Pos p = p1;
        move(&p, d);
        if (m2.isInMatrix(p) && m2.get(p) == null_value)
            return d;
    }
    return Direction::NotValid;
}

bool Board_API::check_next(const Matrix &m1, const Matrix &m2)
{
    return get_direction(m1, m2) != Direction::NotValid;
}
