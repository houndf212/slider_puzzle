#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(scene()->sceneRect());
    QGraphicsView::resizeEvent(event);
}
