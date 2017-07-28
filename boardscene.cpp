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

bool BoardScene::move(Direction d)
{
    Pos np = m_board.get_null_pos();
    if (!m_board.null_move(d))
        return false;

    auto val = m_board.pos_value(np);
    move_number(val, np);
    return true;
}

void BoardScene::onNumberClicked()
{
    NumberItem *item = dynamic_cast<NumberItem *>(sender());
    Q_ASSERT(item!=nullptr);

    auto val = item->getValue();
    Pos p = m_board.value_pos(val);

    Q_ASSERT(item->getCurrentPos() == p);
    Q_ASSERT(m_board.pos_value(p) == val);

    Direction d = m_board.test_null_move_to(p);
    if (d!=Direction::NotValid) {
        Pos np = m_board.get_null_pos();
        bool b = m_board.null_move(d);
        assert(b!=false);
        move_number(val, np);
    }
}

//void BoardScene::onNumberWheel(BoardRotator::ClockDirection clock)
//{
//    NumberItem *item = dynamic_cast<NumberItem *>(sender());
//    Q_ASSERT(item!=nullptr);
//    qDebug() << clock;

//    int val = item->getValue();
//    Pos p = m_board.value_pos(val);

//    Q_ASSERT(item->getCurrentPos() == p);
//    Q_ASSERT(m_board.pos_value(p) == val);

////    auto mlist = BoardRotator::rotate(m_board, p, clock);
////    m_board.print();
////    for (auto d : mlist)
////        m_board.null_move(d);
////    m_board.print();
//}

void BoardScene::gen_board(int row, int col)
{
    if (m_board.row_size() !=row || m_board.col_size()!=col)
        m_board.resize(row, col);

    m_board.gen();
}

void BoardScene::gen_graphics(int row, int col)
{
    m_scene->setSceneRect(0, 0, SCALE*col, SCALE*row);
    //first clear
    for (QGraphicsItem *it : m_scene->items()) {
        delete it;
    }
    //clear hash
    m_itemMap.clear();

    for (int r=0; r<row; ++r) {
        for (int c=0; c<col; ++c) {
            Pos p(r, c);
            if (p == m_board.get_null_pos())
                continue;

            NumberItem* item = new NumberItem;
            connect(item, &NumberItem::clicked, this, &BoardScene::onNumberClicked);
//            connect(item, &NumberItem::wheel, this, &BoardScene::onNumberWheel);
            m_scene->addItem(item);
            auto val = m_board.pos_value(p);
            m_itemMap.insert(std::make_pair(val, item));
            item->setRect(0, 0, SCALE, SCALE);
            item->setValue(val);
            item->setCurrentPos(p);
            item->setPos(c*SCALE, r*SCALE);
        }
    }
}

void BoardScene::move_number(Matrix::value_type val, Pos p)
{
    typedef std::unordered_map<int, NumberItem*>::const_iterator Iter;
    Iter it = m_itemMap.find(val);
    Q_ASSERT(it != m_itemMap.cend());
    NumberItem *item = it->second;
    item->setCurrentPos(p);
    item->animate_move(QPointF(p.col()*SCALE, p.row()*SCALE), 300);
}
