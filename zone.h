#ifndef ZONE_H
#define ZONE_H

/**
* @file zone.h
* @brief Header for column/pole of blocks
*
* @author Michał Dołharz
*
*/

#include <QGraphicsScene>
//#include <QGraphicsRectItem>
//#include <QPainter>
#include "block.h"
#include <QDebug>

#define BLOCK_WIDTH 70          //!< Simple block width.
#define BLOCK_WIDTH_SPACE 10    //!< Horizontal space between blocks.
#define BLOCK_HEIGHT 40         //!< Simple block height.
#define BLOCK_HEIGHT_SPACE 5    //!< Vertical space between blocks.

/*!
 * \brief The Zone class. Defines zone (column/pole of blocks).
 */
class Zone
{
public:
    /*!
     * \brief Default Zone constructor.
     */
    Zone();

    /*!
     * \brief Zone constructor. Creates desired zone at desired placed and adds it to the scene.
     * \param[out] scene Scene handle. Created zone is added to this scene.
     * \param[in] x x coordinate, at which the zone will be created.
     * \param[in] y y coordinate, at which the zone will be created.
     * \param[in] zoneNumber Number of zone to be created. Amount of blocks and their color is based on this parameter.
     */
    Zone(QGraphicsScene* scene, int x, int y, int zoneNumber, int viewZoneNumber);

    /*!
     * \brief Shows zone.
     */
    void show();

    /*!
     * \brief Hides zone.
     */
    void hide();

    /*!
     * \brief Checks if zone is hidden.
     * \return <c>True</c> if zone is hidden, <c>False</c> otherwise.
     */
    bool isHidden();

    /*!
     * \brief Moves zone by the given values.
     * \param[in] x Horizontal move
     * \param[in] y Vertical move
     */
    void move(int x, int y);

private:
    QGraphicsItemGroup *zone; //!< Pointer to the group of blocks.

    /*!
     * \brief Defines the outer bounds of the item as a rectangle.
     * \return QRectF object defining rectangle region.
     */
    QRectF boundingRect() const;

    /*!
     * \brief Reimplemented from QGraphicsItem. Paints the contents of an item in local coordinates.
     * \param[in] painter QPainter object.
     * \param[in] option Optional QStyleOptionGraphicsItem object.
     * \param[in] widget Optional QWidget object.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /*!
     * \brief Holds defined colors.
     */
    struct Colors{
        static QColor DarkGreen;  //!< Defined own dark green color
        static QColor Green;      //!< Defined own  green color

        static QColor DarkYellow; //!< Defined own dark yellow color
        static QColor Yellow;     //!< Defined own  green color

        static QColor DarkOrange; //!< Defined own dark orange color
        static QColor Orange;     //!< Defined own  green color

        static QColor DarkRed;    //!< Defined own dark red color
        static QColor Red;        //!< Defined own  green color
    };

};

#endif // ZONE_H
