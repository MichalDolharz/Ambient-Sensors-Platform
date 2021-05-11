#include "blocks.h"

Blocks::Blocks()
{
    this->Grupa = new QGraphicsItemGroup();
    colorFlag = 0;
}

Blocks::Blocks(QGraphicsScene* scene, int x, int y, int n, int color)
{

    this->Grupa = new QGraphicsItemGroup;
    QColor setColor;
    switch(color)
    {
    case 0:
        setColor = QColor(176, 203, 31);
        break;
    case 1:
        setColor = QColor(255, 237, 0);
        break;
    case 2:
        setColor = QColor(239, 127, 26);
        break;
    case 3:
        setColor = QColor(227, 30, 36);
        break;
    default:
        setColor = QColor(255, 1802, 193);
        break;
    }

    QGraphicsRectItem *tmp;
    for(int i = 0; i < n; i++)
    {
        tmp = new Block();
        tmp->setBrush(setColor);
        tmp->setPen(Qt::NoPen);
        tmp->setRect(0,(BLOCK_HEIGHT+BLOCK_HEIGHT_SPACE)*i, BLOCK_WIDTH, BLOCK_HEIGHT);
        Grupa->addToGroup(tmp);
    }

    Grupa->moveBy(x-BLOCK_WIDTH/2,y);//-((BLOCK_HEIGHT+BLOCK_HEIGHT_SPACE)*n)/2); // wysrodkowuje

    //QPainter painter;
    //Grupa->paint(painter);
    scene->addItem(Grupa);

    this->colorFlag = color;
}

bool Blocks::isHidden()
{
    if(Grupa->y() > 1000)
        return true;
    else
        return false;
}

void Blocks::show()
{
    Grupa->moveBy(0, -2000);
}
void Blocks::hide()
{
    Grupa->moveBy(0, 2000);
}
void Blocks::move(int x, int y)
{
    Grupa->moveBy(x, y);
}

