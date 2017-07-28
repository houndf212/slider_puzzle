#include "debug_output.h"
#include <iostream>
#include <iomanip>

#include "matrix.h"
#include "boolmatrix.h"
#include "pos.h"
#include "board.h"

template<>
void print(const Matrix& m)
{
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            std::cout << std::setw(2) << static_cast<int>(m.get(Pos(row, col)))<<" ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<>
void print(const BoolMatrix& m)
{
    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            std::cout<< static_cast<int>(m.get(Pos(row, col)))<<" ";
        }
        std::cout << std::endl;
    }
}

template<>
void print(const Board &b)
{
    print(b.inner_matrix());
}

template<>
void  print(const Pos &p)
{
    std::cout<<"("<<p.row()<<", "<<p.col()<<")";
}

template<>
void  print(const PosList &lst)
{
    std::cout<<"[";
    for (const auto &p : lst) {
        print(p);
        std::cout<<",";
    }
    std::cout<<"]";
    std::cout<<std::endl;
}

template<>
void print(const Direction &d)
{
    switch (d) {
    case Direction::Null_Up:
        std::cout << "null_up";
        break;
    case Direction::Null_Down:
        std::cout << "null_down";
        break;
    case Direction::Null_Right:
        std::cout << "null_right";
        break;
    case Direction::Null_Left:
        std::cout << "null_left";
        break;
    case Direction::NotValid:
        std::cout << "not_valid";
        break;
    default:
        break;
    }
}

template<>
void print(const MoveList &mlst)
{
    std::cout<<"[";
    for (const auto &p : mlst) {
        print(p);
        std::cout<<",";
    }
    std::cout<<"]";
    std::cout<<std::endl;
}

template<>
void print(const std::list<int> &lst)
{
    std::cout<<"[";
    for (const auto &p : lst) {
        std::cout<<p;
        std::cout<<",";
    }
    std::cout<<"]";
    std::cout<<std::endl;
}

