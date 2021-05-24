#include "block.h"

Block::Block()
{}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPathItem::paint(painter, option, widget);
}

