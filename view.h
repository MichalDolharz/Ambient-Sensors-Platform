/**
* @file view.h
* @brief Header for zone composed of blocks and car graphic
*
* @author Michał Dołharz
*
*/
#ifndef VIEW_H
#define VIEW_H

#include "zone.h"
//#include <QGraphicsView>
#include <QPixmap>
//#include <QImage>
#include <QGraphicsPixmapItem>
//#include <QFileDialog>

/*!
 * \brief Holds modes of view.
 */
enum viewModes{
    frontView,
    backView,
    bothSidesView
};

/*!
 * \brief The View class.
 */
class View
{
public:
    /*!
     * \brief View constructor. Creates view based on vieType parameter and adds to the scene handle.
     * \param[out] scene Scene handle.
     * \param[in] viewType Sets view mode.
     */
    View(QGraphicsScene* scene, int viewType = frontView);

    /*!
     * \brief Set new status on given as a parameter sensor. Updates the scene.
     * \param[in] sensor Sensor that will be given new status.
     * \param[in] status new status to be given.
     */
    setStatus(int sensor, int status);

    //void move(int sensor, int status, int x, int y);

private:
    QGraphicsScene* sceneHandle; //!< Scene handle. Points to the original scene to add items.
    Zone** view;                 //!< 2D array of View objects.
    int viewMode;                //!< View mode.
    int *statuses;               //!< Holds statuses in order.
};

#endif // VIEW_H
