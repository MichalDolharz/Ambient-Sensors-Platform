#include "view.h"

View::View(QGraphicsScene* scene)
{
    sceneHandle = scene;

    int Xcenters[] = {240, 320, 400, 480, 560};
    int Ycenters[] = {100, 145, 190, 235};

    // create front view
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            frontView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, frontViewMode);
            if(y > 0)
            {
               frontView[x][y].hide();
            }
        }
    }

    // create back view
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            backView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, backViewMode);
            backView[x][y].hide();
        }
    }

    // create left side of both sides view
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            bothSidesFrontView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, bothSidesFrontViewMode);
            bothSidesFrontView[x][y].hide();
        }
    }

    // create right side of both sides view
    for(int x = 0; x < 5; x++)
    {
        for(int y = 0; y < 4; y++)
        {
            bothSidesBackView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, bothSidesBackViewMode);
            bothSidesBackView[x][y].hide();
        }
    }

    // Load car images
    int width, height;

        frontViewImg = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/qt_img/front.png"));
        width = frontViewImg->boundingRect().width();
        height = frontViewImg->boundingRect().height();
        frontViewImg->setPos(400-width/2, 600-height);
        scene->addItem(frontViewImg);

        backViewImg = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/qt_img/back.png"));
        width = backViewImg->boundingRect().width();
        //height = backViewImg->boundingRect().height();
        backViewImg->setPos(400-width/2, 0);
        scene->addItem(backViewImg);

        backViewImg->hide();

        bothSidesViewImg = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/qt_img/bothsides.png"));
        width = bothSidesViewImg->boundingRect().width();
        height = bothSidesViewImg->boundingRect().height();
        bothSidesViewImg->setPos(400-width/2, 300-height/2);
        scene->addItem(bothSidesViewImg);

        bothSidesViewImg->hide();

        // save front view as default starting view
        this->thisViewMode = frontViewMode;

        // set 0 to all the statuses
        for(int i = 0; i < 10; i++)
        {
            statuses[i] = 0;
        }
}

void View::updateScreen(int sensor, int status)
{
    bool back = 0;
    bool front = 0;

    int tmp = statuses[sensor]; // backup variable
    statuses[sensor] = status; // for calculations


    int viewFrom = this->thisViewMode;
    int viewTo;

    // set flags
    if(checkStatuses(frontViewMode))
        front = 1;
    if(checkStatuses(backViewMode))
        back = 1;

    statuses[sensor] = tmp; // restore

    // some logic
    if(front == 1 && back == 1)
        viewTo = bothSidesViewMode;
    else if(front == 1 && back == 0)
        viewTo = frontViewMode;
    else if(front == 0 && back == 1)
        viewTo = backViewMode;
    else if (front == 0 && back == 0)
        viewTo = noneViewMode;


    updateView(viewFrom, viewTo, sensor, status);

    this->thisViewMode = viewTo; // save new view
}
void View::updateView(int viewFrom, int viewTo, int sensor, int status)
{
    Zone (*zone)[5][5];
    int sensorScale = 0; // scalling 5-9 sensors to 0-4.
    bool sideToUpdate; // 1 - front, 0 - back. Necessary to bothSidesViewMode.
    QGraphicsPixmapItem* img; // pointer to images (car images).

    // check which view is now and take some pointers and scalling variables
    switch(viewFrom)
    {
    case frontViewMode:
        zone = &frontView;
        img = frontViewImg;
        break;
    case backViewMode:
        zone = &backView;
        img = backViewImg;
        sensorScale = 5;
        break;
    case bothSidesViewMode:
        if(sensor >= 0 && sensor < 5) // 0-4
        {
            zone = &bothSidesFrontView;
        }
        else if(sensor >= 5 && sensor < 10) // 5-9
        {
            zone = &bothSidesBackView;
            sensorScale = 5;
        }

        img = bothSidesViewImg;
        break;
    }

    // No view change. Update the front view, the back view or both sides view.
    if(viewFrom == viewTo && viewFrom != noneViewMode)
    {
        (*zone)[sensor - sensorScale][statuses[sensor]].hide();

        statuses[sensor] = status;

        (*zone)[sensor - sensorScale][statuses[sensor]].show();

    }
    // View needs to be changed.
    else
    {
        // Hide previous view. Only the front view and the back view.
        if(viewFrom == frontViewMode || viewFrom == backViewMode){

            for(int i = 0; i < 5; i++)
                (*zone)[i][statuses[i+sensorScale]].hide();

        }
        // Hide previous view. Only the both sides view
        else if(viewFrom == bothSidesViewMode)
        {
            zone = &bothSidesFrontView;
            for(int i = 0; i < 5; i++)
                (*zone)[i][statuses[i]].hide();

            zone = &bothSidesBackView;
            for(int i = 0; i < 5; i++)
                (*zone)[i][statuses[i+5]].hide();
        }

        // Hide car image. There is no image on the noneViewMode, so can't be hidden.
        if(viewFrom != noneViewMode)
            img->hide();

        // Set new status.
        statuses[sensor] = status;

        // Take some pointers and scalling variables for next view to be set.
        switch(viewTo)
        {
        case frontViewMode:
            zone = &frontView;
            img = frontViewImg;
            sensorScale = 0;
            frontViewImg->show();
            break;
        case backViewMode:
            zone = &backView;
            img = backViewImg;
            sensorScale = 5;
            backViewImg->show();
            break;
        case bothSidesViewMode:
            bothSidesViewImg->show();
            img = bothSidesViewImg;
            break;
        case noneViewMode:
            return;
            break;
        }

        // Show car image. In the noneViewMode there is no image to be shown.
        if(viewTo != noneViewMode)
            img->show();

        // Show new view. Only the front view and the back view.
        if(viewTo == frontViewMode || viewTo == backViewMode)
        {
            for(int i = 0; i < 5; i++)
                (*zone)[i][statuses[i+sensorScale]].show(); // zones are set as the statuses are set

        }
        // Show ne view. Only the both sides view.
        else if(viewTo == bothSidesViewMode)
        {
            zone = &bothSidesFrontView;
            for(int i = 0; i < 5; i++)
                (*zone)[i][statuses[i]].show(); // zones are set as the statuses are set

            zone = &bothSidesBackView;
            for(int i = 1; i < 5; i++)
                (*zone)[i][statuses[i+5]].show(); // zones are set as the statuses are set
        }

    }
}

bool View::checkStatuses(int viewMode)
{
    int startingSensor;

    if(viewMode == frontViewMode)
        startingSensor = 0;
    else if(viewMode == backViewMode)
        startingSensor = 5;
    else
        return 1;

    for(int i = startingSensor; i < startingSensor+5; i++)
    {
        if(statuses[i] != 0)
            return 1;
    }
    return 0;
}
