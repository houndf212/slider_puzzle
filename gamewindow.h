#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtWidgets>
#include "graphicsview.h"
#include "boardscene.h"
#include "puzzle_mover.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();

private:
    void onResize();
    void onGen();
    void onAutoSolve();
    void onTimeout();

    void enterAutoSolve();
    void leaveAutoSolve();
private:
    BoardScene* m_board;
    GraphicsView *m_view;
    QPushButton *m_btn_resize;
    QPushButton *btn_gen;
    QPushButton* m_btn_auto_solve;
    QTimer *m_timer;
    MoveList m_movelist;

//    // QWidget interface
//protected:
//    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEWINDOW_H
