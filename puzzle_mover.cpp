﻿#include "puzzle_mover.h"
#include "linemover.h"
#include "boardrotator.h"

static bool check_line(PosList line, const Board &board)
{
    for (const Pos &p : line) {
        if (board.origin_value(p) != board.pos_value(p))
            return false;
    }
    return true;
}

MoveList PuzzleMover::solve(const Board &origin_board)
{
    Board board = origin_board;
    BoolMatrix fixed;
    fixed.resize(board.row_size(), board.col_size());
    fixed.set_all_unfixed();

    MoveList mlist;
    std::list<PosList> lines = get_move_lines(board);
    for (const PosList& line : lines) {
        MoveList lst = LineMover::finish_line(line, &board, &fixed);
        mlist.check_loop_append(lst);
        assert(check_line(line, board));
    }

    // solve last "two"
    // ? ?  ? ?
    // 0 8  8 0
    Pos p_null(board.row_size()-1, board.col_size()-1);
    if (board.get_null_pos()!=p_null) {
        // 必然是右移动一格
        bool b = board.null_move(Board::Null_Right);
        assert(b == true);
        mlist.check_loop_push_back(Board::Null_Right);
    }
    assert(board.isDone());
    assert(check_loop(mlist));
    return mlist;
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
                left_right.push_back(Pos(row, col));
            }
            lines.push_back(left_right);
        }
    }
    // 1 2 3
    // 4 5
    else if (board.row_size() < board.col_size()) {
        top_left.col() = board.col_size() - board.row_size();
        for (int col=0; col<top_left.col(); ++col) {
            PosList down_up;
            for (int row=board.row_size()-1; row>=0; --row) {
                down_up.push_back(Pos(row, col));
            }
            lines.push_back(down_up);
        }
    }
    //留下最后两个，所以减1
    Pos buttom_right(board.row_size()-1, board.col_size()-1);
    while (top_left!=buttom_right) {
        PosList left_right;
        for (int col=top_left.col(); col<board.col_size(); ++col) {
            left_right.push_back(Pos(top_left.row(), col));
        }
        assert(left_right.size()>=2);
        lines.push_back(left_right);

        //先左右 后上下，所以上下先达到2
        if (left_right.size() == 2)
            break;

        PosList down_up;
        for (int row=board.row_size()-1; row>top_left.row(); --row) {
            down_up.push_back(Pos(row, top_left.col()));
        }
        assert(down_up.size()>=2);
        lines.push_back(down_up);
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
        if (Board::is_loop(pre, *it))
            return false;
        pre = *it;
    }
    return true;
}
