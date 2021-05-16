#include "zone.h"

#define FIRST_BLOCK_START_EDGE 236
#define FIRST_BLOCK_END_EDGE 277

Zone::Zone()
{
    this->zone = new QGraphicsItemGroup();
}

Zone::Zone(QGraphicsScene* scene, int x, int y, int zoneNumber, int viewZoneNumber)
{
    int numberOfBlocks;
    QColor setColor;
    viewZoneNumber -=2; // {0,1,2,3,4} --> {-2, -1, 0, 1, 2} (will be used to rotate group)

    this->zone = new QGraphicsItemGroup;

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

    QGraphicsPathItem *tmp;
    for(int i = 0; i < numberOfBlocks; i++)
    {
        int blockStartEdge = (FIRST_BLOCK_START_EDGE+i*45);
        int blockEndEdge = (FIRST_BLOCK_END_EDGE+i*45);
        QRect Rect1(-blockStartEdge, -blockStartEdge, 2*blockStartEdge, 2*blockStartEdge); // creates square of width = 2*blockStartEdge
        QRect Rect2(-blockEndEdge, -blockEndEdge, 2*blockEndEdge, 2*blockEndEdge); // creates square of width = 2*blockEndEdge
        QPointF Rcenter(0, 0); // center point

        QPainterPath myPath; // on this variable the block will be "built"

        // Building block's shape (not block yet):
        myPath.moveTo(Rcenter); // move to center
        myPath.arcTo(Rect1, 352.5, 15); // crop the first circle. 15 degree. Centered to the Y axis
        myPath.lineTo(Rcenter); // go back to the center
        myPath.arcTo(Rect2, 352.5, 15); // crop the second circle. 15 degree. Centered to the Y axis
        myPath.closeSubpath(); // end

        //QPainterPath sim = myPath.simplified(); // not sure if version with simplified is any changed

        tmp = new Block(); // creates block
        tmp->setBrush(setColor); // sets color
        tmp->setPen(Qt::NoPen); // hides block's border
        tmp->setPath(myPath); // sets shape to the block
        //tmp->setPath(sim); // version with simplified option used
        tmp->setRotation(-90); // rotates

        zone->addToGroup(tmp); // adds to group
    }
    zone->moveBy(0, FIRST_BLOCK_START_EDGE); // translates group so the starting edge of block is at the (0, 0) point
    zone->setRotation(viewZoneNumber*17); // rotates zone
    zone->moveBy(400, 281); // translates group to final position

    scene->addItem(zone);

}

/*Zone::Zone(QGraphicsScene* scene, int x, int y, int zoneNumber)
{
    int numberOfBlocks;
    QColor setColor;

    this->zone = new QGraphicsItemGroup;

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
        zone->addToGroup(tmp);
    }

    zone->moveBy(x-BLOCK_WIDTH/2, y);

    scene->addItem(zone);

}*/

bool Zone::isHidden()
{
    if(zone->y() > WINDOW_HEIGHT)
        return true;
    else
        return false;
}

void Zone::show()
{
    zone->moveBy(0, -2000);
}
void Zone::hide()
{
    zone->moveBy(0, 2000);
}
void Zone::move(int x, int y)
{
    zone->moveBy(x, y);
}

QColor Zone::Colors::DarkGreen(176, 203, 31);
QColor Zone::Colors::Green(Qt::white);

QColor Zone::Colors::DarkYellow(255, 237, 0);
QColor Zone::Colors::Yellow(Qt::white);

QColor Zone::Colors::DarkOrange(239, 127, 26);
QColor Zone::Colors::Orange(Qt::white);

QColor Zone::Colors::DarkRed(227, 30, 36);
QColor Zone::Colors::Red(Qt::white);

