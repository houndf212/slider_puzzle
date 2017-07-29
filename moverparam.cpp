#include "moverparam.h"

MoverParam::MoverParam(const Board &b)
{
    board.clone(b);
    fixed_matrix.resize(board.row_size(), board.col_size());
    fixed_matrix.set_all_unfixed();
    move_list.clear();
}
