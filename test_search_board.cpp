#include "board.h"
#include "boardgen.h"
#include "puzzle_mover.h"
#include "debug_output.h"
#include <list>
#include <set>
#include "dijkstra.h"
#include "boardgraph.h"
#include <iostream>


void test_search_board()
{
//    assert(check_matrix_board());
    Board b;
    b.gen(3, 3);
    BoardGen::gen(&b);

    typedef BoardGraph BG;
    typedef Dijkstra<BG> G;

    BG g;
    auto p = G::AStart_path(g, b.inner_matrix(), b.inner_origin_matrix());
    print(b.inner_matrix());
    std::cout<<"###"<<std::endl;
    for (const auto & m : p.first) {
        print(m);
    }
    std::cout << p.second <<std::endl;
}


