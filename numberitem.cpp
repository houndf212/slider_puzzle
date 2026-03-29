#include "numberitem.h"
#include <QPainter>
#include <QGraphicsSceneWheelEvent>
#include "boardscene.h"

NumberItem::NumberItem(int val, BoardScene *ctrl, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
    ,m_value(val)
    ,m_strVal(QString::number(val))
    ,m_ctrl(ctrl)
    ,m_isHover(false)
{
    constexpr int g_width = 2;
    m_defaultPen = QPen(Qt::blue, g_width);
    m_hoverPen = QPen(Qt::red, g_width);
    m_canMovePen = QPen(Qt::green, g_width);

    m_defaultBrush = QBrush(Qt::gray);

    m_font.setPointSize(24);
    m_font.setBold(true);

    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
}

void NumberItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen(m_defaultPen);
    painter->setBrush(m_defaultBrush);
    painter->setFont(m_font);

    painter->drawRect(rect());

    if (m_isHover)
    {
        bool bCan = m_ctrl->canMoveNum(m_value);
        if (bCan)
        {
            painter->setPen(m_canMovePen);
        }
        else
        {
            painter->setPen(m_hoverPen);
        }
    }


    painter->drawText(rect(), Qt::AlignCenter, m_strVal);
}

void NumberItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    m_ctrl->onNumberClicked(m_value);
    QGraphicsRectItem::mousePressEvent(e);
}

void NumberItem::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    m_isHover = true;
    QGraphicsRectItem::hoverEnterEvent(e);
    //qDebug() << "hover in: " << m_value;
}

void NumberItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    m_isHover = false;
    QGraphicsRectItem::hoverLeaveEvent(e);
    //qDebug() << "hover out: " << m_value;
}

//void NumberItem::wheelEvent(QGraphicsSceneWheelEvent *event)
//{
//    if (event->delta() < 0)
//        Q_EMIT wheel(BoardRotator::ClockWise);
//    else
//        Q_EMIT wheel(BoardRotator::AntiClock);
//}

