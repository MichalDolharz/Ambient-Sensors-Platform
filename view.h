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
     * \param[in] viewType Sets view mode.
     */
    View(QGraphicsScene* scene);

    /*!
     * \brief Set new status on given as a parameter sensor. Updates the scene.
     * \param[in] sensor Sensor that will be given new status.
     * \param[in] status new status to be given.
     */
    void setStatus(int sensor, int status);
    void tmpsetStatus(int sensor, int status);

    void updateScreen(int sensor, int status);

    //void move(int sensor, int status, int x, int y);

private:
    QGraphicsScene* sceneHandle; //!< Scene handle. Points to the original scene to add items.
    //Zone** frontView;                 //!< 2D array of View objects.
    //Zone** backView;                 //!< 2D array of View objects.
    //Zone** bothSidesFrontView;                 //!< 2D array of View objects.
    //Zone** bothSidesBackView;                 //!< 2D array of View objects.
    //Zone (*frontView)[5];                 //!< 2D array of View objects.
    //Zone (*backView)[5];                 //!< 2D array of View objects.
    //Zone (*bothSidesFrontView)[5];                 //!< 2D array of View objects.
    //Zone (*bothSidesBackView)[5];                 //!< 2D array of View objects.
    Zone frontView[5][5];                 //!< 2D array of View objects.
    Zone backView[5][5];                //!< 2D array of View objects.
    Zone bothSidesFrontView[5][5];                 //!< 2D array of View objects.
    Zone bothSidesBackView[5][5];

    int thisViewMode;                //!< View mode.
    QGraphicsPixmapItem* frontViewImg;
    QGraphicsPixmapItem* backViewImg;
    QGraphicsPixmapItem* bothSidesViewImg;
    int statuses[10];               //!< Holds statuses in order.

    //void hideImg(QGraphicsPixmapItem* viewImg);
    //void showImg(QGraphicsPixmapItem* viewImg);
    void hideImg(QGraphicsPixmapItem* viewImg);
    void showImg(QGraphicsPixmapItem* viewImg);
    //bool hiddenView();
    bool checkStatuses(int view);
    void updateView(int viewFrom, int viewTo, int sensor, int status, int prev_status);
};

#endif // VIEW_H
