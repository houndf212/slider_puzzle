#include "pathfiner.h"

/*由于 操作方式是 上： 从左到右
 *              左： 从上到下
 * 所以 移动的路径一定是 先左右后上 和 先上下后左
 *
 *
 *
*/
std::vector<Pos> PathFiner::find_path(Pos start, Pos end)
{
    std::vector<Pos> vec;
    if (start.equal(end))
        return vec;

    // 正上方
    if (start.col() == end.col() && start.row() > end.row()) {
        for (int row=start.row()-1; row>=end.row(); --row) {
            vec.push_back(Pos(row, start.col()));
        }
        return vec;
    }
    // 正左方
    if (start.row() == end.col() && start.col() > end.col()) {
        for (int col=start.col()-1; col>=end.col(); --col) {
            vec.push_back(Pos(start.row(), col));
        }
        return vec;
    }
    //右上方
    if (start.row() > end.row() && start.col() < end.col()) {
        //先右再上
        for (int col=start.col()+1; col<=end.col(); ++col) {
            vec.push_back(Pos(start.row(), col));
        }
        for (int row=start.row()-1; row>=end.row(); --row) {
            vec.push_back(Pos(row, end.col()));
        }
        return vec;
    }
    // 左下方
    if (start.row() < end.row() && start.col() > end.col()) {
        //先下后左
        for (int row=start.row()+1; row<=end.row(); ++row) {
            vec.push_back(Pos(row, start.col()));
        }
        for (int col=start.col()-1; col>=end.col(); --col) {
            vec.push_back(Pos(end.row(), col));
        }
        return vec;
    }
    //左上方， 无所谓方向
    if (start.row() > end.row() && start.col() > end.col()) {
        for (int row=start.row()-1; row<=end.row(); --row) {
            vec.push_back(Pos(row, start.col()));
        }
        for (int col=start.col()-1; col>=end.col(); --col) {
            vec.push_back(Pos(end.row(), col));
        }
        return vec;
    }
    Q_ASSERT(false);
    return vec;
}
