#ifndef NUMBERITEM_H
#define NUMBERITEM_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QFont>

class BoardScene;

class NumberItem : public QGraphicsRectItem
{
public:
    explicit NumberItem(int value, BoardScene *ctrl, QGraphicsItem *parent = 0);
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *e) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *e) override;
private:
    const int m_value;
    const QString m_strVal;
    BoardScene *m_ctrl;
    bool m_isHover;
    QPen m_defaultPen;
    QPen m_hoverPen;
    QPen m_canMovePen;
    QFont m_font;
    QBrush m_defaultBrush;

};

#endif // NUMBERITEM_H
