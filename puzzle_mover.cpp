#include "puzzle_mover.h"
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
    assert(lines.back().size() == 1);
    lines.pop_back();
    for (const PosList& line : lines) {
        MoveList lst = LineMover::finish_line(line, &board, &fixed);
        movelist_append(&mlist, lst);
//        board.print();
//        fixed.print();
        assert(check_line(line, board));
    }

    // ? ?  ? ?
    // 0 8  8 0
    // solve last "two"
    Pos p_null(board.row_size()-1, board.col_size()-1);
    if (!board.get_null_pos().equal(p_null)) {
        // 必然是右移动一格
        bool b = board.null_move(Board::Null_Right);
        assert(b == true);
        mlist.push_back(Board::Null_Right);
    }
    board.print();
    return mlist;
}

std::list<PosList> PuzzleMover::get_move_lines(const Board &board)
{
    std::list<PosList> lines;
//     留下最后一个正方形 所以减2
    for (int i=0; i<board.row_size()-1; ++i) {
        PosList left_right;
        for (int col=i; col<board.col_size(); ++col) {
            left_right.push_back(Pos(i, col));
        }
        assert(!left_right.empty());
        lines.push_back(left_right);

        PosList down_up;
        for (int row=board.row_size()-1; row>i; --row) {
            down_up.push_back(Pos(row, i));
        }
        assert(!down_up.empty());
        lines.push_back(down_up);
    }
    return lines;
}
