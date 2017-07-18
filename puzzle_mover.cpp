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
    if (board.get_null_pos()!=p_null) {
        // 必然是右移动一格
        bool b = board.null_move(Board::Null_Right);
        assert(b == true);
        mlist.push_back(Board::Null_Right);
    }
    assert(board.isDone());
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
        assert(!left_right.empty());
        lines.push_back(left_right);

        if (left_right.size() == 2)
            break;

        PosList down_up;
        for (int row=board.row_size()-1; row>top_left.row(); --row) {
            down_up.push_back(Pos(row, top_left.col()));
        }
        assert(!down_up.empty());
        lines.push_back(down_up);
        top_left.row()++;
        top_left.col()++;
    }
//    for (const PosList& line : lines) {
//        qDebug() << QList<Pos>::fromStdList(line);
//    }
    return lines;
}
