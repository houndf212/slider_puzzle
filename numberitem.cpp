#include "numberitem.h"
#include <QPainter>
#include <QGraphicsSceneWheelEvent>
#include "boardscene.h"

NumberItem::NumberItem(int val, BoardScene *ctrl, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
    ,m_value(val)
    ,m_strVal(QString::number(val))
    ,m_ctrl(ctrl)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

void NumberItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRect(rect());
    painter->drawText(rect(), Qt::AlignCenter, m_strVal);
}

void NumberItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    m_ctrl->onNumberClicked(m_value);
}

//void NumberItem::wheelEvent(QGraphicsSceneWheelEvent *event)
//{
//    if (event->delta() < 0)
//        Q_EMIT wheel(BoardRotator::ClockWise);
//    else
//        Q_EMIT wheel(BoardRotator::AntiClock);
//}

