#include "gamewindow.h"
#include "sizepickerdialog.h"
#include "puzzle_mover.h"

static bool
_to_mvList(
    MoveList &mv,
    const Board *_board,
    const std::vector<uint8_t> &numMV)
{
    Board board;
    board.clone(*_board);

    mv.clear();
    for (auto val : numMV)
    {
        auto pos = board.value_pos(val);
        auto dir = board.test_null_move_to(pos);
        if (Direction::NotValid == dir)
        {
            return false;
        }

        mv.check_loop_push_back(dir);
        bool b = board.null_move(dir);
        assert(b);
    }

    return board.isDone();
}

GameWindow::GameWindow()
{
    m_board = new BoardScene;
    m_view = new GraphicsView(m_board->get_scene());
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_btn_resize = new QPushButton("Resize");
    m_btn_resize->setFocusPolicy(Qt::NoFocus);
    connect(m_btn_resize, &QPushButton::clicked, this, &GameWindow::onResize);

    btn_gen = new QPushButton("Random");
    btn_gen->setFocusPolicy(Qt::NoFocus);
    connect(btn_gen, &QPushButton::clicked, this, &GameWindow::onGen);

    m_btn_auto_solve = new QPushButton("Auto solve");
    m_btn_auto_solve->setFocusPolicy(Qt::NoFocus);
    connect(m_btn_auto_solve, &QPushButton::clicked, this, &GameWindow::onAutoSolve);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameWindow::onTimeout);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_btn_resize);
    btnLayout->addWidget(btn_gen);
    btnLayout->addWidget(m_btn_auto_solve);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(btnLayout);
    layout->addWidget(m_view);

    setLayout(layout);

    m_board->resize_board(3, 3);
    m_view->setMinimumSize(300, 300);

    m_nineSolver.buildAllStatus();
    m_numSolver.buildAllStatus();
}

GameWindow::~GameWindow()
{
    delete m_board;
}

void GameWindow::onResize()
{
    SizePickerDialog d(this);
    d.setSize(QSize(m_board->inner_board()->col_size(),
                    m_board->inner_board()->row_size()));
    d.exec();
    QSize s = d.getSize();
    m_board->resize_board(s.height(), s.width());
    m_view->setMinimumSize(s*100);
    m_view->fitInView(m_board->get_scene()->sceneRect());
}

void GameWindow::onGen()
{
    m_board->gen();

    const Board *bb = m_board->inner_board();

    if (3 == bb->row_size() && 3 == bb->col_size())
    {
        uint8_t arr[9];

        int index = 0;
        for (char r=0; r<3; ++r)
        {
            for (char c=0; c<3; ++c)
            {
                auto v = bb->pos_value({r, c});
                arr[index++] = v;
            }
        }


        m_nineSolver.solve(arr);

        m_numSolver.solve(arr, 9);

        std::vector<uint8_t> mvList;
        m_meetSolver33.solve(mvList, arr, 9);
    }

    if (3 == bb->row_size() && 4 == bb->col_size())
    {
        uint8_t arr[12];

        int index = 0;
        for (char r=0; r<3; ++r)
        {
            for (char c=0; c<4; ++c)
            {
                auto v = bb->pos_value({r, c});
                arr[index++] = v;
            }
        }

        std::vector<uint8_t> mvList;
        m_meetSolver34.solve(mvList, arr, 12);

        bool b = _to_mvList(m_movelist, m_board->inner_board(), mvList);
        if (b)
        {
            printf("Meet Solver Done!\n");
        }
    }
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
        assert(m_board->inner_board()->isDone());
        leaveAutoSolve();
        return;
    }
    Direction d = m_movelist.front();
    m_movelist.pop_front();
    bool b = m_board->move(d);
    assert(b==true);
    Q_UNUSED(b);
}

void GameWindow::enterAutoSolve()
{
    if (m_board->inner_board()->isDone())
        return;

    m_btn_auto_solve->setText("Stop");
    m_btn_resize->setEnabled(false);
    btn_gen->setEnabled(false);
    m_view->setEnabled(false);

    auto row = m_board->inner_board()->row_size();
    auto col = m_board->inner_board()->col_size();
    if (row * col > 3*3)
    {
        m_movelist = PuzzleMover::solve(*m_board->inner_board());

        MoveList mv;
        if ((3 == row && 4 == col) || (4 == row && 3 == col))
        {
            mv = solve_43or34();
        }

        if (false == mv.empty())
        {
            printf("Solve By Meet In Middle Solver: old %zu new %zu\n", m_movelist.size(), mv.size());
            m_movelist = mv;
        }
    }
    else
    {
        m_movelist = PuzzleMover::search_solve(*m_board->inner_board());
    }

    printf("auto solve steps: %zu\n", m_movelist.size());
    assert(m_board->inner_board()->can_solve(m_movelist));
    m_timer->start(1*300);
}

void GameWindow::leaveAutoSolve()
{
    m_btn_auto_solve->setText("Auto solve");
    m_btn_resize->setEnabled(true);
    btn_gen->setEnabled(true);
    m_view->setEnabled(true);

    m_movelist.clear();
    m_timer->stop();
}

MoveList GameWindow::solve_43or34()
{
    MoveList ret;

    const Board *bb = m_board->inner_board();

    auto row = m_board->inner_board()->row_size();
    auto col = m_board->inner_board()->col_size();

    uint8_t arr[12];

    int index = 0;
    for (char r=0; r<row; ++r)
    {
        for (char c=0; c<col; ++c)
        {
            auto v = bb->pos_value({r, c});
            arr[index++] = v;
        }
    }

    bool bSolved = false;
    std::vector<uint8_t> mvList;
    if (3 == row && 4 == col)
    {
        bSolved = m_meetSolver34.solve(mvList, arr, 12);
    }
    else if (4 == row && 3 == col)
    {
        bSolved = m_meetSolver43.solve(mvList, arr, 12);
    }

    if (bSolved)
    {
        bool b = _to_mvList(ret, m_board->inner_board(), mvList);
        if (false == b)
        {
            ret.clear();
        }
    }

    return ret;
}

//void GameWindow::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key()) {
//    case Qt::Key_Up:
//        m_board->move(Direction::Null_Down);
//        break;
//    case Qt::Key_Down:
//        m_board->move(Direction::Null_Up);
//        break;
//    case Qt::Key_Left:
//        m_board->move(Direction::Null_Right);
//        break;
//    case Qt::Key_Right:
//        m_board->move(Direction::Null_Left);
//        break;
//    default:
//        break;
//    }
//}
