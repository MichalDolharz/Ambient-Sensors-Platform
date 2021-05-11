#ifndef BLOCK_H
#define BLOCK_H

#include <QRectF>
#include <QPainter>
//#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Block : public QGraphicsRectItem
{
    public:
        Block(QGraphicsItem *parent = Q_NULLPTR);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BLOCK_H
