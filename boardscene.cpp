#include "boardscene.h"
#include "numberitem.h"
#include "numberitemobject.h"

static constexpr int SCALE = 50;

BoardScene::BoardScene()
{
    m_scene = new QGraphicsScene;
    resize_board(3, 3);
}

BoardScene::~BoardScene()
{
    delete m_scene;

    _clean_objItemVec();
}

void BoardScene::_clean_objItemVec()
{
    for (auto p : m_val2ItemObjectVec)
    {
        delete p;
    }

    m_val2ItemObjectVec.clear();
}

void BoardScene::resize_board(int row, int col)
{
    if (m_board.row_size() != row || m_board.col_size() != col)
    {
        m_board.resize(row, col);
        _create_graphics(row, col);
    }
}

void BoardScene::gen()
{
    m_board.gen();

    for (int row=0; row<m_board.row_size(); ++row)
    {
        for (int col=0; col<m_board.col_size(); ++col)
        {
            Pos p(row, col);
            if (p == m_board.get_null_pos())
            {
                continue;
            }

            auto val = m_board.pos_value(p);
            move_number(val, p);
        }
    }
}

void BoardScene::_create_graphics(int row, int col)
{
    m_scene->setSceneRect(0, 0, SCALE*col, SCALE*row);

    //first clear
    for (QGraphicsItem *it : m_scene->items())
    {
        delete it;
    }

    //clear all
    _clean_objItemVec();
    assert(m_val2ItemObjectVec.empty());

    size_t allSize = row * col;
    m_val2ItemObjectVec.resize(allSize, nullptr);

    for (int r=0; r<row; ++r)
    {
        for (int c=0; c<col; ++c)
        {
            Pos p(r, c);
            if (p == m_board.get_null_pos())
            {
                continue;
            }

            int val = m_board.pos_value(p);
            QPointF pos(p.col() * SCALE, p.row() * SCALE);

            NumberItem* item = new NumberItem(val, this);
            m_scene->addItem(item);

            item->setRect(0, 0, SCALE, SCALE);
            item->setPos(pos);

            NumberItemObject *itemObj = new NumberItemObject(item);

            assert(val < m_val2ItemObjectVec.size());
            assert(nullptr == m_val2ItemObjectVec[val]);

            m_val2ItemObjectVec[val] = itemObj;
        }
    }
}

bool BoardScene::move(Direction d)
{
    Pos np = m_board.get_null_pos();
    if (!m_board.null_move(d))
    {
        return false;
    }

    auto val = m_board.pos_value(np);
    move_number(val, np);
    return true;
}

void BoardScene::onNumberClicked(int val)
{
    Pos p = m_board.value_pos(val);

    Direction d = m_board.test_null_move_to(p);
    if (d != Direction::NotValid) {
        Pos np = m_board.get_null_pos();
        bool b = m_board.null_move(d);
        assert(b != false);
        Q_UNUSED(b);
        move_number(val, np);
    }
}

void BoardScene::move_number(int val, Pos p)
{
    assert(val < m_val2ItemObjectVec.size());
    auto obj = m_val2ItemObjectVec[val];
    assert(nullptr != obj);
    QPointF pos(p.col() * SCALE, p.row() * SCALE);
    obj->moveToPos(pos);
}
