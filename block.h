/**
* @file block.h
* @brief Header for simple block
*
* @author Michał Dołharz
*
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QGraphicsPathItem>
#include <QPainterPath>

#define WINDOW_WIDTH 800  //!< Main (and every) window width.
#define WINDOW_HEIGHT 600 //!< Main (and every) window height.

/*!
 * \brief The Block class. Defines single block.
 */
class Block : public QGraphicsPathItem
{
    public:
        /*!
         * \brief Default Block class constructor.
         */
        Block();//QGraphicsItem *parent = Q_NULLPTR);
    private:
        /*!
         * \brief Reimplemented from QGraphicsItem. Paints the contents of an item in local coordinates.
         * \param[in] painter QPainter object.
         * \param[in] option Optional QStyleOptionGraphicsItem object.
         * \param[in] widget Optional QWidget object.
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BLOCK_H
