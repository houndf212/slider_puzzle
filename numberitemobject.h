#ifndef NUMBERITEMOBJECT_H
#define NUMBERITEMOBJECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPropertyAnimation>

class NumberItemObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF itemPos READ getItemPos WRITE setItemPos)
public:
    NumberItemObject(QGraphicsRectItem *numIterm);

    ~NumberItemObject();

    QPointF getItemPos() const;

    void setItemPos(const QPointF &p);

    void moveToPos(const QPointF &p);
private:
    QGraphicsRectItem  *m_rect;
    QPropertyAnimation *m_animation;
};

#endif // NUMBERITEMOBJECT_H
