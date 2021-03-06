﻿#include "numberitem.h"
#include <QPainter>
#include <QGraphicsSceneWheelEvent>

NumberItem::NumberItem(QGraphicsItem *parent)
    :QGraphicsRectItem(parent),
      m_value(0)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    init_animation();
}

void NumberItem::animate_move(QPointF p, int msec)
{
    pos_animate->stop();
    pos_animate->setDuration(msec);
    pos_animate->setStartValue(this->pos());
    pos_animate->setEndValue(p);
    pos_animate->start();
}



void NumberItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(rect());
    painter->drawText(rect(), Qt::AlignCenter, QString::number(m_value));
}

void NumberItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    Q_EMIT clicked();
}

//void NumberItem::wheelEvent(QGraphicsSceneWheelEvent *event)
//{
//    if (event->delta() < 0)
//        Q_EMIT wheel(BoardRotator::ClockWise);
//    else
//        Q_EMIT wheel(BoardRotator::AntiClock);
//}

void NumberItem::init_animation()
{
    pos_animate = new QPropertyAnimation(this, "pos", this);
    pos_animate->setEasingCurve(QEasingCurve::InQuad);
}
