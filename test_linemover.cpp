#include "linemover.h"
#include "boardgen.h"

void test_linemover()
{
    Board board;
    board.gen(5, 5);
    BoardGen::gen(&board);
    BoolMatrix fixed;
    fixed.resize(5, 5);
    fixed.set_all_unfixed();

    board.print();
    PosList line;
    line.push_back({0, 0});
    line.push_back({0, 1});
    line.push_back({0, 2});
    line.push_back({0, 3});
    line.push_back({0, 4});

    MoverParam param(board);

    LineMover::finish_line(line, &param);
    param.board.print();
    param.fixed_matrix.print();
}
