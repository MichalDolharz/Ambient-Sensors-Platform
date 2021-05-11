#include "block.h"

Block::Block()//QGraphicsItem *parent)    : QGraphicsRectItem(parent)
{}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
}

