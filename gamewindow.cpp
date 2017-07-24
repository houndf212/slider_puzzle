#include "gamewindow.h"
#include "sizepickerdialog.h"

GameWindow::GameWindow()
{
    m_board = new BoardScene(this);
    m_view = new GraphicsView(m_board->get_scene());
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_btn_reset = new QPushButton("Reset");
    m_btn_reset->setFocusPolicy(Qt::NoFocus);
    connect(m_btn_reset, &QPushButton::clicked, this, &GameWindow::onReset);

    m_btn_auto_solve = new QPushButton("Auto solve");
    m_btn_auto_solve->setFocusPolicy(Qt::NoFocus);
    connect(m_btn_auto_solve, &QPushButton::clicked, this, &GameWindow::onAutoSolve);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameWindow::onTimeout);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_btn_reset);
    btnLayout->addWidget(m_btn_auto_solve);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(btnLayout);
    layout->addWidget(m_view);

    setLayout(layout);

    m_board->reset(3, 3);
    m_view->setMinimumSize(300, 300);
}

void GameWindow::onReset()
{
    SizePickerDialog d(this);
    d.setSize(QSize(m_board->inner_board().col_size(),
                    m_board->inner_board().row_size()));
    d.exec();
    QSize s = d.getSize();
    m_board->reset(s.height(), s.width());
//    m_view->resize(s*100);
    m_view->setMinimumSize(s*100);
    //    resize(sizeHint());
}

void GameWindow::onAutoSolve()
{
    if (m_timer->isActive())
        leaveAutoSolve();
    else
        enterAutoSolve();
}

void GameWindow::onTimeout()
{
    if (m_movelist.empty()) {
        m_timer->stop();
        assert(m_board->inner_board().isDone());
        leaveAutoSolve();
        return;
    }
    Board::Direction d = m_movelist.front();
    m_movelist.pop_front();
    bool b = m_board->move(d);
    assert(b==true);
}

void GameWindow::enterAutoSolve()
{
    if (m_board->inner_board().isDone())
        return;

    m_btn_auto_solve->setText("Stop");
    m_btn_reset->setEnabled(false);
    m_view->setEnabled(false);

    m_movelist = PuzzleMover::solve(m_board->inner_board());
    qDebug() << "old sover size: " << m_movelist.size();
    m_movelist = PuzzleMover::search_solve(m_board->inner_board());
    qDebug() << "new sover size: " << m_movelist.size();
    m_timer->start(1*300);
}

void GameWindow::leaveAutoSolve()
{
    m_btn_auto_solve->setText("Auto solve");
    m_btn_reset->setEnabled(true);
    m_view->setEnabled(true);

    m_movelist.clear();
    m_timer->stop();
}

//void GameWindow::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_Up:
//        m_board->move(Board::Null_Down);
//        break;
//    case Qt::Key_Down:
//        m_board->move(Board::Null_Up);
//        break;
//    case Qt::Key_Left:
//        m_board->move(Board::Null_Right);
//        break;
//    case Qt::Key_Right:
//        m_board->move(Board::Null_Left);
//        break;
//    default:
//        break;
//    }
//}
