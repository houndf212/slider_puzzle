#include "boardscene.h"
#include "boardgen.h"

BoardScene::BoardScene(QObject *parent)
    :QObject(parent)
{
    m_scene = new QGraphicsScene(this);
    reset(3, 3);
}

void BoardScene::reset(int row, int col)
{
    gen_board(row, col);
    gen_graphics(row, col);
}

bool BoardScene::move(Board::Direction d)
{
    Pos np = m_board.get_null_pos();
    if (!m_board.move(d))
        return false;

    int val = m_board.pos_value(np);
    move_number(val, np);
    return true;
}

void BoardScene::onNumberClicked()
{
    NumberItem *item = dynamic_cast<NumberItem *>(sender());
    Q_ASSERT(item!=nullptr);

    int val = item->getValue();
    Pos p = m_board.value_pos(val); ;

    Q_ASSERT(item->getCurrentPos().equal(p));
    Q_ASSERT(m_board.pos_value(p) == val);

    Pos np = m_board.get_null_pos();
    if (m_board.move_pos(p)) {
        move_number(val, np);
    }
}

void BoardScene::gen_board(int row, int col)
{
    m_board.gen(row, col);
    BoardGen::gen(&m_board);
}

void BoardScene::gen_graphics(int row, int col)
{
    m_scene->setSceneRect(0, 0, SCALE*col, SCALE*row);
    //first clear
    QList<QGraphicsItem *> items = m_scene->items();
    for (QGraphicsItem *it : items) {
        delete it;
    }
    //clear hash
    m_itemMap.clear();

    for (int r=0; r<row; ++r) {
        for (int c=0; c<col; ++c) {
            Pos p(r, c);
            if (p.equal(m_board.get_null_pos()))
                continue;

            NumberItem* item = new NumberItem;
            connect(item, &NumberItem::clicked, this, &BoardScene::onNumberClicked);
            m_scene->addItem(item);
            int val = m_board.pos_value(p);
            m_itemMap.insert(std::make_pair(val, item));
            item->setRect(0, 0, SCALE, SCALE);
            item->setValue(val);
            item->setCurrentPos(p);
            item->setPos(c*SCALE, r*SCALE);
        }
    }
}

void BoardScene::move_number(int val, Pos p)
{
    typedef std::unordered_map<int, NumberItem*>::const_iterator Iter;
    Iter it = m_itemMap.find(val);
    Q_ASSERT(it != m_itemMap.cend());
    NumberItem *item = it->second;
    item->setCurrentPos(p);
    item->animate_move(QPointF(p.col()*SCALE, p.row()*SCALE), 300);
}
