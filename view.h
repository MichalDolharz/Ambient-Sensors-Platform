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
#include <QPixmap>
#include <QGraphicsPixmapItem>

/*!
 * \brief Holds modes of view.
 */
enum viewModes{
    frontViewMode,
    backViewMode,
    bothSidesViewMode,
    bothSidesFrontViewMode,
    bothSidesBackViewMode,
    noneViewMode
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
     */
    View(QGraphicsScene* scene);

    /*!
     * \brief Set new status on given as a parameter sensor. Updates the scene.
     * \param[in] sensor Sensor that will be given new status.
     * \param[in] status new status to be given.
     */

    void updateScreen(int sensor, int status);

    //void move(int sensor, int status, int x, int y);

private:
    QGraphicsScene* sceneHandle; //!< Scene handle. Points to the original scene to add items.

    Zone frontView[5][5];                 //!< 2D array of View objects.
    Zone backView[5][5];                //!< 2D array of View objects.
    Zone bothSidesFrontView[5][5];                 //!< 2D array of View objects.
    Zone bothSidesBackView[5][5];//!< 2D array of View objects.

    int thisViewMode;                //!< Current view mode.
    QGraphicsPixmapItem* frontViewImg; //!< Image of car's front
    QGraphicsPixmapItem* backViewImg; //!< Image of car's back
    QGraphicsPixmapItem* bothSidesViewImg; //!< Full car image
    int statuses[10];               //!< Holds statuses in order.

    /*!
     * \brief Checks if any of sensors from view (parameter) have status other than 0 (if any sensor is detecting an obstacle).
     * \param[in] view View to be checked.
     * \return Return <c>True</c> if any sensor in this view has status other than 0. Returns <c>False</c> if every sensor has status 0.
     */
    bool checkStatuses(int view);

    /*!
     * \brief Updates the view or changes it. to the new one.
     * \param[in] viewFrom Current view.
     * \param[in] viewTo If the same as viewFrom, the view will be updated. If other, the view will be changed.
     * \param[in] sensor Sensor that detected change.
     * \param[in] status New status to be set to the sensor.
     */
    void updateView(int viewFrom, int viewTo, int sensor, int status);
};

#endif // VIEW_H
