﻿#include "boardscene.h"

BoardScene::BoardScene(QObject *parent)
    :QObject(parent)
{
    m_scene = new QGraphicsScene(this);
    resize_board(3, 3);
}

void BoardScene::resize_board(int row, int col)
{
    if (m_board.row_size() !=row || m_board.col_size()!=col) {
        m_board.resize(row, col);
        gen_graphics(row, col);
    }
}

void BoardScene::gen()
{
    m_board.gen();
    for (int row=0; row<m_board.row_size(); ++row) {
        for (int col=0; col<m_board.col_size(); ++col) {
            Pos p(row, col);
            if (p == m_board.get_null_pos())
                continue;
            auto val = m_board.pos_value(p);
            move_number(val, p);
        }
    }
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
        Q_UNUSED(b);
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
            m_itemMap.emplace(val, item);
            item->setRect(0, 0, SCALE, SCALE);
            item->setValue(val);
            item->setCurrentPos(p);
//            move_number(val, p);
            item->setPos(c*SCALE, r*SCALE);
        }
    }
    gen();
}

void BoardScene::move_number(Matrix::value_type val, Pos p)
{
    NumberItem *item = m_itemMap.at(val);
    item->setCurrentPos(p);
    item->animate_move(QPointF(p.col()*SCALE, p.row()*SCALE), 300);
}
