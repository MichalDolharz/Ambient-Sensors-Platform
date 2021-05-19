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
#include "block.h"
#include <QDebug>
#include <QRadialGradient>

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
     * \param[in] zoneNumber Number of zone, where <c>0</c> is the red one and 3 is the green one. Data correctness is not being checked. Amount of blocks and their color is based on this parameter.
     * \param[in] zonePosition Number of position of zone to be created, where <c>0</c> is the farthest left one and <4> is the farthest right one. Rotation and position of a zone is based on this parameter.
     * \param[in] viewMode View, which zone being created will be part of.
     */
    Zone(QGraphicsScene* scene, int x, int y, int zoneNumber, int zonePosition, int viewMode);

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
     * \brief Returns a gradient color for a block defined by given parameters.
     * \param[in] blockStartEdge Starting edge of block.
     * \param[in] zoneNumber Number of zone, where <c>0</c> is the red one and 3 is the green one. Color is chosen based on this parameter. Data correctness is not being checked.
     * \param[in] blockNumber Number of block in zone, where <c>0</c> is the lowest one and 3/2/1/0 is the highest one in zone 3/2/1/0. Data correctness is not being checked.
     * \param[in] viewMode View, which zone being created will be part of.
     * \return Returns QRadialGradient object with colors and a set position.
     */
    QRadialGradient getGradColor(int blockStartEdge, int zoneNumber, int blockNumber, int viewMode);

    /*!
     * \brief Returns QPath object that will be a shape of a block defined by given parameters.
     * \param[in] blockStartEdge Starting edge of block.
     * \param[in] blockEndEdge Ending of block.
     * \return Returns QPath object with shape of a block.
     */
    QPainterPath getBlockPath(int blockStartEdge, int blockEndEdge);

    /*!
     * \brief Sets a given shape and a gradient color to a block.
     * \param[out] block Block to be given shape and color.
     * \param[in] blockPath Shape of a block.
     * \param[in] brush Gradient color of a block.
     * \param[in] viewMode View, which zone being created will be part of.
     */
    void createBlock(QGraphicsPathItem *block, QPainterPath blockPath, QBrush brush, int viewMode);

    /*!
     * \brief Moves zone (simple group/columns of blocks) to a corresponding position based on zone position number.
     * \param[out] zone Zone to be moved.
     * \param[in] zonePosition Position to which a zone will be moved.
     * \param[in] viewMode View, which zone being created will be part of.
     */
    void moveToDestination(QGraphicsItemGroup *zone, int zonePosition, int viewMode);

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
