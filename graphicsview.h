#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // GRAPHICSVIEW_H
