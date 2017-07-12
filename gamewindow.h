#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtWidgets>
#include "graphicsview.h"
#include "boardscene.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();

private:
    Q_SLOT void onReset();

private:
    BoardScene* m_board;
    GraphicsView *m_view;
    QPushButton* m_btn;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEWINDOW_H
