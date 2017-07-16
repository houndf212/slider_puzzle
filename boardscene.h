#ifndef BOARDSCENE_H
#define BOARDSCENE_H
#include <QtCore>
#include <QGraphicsScene>
#include <unordered_map>
#include "board.h"
#include "numberitem.h"

class BoardScene : public QObject
{
    Q_OBJECT
public:
    explicit BoardScene(QObject* parent=nullptr);
    QGraphicsScene* get_scene() const { return m_scene; }
    Q_SIGNAL void sig_done();
    void reset(int row, int col);
    bool move(Board::Direction d);

private:
    Q_SLOT void onNumberClicked();
    Q_SLOT void onNumberWheel(BoardRotator::ClockDirection clock);
private:
    void gen_board(int row, int col);
    void gen_graphics(int row, int col);

    void move_number(int val, Pos p);
private:
    QGraphicsScene* m_scene;
    std::unordered_map<int, NumberItem*> m_itemMap;
    Board m_board;
private:
    static constexpr int SCALE = 50;
};

#endif // BOARDSCENE_H
