#ifndef MOVEDIRECTION_H
#define MOVEDIRECTION_H
#include <assert.h>

enum class Direction
{
    NotValid,
    Null_Up = 0x1 | 0x1 <<1, // 0011
    Null_Down = Null_Up<<2, // 1100
    Null_Left = 0x1 | 0x1<<2, // 0101
    Null_Right = Null_Left<<1, //1010
};

template<Direction d>
constexpr int toInt()
{
    return static_cast<int>(d);
}

inline bool is_reverse(Direction d1, Direction d2)
{
    static_assert((toInt<Direction::Null_Up>()&toInt<Direction::Null_Down>()) == 0, "");
    static_assert((toInt<Direction::Null_Left>()&toInt<Direction::Null_Right>()) == 0, "");

    static_assert((toInt<Direction::Null_Up>()&toInt<Direction::Null_Right>()) != 0, "");
    static_assert((toInt<Direction::Null_Up>()&toInt<Direction::Null_Left>()) != 0, "");

    static_assert((toInt<Direction::Null_Down>()&toInt<Direction::Null_Right>()) != 0, "");
    static_assert((toInt<Direction::Null_Down>()&toInt<Direction::Null_Left>()) != 0, "");

    return (static_cast<int>(d1)&static_cast<int>(d2)) == 0;
}

inline Direction reverse(Direction d)
{
    assert(d!=Direction::NotValid);
    constexpr int full = toInt<Direction::Null_Up>() | toInt<Direction::Null_Down>();

    static_assert((full^toInt<Direction::Null_Up>()) == toInt<Direction::Null_Down>(), "");
    static_assert((full^toInt<Direction::Null_Down>()) == toInt<Direction::Null_Up>(), "");
    static_assert((full^toInt<Direction::Null_Right>()) == toInt<Direction::Null_Left>(), "");
    static_assert((full^toInt<Direction::Null_Left>()) == toInt<Direction::Null_Right>(), "");

    return Direction(static_cast<int>(d)^full);
}
#endif // MOVEDIRECTION_H
