#include "gamewindow.h"
#include "sizepickerdialog.h"

GameWindow::GameWindow()
{
    m_board = new BoardScene(this);
    m_view = new GraphicsView(m_board->get_scene());
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    m_btn = new QPushButton("Reset");
    m_btn->setFocusPolicy(Qt::NoFocus);
    connect(m_btn, &QPushButton::clicked, this, &GameWindow::onReset);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_btn);
    layout->addWidget(m_view);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(layout);

    m_board->reset(3, 3);
    m_view->setMinimumSize(300, 300);
}

void GameWindow::onReset()
{
    SizePickerDialog d(this);
    d.exec();
    QSize s = d.getSize();
    m_board->reset(s.height(), s.width());
    m_view->setFixedSize(s*100);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        m_board->move(Board::Up);
        break;
    case Qt::Key_Down:
        m_board->move(Board::Down);
        break;
    case Qt::Key_Left:
        m_board->move(Board::Left);
        break;
    case Qt::Key_Right:
        m_board->move(Board::Right);
        break;
    default:
        break;
    }
}
