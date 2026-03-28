#ifndef BOARDSCENE_H
#define BOARDSCENE_H
#include <QtCore>
#include <QGraphicsScene>
#include <unordered_map>
#include "board.h"

class NumberItemObject;

class BoardScene
{
public:
    BoardScene();

    ~BoardScene();

    QGraphicsScene *get_scene() const { return m_scene; }

    const Board *inner_board() const { return &m_board; }

    void resize_board(int row, int col);

    void gen();

    bool move(Direction d);

    void onNumberClicked(int val);
private:
    void _clean_objItemVec();

    void _create_graphics(int row, int col);

    void move_number(int val, Pos p);
private:
    QGraphicsScene *m_scene;
    std::vector<NumberItemObject*> m_val2ItemObjectVec;
    Board m_board;
};

#endif // BOARDSCENE_H
