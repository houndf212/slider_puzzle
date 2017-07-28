#include "linemover.h"
#include "debug_output.h"

void test_linemover()
{
    Board board;
    board.resize(5, 5);
    board.gen();
    BoolMatrix fixed;
    fixed.resize(5, 5);
    fixed.set_all_unfixed();

    print(board);
    PosList line;
    line.emplace_back(0, 0);
    line.emplace_back(0, 1);
    line.emplace_back(0, 2);
    line.emplace_back(0, 3);
    line.emplace_back(0, 4);

    MoverParam param(board);

    LineMover::finish_line(line, &param);
    print(param.board);
    print(param.fixed_matrix);
}
