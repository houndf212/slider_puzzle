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
    Q_SLOT void onReset();
    Q_SLOT void onAutoSolve();
    Q_SLOT void onTimeout();

    void enterAutoSolve();
    void leaveAutoSolve();
private:
    BoardScene* m_board;
    GraphicsView *m_view;
    QPushButton *m_btn_reset;

    QPushButton* m_btn_auto_solve;
    QTimer *m_timer;
    MoveList m_movelist;

//    // QWidget interface
//protected:
//    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEWINDOW_H
