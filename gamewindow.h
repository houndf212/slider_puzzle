#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtWidgets>
#include "graphicsview.h"
#include "boardscene.h"
#include "NineSolver.h"
#include "NumSolver.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();
    ~GameWindow();

private:
    void onResize();
    void onGen();
    void onAutoSolve();
    void onTimeout();

    void enterAutoSolve();
    void leaveAutoSolve();

    MoveList solve_43or34();
private:
    BoardScene* m_board;
    GraphicsView *m_view;
    QPushButton *m_btn_resize;
    QPushButton *btn_gen;
    QPushButton* m_btn_auto_solve;
    QTimer *m_timer;
    MoveList m_movelist;

    NineSolver m_nineSolver;
    num_puzzle::NumSolver<3, 3> m_numSolver;
    num_puzzle::MeetInMiddleSolver<3, 3> m_meetSolver33;
    num_puzzle::MeetInMiddleSolver<3, 4> m_meetSolver34;
    num_puzzle::MeetInMiddleSolver<4, 3> m_meetSolver43;

//    // QWidget interface
//protected:
//    void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEWINDOW_H
