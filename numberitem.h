#ifndef NUMBERITEM_H
#define NUMBERITEM_H

#include <QGraphicsItem>

class BoardScene;

class NumberItem : public QGraphicsRectItem
{
public:
    explicit NumberItem(int value, BoardScene *ctrl, QGraphicsItem *parent = 0);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
//    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
private:
    const int m_value;
    const QString m_strVal;
    BoardScene *m_ctrl;
};

#endif // NUMBERITEM_H
