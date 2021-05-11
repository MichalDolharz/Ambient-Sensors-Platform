#include "zone.h"

Zone::Zone()
{
    this->Grupa = new QGraphicsItemGroup();
}

Zone::Zone(QGraphicsScene* scene, int x, int y, int zoneNumber)
{
    int numberOfBlocks;
    QColor setColor;

    this->Grupa = new QGraphicsItemGroup;

    switch(zoneNumber)
    {
    case 0:
        setColor = Colors::DarkGreen;
        numberOfBlocks = 4;
        break;
    case 1:
        setColor = Colors::DarkYellow;
        numberOfBlocks = 3;
        break;
    case 2:
        setColor = Colors::DarkOrange;
        numberOfBlocks = 2;
        break;
    case 3:
        setColor = Colors::DarkRed;
        numberOfBlocks = 1;
        break;
    default:
        setColor = Qt::white;
        break;
    }

    QGraphicsRectItem *tmp;
    for(int i = 0; i < numberOfBlocks; i++)
    {
        tmp = new Block();
        tmp->setBrush(setColor);
        tmp->setPen(Qt::NoPen);
        tmp->setRect(0,(BLOCK_HEIGHT+BLOCK_HEIGHT_SPACE)*i, BLOCK_WIDTH, BLOCK_HEIGHT);
        Grupa->addToGroup(tmp);
    }

    Grupa->moveBy(x-BLOCK_WIDTH/2, y);

    scene->addItem(Grupa);

}

bool Zone::isHidden()
{
    if(Grupa->y() > WINDOW_HEIGHT)
        return true;
    else
        return false;
}

void Zone::show()
{
    Grupa->moveBy(0, -2000);
}
void Zone::hide()
{
    Grupa->moveBy(0, 2000);
}
void Zone::move(int x, int y)
{
    Grupa->moveBy(x, y);
}

QColor Zone::Colors::DarkGreen(176, 203, 31);
QColor Zone::Colors::Green(Qt::white);

QColor Zone::Colors::DarkYellow(255, 237, 0);
QColor Zone::Colors::Yellow(Qt::white);

QColor Zone::Colors::DarkOrange(239, 127, 26);
QColor Zone::Colors::Orange(Qt::white);

QColor Zone::Colors::DarkRed(227, 30, 36);
QColor Zone::Colors::Red(Qt::white);

