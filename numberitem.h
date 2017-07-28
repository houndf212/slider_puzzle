#ifndef NUMBERITEM_H
#define NUMBERITEM_H
#include <QtCore>
#include <QGraphicsItem>
#include "pos.h"
#include "boardrotator.h"

class NumberItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Q_SIGNAL void clicked();
//    Q_SIGNAL void wheel(BoardRotator::ClockDirection clock);
    NumberItem(QGraphicsItem *parent = 0);

    void animate_move(QPointF p, int msec);

    Matrix::value_type getValue() const { return m_value; }
    void setValue(Matrix::value_type val) { m_value = val; }

    Pos getCurrentPos() const { return m_pos; }
    void setCurrentPos(Pos p) { m_pos = p; }
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
//    virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
private:
    void init_animation();
private:
    Matrix::value_type m_value;
    Pos m_pos;
    QPropertyAnimation* pos_animate;
};

#endif // NUMBERITEM_H
