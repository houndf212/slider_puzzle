#ifndef BOARD_H
#define BOARD_H
#include "matrix.h"
class Board
{
public:
    enum Direction
    {
        NotValid,
        Null_Up = 0x1 | 0x1 <<1, // 0011
        Null_Down = Null_Up<<2, // 1100
        Null_Left = 0x1 | 0x1<<2, // 0101
        Null_Right = Null_Left<<1, //1010
    };
    static bool is_loop(Direction d1, Direction d2)
    {
        static_assert((Null_Up&Null_Down) == 0, "");
        static_assert((Null_Left&Null_Right) == 0, "");

        static_assert((Null_Up&Null_Right) != 0, "");
        static_assert((Null_Up&Null_Left) != 0, "");

        static_assert((Null_Down&Null_Right) != 0, "");
        static_assert((Null_Down&Null_Left) != 0, "");
        return (d1&d2) == 0;
    }
public:
    void gen(int row, int col);

    bool null_move(Direction d);

    Direction test_null_move_to(Pos p) const;

    Pos get_null_pos() const { return null_pos; }

    int pos_value(Pos p) const;
    Pos value_pos(int value) const;

    Pos origin_pos(int val) const;
    int origin_value(Pos p) const;

    void print() const;
    bool isDone() const;

    bool isInBoard(Pos p) const { return matrix.isInMatrix(p); }
    int row_size() const { return matrix.row_size(); }
    int col_size() const { return matrix.col_size(); }
private:
    void init_matrix();
    bool inner_null_move(int dr, int dc);
    void swap_null(Pos p);
private:
    Matrix matrix;
    //完成时的矩阵
    Matrix origin_matrix;
    //方向通过value 追踪pos位置
    std::vector<Pos> value_index;
    //完成时应该的位置
    std::vector<Pos> origin_value_index;
    Pos null_pos;
    static constexpr int null_value = 0;
};

#include "movelist.h"

//typedef std::list<Board::Direction> MoveList;
//inline void movelist_append(MoveList* to, const MoveList & from)
//{
//    to->insert(end(*to), begin(from), end(from));
//}
QDebug operator <<(QDebug debug, Board::Direction d);

#endif // BOARD_H
