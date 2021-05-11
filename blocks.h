#ifndef BLOCKS_H
#define BLOCKS_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QGraphicsItem>
#include "block.h"
#include <QDebug>

#define BLOCK_WIDTH 70
#define BLOCK_WIDTH_SPACE 10
#define BLOCK_HEIGHT 40
#define BLOCK_HEIGHT_SPACE 5

class Blocks// : public QGraphicsItem
{
public:
    //Blocks(QGraphicsItem* parent = nullptr);
    Blocks();
    Blocks(QGraphicsScene* scene, int x, int y, int n, int color);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void show();
    void hide();
    bool isHidden();
    void move(int x, int y);

private:
    QGraphicsItemGroup *Grupa;
    int colorFlag;
};

#endif // BLOCKS_H
