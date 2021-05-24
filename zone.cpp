#include "zone.h"
#include "view.h"

#define FIRST_BLOCK_START_EDGE 236
#define FIRST_BLOCK_END_EDGE 277
#define FIRST_BLOCK_START_EDGE_BOTH 136
#define FIRST_BLOCK_END_EDGE_BOTH 159
#define EDGE_TO_EDGE 45
#define EDGE_TO_EDGE_BOTH 27
#define SIDE_TO_SIDE 2

Zone::Zone()
{
    this->zone = new QGraphicsItemGroup();
}

Zone::Zone(QGraphicsScene* scene, int x, int y, int zoneNumber, int zonePosition, int viewMode)
{
    int numberOfBlocks = 4 - zoneNumber; // number of blocks to set into the zone
    zonePosition -=2; // {0,1,2,3,4} --> {-2, -1, 0, 1, 2} (will be used to rotate the zone (group of blocks))

    this->zone = new QGraphicsItemGroup; // sets zone object pointer

    QGraphicsPathItem *block; // shape of block will be set to this variable

    int blockStartEdge;
    int blockEndEdge;

    // Generating blocks
    for(int blockNumber = 0; blockNumber < numberOfBlocks; blockNumber++)
    {
        switch(viewMode)
        {
        case frontViewMode:
            blockStartEdge = (FIRST_BLOCK_START_EDGE+blockNumber*EDGE_TO_EDGE); // starting edge of the first block (reference point for next instructions)
            blockEndEdge = (FIRST_BLOCK_END_EDGE+blockNumber*EDGE_TO_EDGE); // ending edge of the first block (reference point for next instructions)
            break;
        case backViewMode:
            blockStartEdge = (FIRST_BLOCK_START_EDGE+blockNumber*EDGE_TO_EDGE); // starting edge of the first block (reference point for next instructions)
            blockEndEdge = (FIRST_BLOCK_END_EDGE+blockNumber*EDGE_TO_EDGE); // ending edge of the first block (reference point for next instructions)
            break;
        case bothSidesFrontViewMode:
            blockStartEdge = (FIRST_BLOCK_START_EDGE_BOTH+blockNumber*EDGE_TO_EDGE_BOTH); // starting edge of the first block (reference point for next instructions)
            blockEndEdge = (FIRST_BLOCK_END_EDGE_BOTH+blockNumber*EDGE_TO_EDGE_BOTH); // ending edge of the first block (reference point for next instructions)
            break;
        case bothSidesBackViewMode:
            blockStartEdge = (FIRST_BLOCK_START_EDGE_BOTH+blockNumber*EDGE_TO_EDGE_BOTH); // starting edge of the first block (reference point for next instructions)
            blockEndEdge = (FIRST_BLOCK_END_EDGE_BOTH+blockNumber*EDGE_TO_EDGE_BOTH); // ending edge of the first block (reference point for next instructions)
            break;
        }

        QPainterPath blockPath = getBlockPath(blockStartEdge, blockEndEdge);

        QBrush brush(getGradColor(blockStartEdge, zoneNumber, blockNumber, viewMode)); // sets the gradient which will be applied to the block

        block = new Block(); // creates new block object

        createBlock(block, blockPath, brush, viewMode); // sets the block with previously set configuration

        zone->addToGroup(block); // adds to group
    }
    this->moveToDestination(zonePosition, viewMode); // moves the group to the right position

    scene->addItem(zone); // adds zone to the scene
}

void Zone::moveToDestination(int zonePosition, int viewMode)
{
    int move;
    int start;

    switch(viewMode)
    {
    case frontViewMode:
        start = FIRST_BLOCK_START_EDGE;
        move = 281;
        zone->moveBy(0, start); // translates group so the starting edge of block is at the (0, 0) point
        zone->setRotation(zonePosition*(15+SIDE_TO_SIDE)); // rotates zone
        zone->moveBy(400, move); // translates group to final position
        break;
    case backViewMode:
        start = -FIRST_BLOCK_START_EDGE;
        move = 318;
        zone->moveBy(0, start); // translates group so the starting edge of block is at the (0, 0) point
        zone->setRotation(zonePosition*(15+SIDE_TO_SIDE)); // rotates zone
        zone->moveBy(400, move); // translates group to final position
        break;
    case bothSidesFrontViewMode:
        start = FIRST_BLOCK_START_EDGE_BOTH;
        move = 154;
        zone->moveBy(start, 0); // translates group so the starting edge of block is at the (0, 0) point
        zone->setRotation(zonePosition*(15+SIDE_TO_SIDE)); // rotates zone
        zone->moveBy(move, 300); // translates group to final position
        break;
    case bothSidesBackViewMode:
        start = -FIRST_BLOCK_START_EDGE_BOTH;
        move = 648;
        zone->moveBy(start, 0); // translates group so the starting edge of block is at the (0, 0) point
        zone->setRotation(zonePosition*(15+SIDE_TO_SIDE)); // rotates zone
        zone->moveBy(move, 300); // translates group to final position
        break;
    }


}

void Zone::createBlock(QGraphicsPathItem *block, QPainterPath blockPath, QBrush brush, int viewMode)
{
    int angle;
    switch(viewMode)
    {
    case frontViewMode:
        angle = -90;
        break;
    case backViewMode:
        angle = 90;
        break;
    case bothSidesFrontViewMode:
        angle = 180;
        break;
    case bothSidesBackViewMode:
        angle = 0;
        break;
    }

    block->setBrush(brush); // set brush (gradient)
    block->setPen(Qt::NoPen); // hides block's border
    block->setPath(blockPath); // sets shape to the block
    block->setRotation(angle); // rotates
}


QPainterPath Zone::getBlockPath(int blockStartEdge, int blockEndEdge)
{
    QRect rectStartEdge(-blockStartEdge, -blockStartEdge, 2*blockStartEdge, 2*blockStartEdge); // creates a square of width = 2*blockStartEdge
    QRect rectEndEdge(-blockEndEdge, -blockEndEdge, 2*blockEndEdge, 2*blockEndEdge); // creates a square of width = 2*blockEndEdge

    QPointF rectCenter(0, 0); // center point for creating the block path

    QPainterPath blockPath; // on this variable the block will be "built"

    // Building block's shape (not block yet):
    blockPath.moveTo(rectCenter); // move to center
    blockPath.arcTo(rectStartEdge, 352.5, 15); // crop the first circle. 15 degree. Centered to the Y axis
    blockPath.lineTo(rectCenter); // go back to the center
    blockPath.arcTo(rectEndEdge, 352.5, 15); // crop the second circle. 15 degree. Centered to the Y axis
    blockPath.closeSubpath(); // end

    return blockPath;
}

QRadialGradient Zone::getGradColor(int blockStartEdge, int zoneNumber, int blockNumber, int viewMode)
{
    int radRange;
    switch(viewMode)
    {
    case frontViewMode:
        radRange = 30;
        break;
    case backViewMode:
        radRange = 30;
        break;
    case bothSidesFrontViewMode:
        radRange = 21; // proportionally should be 17, but 21 looks better
    case bothSidesBackViewMode:
        radRange= 22;
    }

    QPointF gradCenter(blockStartEdge-(6+blockNumber*2), 0);
    QRadialGradient gradColor(gradCenter, radRange);

    switch(zoneNumber)
    {
    case 0:
        //setColor = Colors::DarkGreen;
        gradColor.setColorAt(0, Colors::Green);
        gradColor.setColorAt(1, Colors::DarkGreen);
        break;
    case 1:
        //setColor = Colors::DarkYellow;
        gradColor.setColorAt(0, Colors::Yellow);
        gradColor.setColorAt(1, Colors::DarkYellow);
        break;
    case 2:
        //setColor = Colors::DarkOrange;
        gradColor.setColorAt(0, Colors::Orange);
        gradColor.setColorAt(1, Colors::DarkOrange);
        break;
    case 3:
        //setColor = Colors::DarkRed;
        gradColor.setColorAt(0, Colors::Red);
        gradColor.setColorAt(1, Colors::DarkRed);
        break;
    default:
        gradColor.setColorAt(0, Qt::white);
        gradColor.setColorAt(1, Qt::black);
        break;
    }

    return gradColor;
}

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
