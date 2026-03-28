#include "numberitemobject.h"

NumberItemObject::NumberItemObject(
    QGraphicsRectItem *numIter)
    :m_rect(numIter)
{
    m_animation = new QPropertyAnimation(this, "itemPos", nullptr);
}

NumberItemObject::~NumberItemObject()
{
    delete m_animation;
}

QPointF NumberItemObject::getItemPos() const
{
    return m_rect->pos();
}

void NumberItemObject::setItemPos(const QPointF &p)
{
    m_rect->setPos(p);
}

void NumberItemObject::moveToPos(const QPointF &p)
{
    QPointF start = m_rect->pos();

    m_animation->stop();
    m_animation->setDuration(300);
    m_animation->setStartValue(start);
    m_animation->setEndValue(p);
    m_animation->start();
}
