#include "puzzle_mover.h"
#include "linemover.h"
#include "boardrotator.h"
#include "boardgraph.h"
#include "dijkstra.h"


static bool check_line(PosList line, const Board &board)
{
    for (const Pos &p : line) {
        if (board.origin_value(p) != board.pos_value(p))
            return false;
    }
    return true;
}

MoveList PuzzleMover::search_solve(const Board &b)
{
    Matrix start = b.inner_matrix();
    Matrix finish = b.inner_origin_matrix();

    typedef BoardGraph BG;
    typedef Dijkstra<BG> G;
    BG g;
    auto path = G::AStart_path(g, start, finish);
    return BG::toMoveList(path.first, start);
}

MoveList PuzzleMover::solve(const Board &origin_board)
{
    MoverParam param(origin_board);
    if (check_solve(&param))
        return param.move_list;

    else
        return MoveList();
}

bool PuzzleMover::check_solve(MoverParam *param)
{
    std::list<PosList> lines = get_move_lines(param->board);
    for (const PosList& line : lines) {
        bool b = LineMover::finish_line(line, param);
        if (b!=true)
            return false;
        assert(check_line(line, param->board));
    }

    // solve last "two"
    // ? ?  ? ?
    // 0 8  8 0
    Pos p_null(param->board.row_size()-1, param->board.col_size()-1);
    if (param->board.get_null_pos()!=p_null) {
        // 必然是右移动一格
        bool b = param->board.null_move(Direction::Null_Right);
        if (b == true) {
            param->move_list.check_loop_push_back(Direction::Null_Right);
        }
        else {
            return false;
        }
    }
    assert(param->board.isDone());
    assert(check_loop_new(param->move_list));
    return true;
}

std::list<PosList> PuzzleMover::get_move_lines(const Board &board)
{
    std::list<PosList> lines;
    //先弄成正方形

    Pos top_left(0, 0);
    // 1 2
    // 3 4
    // 5
    if (board.row_size() > board.col_size()) {
        top_left.row() = board.row_size() - board.col_size();
        for (int row=0; row<top_left.row(); ++row) {
            PosList left_right;
            for (int col=0; col<board.col_size(); ++col) {
                left_right.emplace_back(row, col);
            }
            lines.push_back(std::move(left_right));
        }
    }
    // 1 2 3
    // 4 5
    else if (board.row_size() < board.col_size()) {
        top_left.col() = board.col_size() - board.row_size();
        for (int col=0; col<top_left.col(); ++col) {
            PosList down_up;
            for (int row=board.row_size()-1; row>=0; --row) {
                down_up.emplace_back(row, col);
            }
            lines.push_back(std::move(down_up));
        }
    }
    //留下最后两个，所以减1
    Pos buttom_right(board.row_size()-1, board.col_size()-1);
    while (top_left!=buttom_right) {
        PosList left_right;
        for (int col=top_left.col(); col<board.col_size(); ++col) {
            left_right.emplace_back(top_left.row(), col);
        }

        auto size = left_right.size();
        assert(size>=2);
        lines.push_back(std::move(left_right));

        //先左右 后上下，所以上下先达到2
        if (size == 2)
            break;

        PosList down_up;
        for (int row=board.row_size()-1; row>top_left.row(); --row) {
            down_up.emplace_back(row, top_left.col());
        }
        assert(down_up.size()>=2);
        lines.push_back(std::move(down_up));
        top_left.row()++;
        top_left.col()++;
    }
    return lines;
}

bool PuzzleMover::check_loop(const MoveList &mlst)
{
    if (mlst.size() < 2)
        return true;

    auto it = begin(mlst);
    MoveList::value_type pre = *it;
    for (it++; it!=end(mlst); ++it) {
        if (is_reverse(pre, *it))
            return false;
        pre = *it;
    }
    return true;
}

bool PuzzleMover::check_loop_new(const MoveList &mlst)
{
    if (mlst.size() < 2)
        return true;

    return std::adjacent_find(begin(mlst), end(mlst), is_reverse) == end(mlst);
}

void test_check_loop()
{
    {
        MoveList mlst;
        mlst.assign({Direction::Null_Down, Direction::Null_Down, Direction::Null_Up});
        assert(!PuzzleMover::check_loop(mlst));
        assert(!PuzzleMover::check_loop_new(mlst));
    }

    {
        MoveList mlst;
        mlst.assign({Direction::Null_Down, Direction::Null_Down});
        assert(PuzzleMover::check_loop(mlst));
        assert(PuzzleMover::check_loop_new(mlst));
    }
}
