#include "board.h"
#include "boardgen.h"
#include "puzzle_mover.h"
#include "debug_output.h"

//测试用搜索方法来计算移动结果

bool check_matrix_board()
{
    Board b;
    b.gen(3, 3);
    BoardGen::gen(&b);
    auto path1 = PuzzleMover::solve(b);

    Board b2(b.inner_matrix());
    auto path2 = PuzzleMover::solve(b2);

    return path1 == path2;
}

void test_search_board()
{
    assert(check_matrix_board());
}
