#include "view.h"

View::View(QGraphicsScene* scene)
{
    sceneHandle = scene;

    int Xcenters[] = {240, 320, 400, 480, 560};
    int Ycenters[] = {100, 145, 190, 235};
    int numberOfZone[] = {4, 3, 2, 1};
    int blockColors[] = {0, 1, 2, 3};

    //Zone (*frontView)[5] = new Zone[5][5];
    //frontView = new Zone*[5];
    //frontView = new Zone[5][5];
    for(int x = 0; x < 5; x++)
    {
        //frontView[x] = new Zone[5];
        for(int y = 0; y < 4; y++)
        {
            frontView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, frontViewMode);
            if(y > 0)
            {
               frontView[x][y].hide();
            }
        }
    }

    //Zone (*backView)[5] = new Zone[5][5];
    //backView = new Zone[5][5];
    //backView = new Zone*[5];
    for(int x = 0; x < 5; x++)
    {
        //backView[x] = new Zone[5];
        for(int y = 0; y < 4; y++)
        {
            backView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, backViewMode);
            //if(y > 0)
            //{
               backView[x][y].hide();
            //}
        }
    }
    //Zone (*bothSidesFrontView)[5] = new Zone[5][5];
    //bothSidesFrontView = new Zone*[5];
    //bothSidesFrontView = new Zone[5][5];
    for(int x = 0; x < 5; x++)
    {
        //bothSidesFrontView[x] = new Zone[5];
        for(int y = 0; y < 4; y++)
        {
            bothSidesFrontView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, bothSidesFrontViewMode);
            //if(y > 0)
            //{
               bothSidesFrontView[x][y].hide();
            //}
        }
    }
    //Zone (*bothSidesBackView)[5] = new Zone[5][5];
    //bothSidesBackView = new Zone*[5];
    //bothSidesBackView = new Zone[5][5];
    for(int x = 0; x < 5; x++)
    {
        //bothSidesBackView[x] = new Zone[5];
        for(int y = 0; y < 4; y++)
        {
            bothSidesBackView[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y, x, bothSidesBackViewMode);
            //if(y > 0)
            //{
               bothSidesBackView[x][y].hide();
            //}
        }
    }

    int width, height;

        //this->viewMode = frontViewMode;
        frontViewImg = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/qt_img/front.png"));
        width = frontViewImg->boundingRect().width();
        height = frontViewImg->boundingRect().height();
        frontViewImg->setPos(400-width/2, 600-height);
        scene->addItem(frontViewImg);

        //frontViewImg->hide();

        backViewImg = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/qt_img/back.png"));
        width = backViewImg->boundingRect().width();
        height = backViewImg->boundingRect().height();
        backViewImg->setPos(400-width/2, 0);
        scene->addItem(backViewImg);

        backViewImg->hide();

        bothSidesViewImg = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/qt_img/bothsides.png"));
        width = bothSidesViewImg->boundingRect().width();
        height = bothSidesViewImg->boundingRect().height();
        bothSidesViewImg->setPos(400-width/2, 300-height/2);
        scene->addItem(bothSidesViewImg);

        bothSidesViewImg->hide();

        this->thisViewMode = frontViewMode;
        //statuses = new int[10];
        for(int i = 0; i < 10; i++)
        {
            statuses[i] = 0;
        }
}

void View::setStatus(int sensor, int status)
{
        statuses[sensor] = status;
}

void View::tmpsetStatus(int sensor, int status)
{
    Zone (*zone)[5][5];

    zone = &frontView;
    (*zone)[sensor][statuses[sensor]].hide();
    this->statuses[sensor] = status;
    (*zone)[sensor][statuses[sensor]].show();
    /*
    // Hides previous zone
        frontView[sensor][statuses[sensor]].hide();

        // Saves new zone
        this->statuses[sensor] = status;

        // Shows new zone
        frontView[sensor][statuses[sensor]].show();*/
}

void View::updateScreen(int sensor, int status)
{
    bool back = 0;
    bool front = 0;

    int prevStatus = statuses[sensor];
    int tmp = statuses[sensor]; // kopia
    statuses[sensor] = status;


    int viewFrom = this->thisViewMode;
    int viewTo;

    if(checkStatuses(frontViewMode))
        front = 1;
    if(checkStatuses(backViewMode))
        back = 1;

    statuses[sensor] = tmp; // przywracamy

    if(front == 1 && back == 1)
        viewTo = bothSidesViewMode;
        //updateView(bothSidesBackViewMode, sensor, prev_status);
        //viewMode = bothSidesViewMode; //pokaz calosc, schowaj przod i tyl
    else if(front == 1 && back == 0)
        viewTo = frontViewMode;
        //updateView(frontViewMode, sensor, prev_status);
        //viewMode = frontViewMode; //pokaz przod, schowaj calosc i przod
    else if(front == 0 && back == 1)
        viewTo = backViewMode;
        //updateView(backViewMode, sensor, prev_status);
        //viewMode = backViewMode; //pokaz tyl, schowaj calosc i przod
    else if (front == 0 && back == 0)
        viewTo = noneViewMode;
        //updateView(noneViewMode, sensor, prev_status);
        //viewMode = noneViewMode;

    //updateView(viewMode);
    //if((viewTo == frontViewMode || viewTo == backViewMode || viewTo == noneViewMode) && !(viewTo == frontViewMode && viewTo == backViewMode))
    //{
        qDebug() <<"\nviewFrom: " << viewFrom <<", viewTo: " << viewTo;

        updateView(viewFrom, viewTo, sensor, status, prevStatus);
        this->thisViewMode = viewTo;
    //}
}
void View::updateView(int viewFrom, int viewTo, int sensor, int status, int prev_status)
{
    Zone (*zone)[5][5];
    int sensorNum;
    int sensorScale = 0;
    bool sideToUpdate; // 1 - front, 0 - back
    QGraphicsPixmapItem* img;


    switch(viewFrom) // sprawdzamy ktory widok byl aktywny
    {
    case frontViewMode:
        zone = &frontView;
        img = frontViewImg;
        sensorNum = sensor;
        qDebug() << "z: frontView";
        break;
    case backViewMode:
        zone = &backView;
        img = backViewImg;
        sensorNum = sensor - 5; // cofamy zakres 5-9 do 0-4
        sensorScale = 5;
        qDebug() << "z: backView";
        break;
    case bothSidesViewMode:
        if(sensor >= 0 && sensor < 5) // 0-4
        {
            qDebug() << "z: bothSidesFrontView";
            zone = &bothSidesFrontView;
            sensorNum = sensor;
            sideToUpdate = 1;
        }
        else if(sensor >= 5 && sensor < 10) // 5-9
        {
            qDebug() << "z: bothSidesBackView";
            zone = &bothSidesBackView;
            sensorNum = sensor - 5;
            sensorScale = 5;
            sideToUpdate = 0;
        }

        img = bothSidesViewImg;
        break;
    }

    if(viewFrom == viewTo && viewFrom != noneViewMode)// && viewFrom != bothSidesViewMode)// && viewFrom != bothSidesViewMode)
    {
        qDebug() << "Bez zmiany widoku";
        for(int i=0; i<10; i++)
        {
            qDebug() << "11strefa" << i << "status" <<statuses[i];
        }
        //qDebug() <<"sensor: " << sensor << ", sensorNum: " << sensorNum << ", statuses[sensorNum]: " << statuses[sensorNum];
        (*zone)[sensorNum][statuses[sensor]].hide();
        qDebug() << "1chowam strefę" << sensorNum << "o statusie" << statuses[sensor]<<  "widoku" << viewFrom;

        statuses[sensor] = status;

        (*zone)[sensorNum][statuses[sensor]].show();
        qDebug() << "1pokazuje strefę" << sensorNum << "o statusie" << statuses[sensor]<<  "widoku" << viewFrom;
        for(int i=0; i<10; i++)
        {
            qDebug() << "12strefa" << i << "status" <<statuses[i];
        }
    }
    else
    {
        qDebug() << "Zmiana widoku";
        // chowamy stary widok
        if(viewFrom == frontViewMode || viewFrom == backViewMode){
            for(int i=0; i<10; i++)
            {
                qDebug() << "21strefa" << i << "status" <<statuses[i];
            }
            for(int i = 0; i < 5; i++)
            {
                (*zone)[i][statuses[i+sensorScale]].hide();
                qDebug() << "2chowam strefę" << i << "o statusie" << statuses[i+sensorScale]<<  "widoku" << viewFrom<< "| sensorScale" << sensorScale;
            }
            for(int i=0; i<10; i++)
            {
                qDebug() << "22strefa" << i << "status" <<statuses[i];
            }
        }
        else if(viewFrom == bothSidesViewMode)
        {
            qDebug() << "Zmiana widoku ale bothSide";
            zone = &bothSidesFrontView;
            for(int i = 0; i < 5; i++)
            {
                (*zone)[i][statuses[i]].hide();
                qDebug() << "3chowam strefę" << i << "o statusie" << statuses[i]<<  "widoku" << bothSidesFrontViewMode;
            }
            zone = &bothSidesBackView;
            for(int i = 0; i < 5; i++)
            {
                (*zone)[i][statuses[i+5]].hide();
                qDebug() << "3chowam strefę" << i << "o statusie" << statuses[i+5]<<  "widoku" << bothSidesBackViewMode;
            }
        }

        if(viewFrom != noneViewMode)
            img->hide();

        statuses[sensor] = status;


        // zmiana wskaźnika
        switch(viewTo)
        {
        case frontViewMode:
            zone = &frontView;
            img = frontViewImg;
            sensorScale = 0;
            qDebug() << "do: frontView";
            frontViewImg->show();
            break;
        case backViewMode:
            zone = &backView;
            img = backViewImg;
            sensorScale = 5;
            backViewImg->show();
            qDebug() << "do: backView";
            break;
        case bothSidesViewMode:
            bothSidesViewImg->show();
            img = bothSidesViewImg;
            break;
        case noneViewMode:
            qDebug() << "\nzodyn\n";
            return;
            break;
        }


        if(viewTo != noneViewMode)
            img->show();


        if(viewTo == frontViewMode || viewTo == backViewMode)
        {
            for(int i=0; i<10; i++)
            {
                qDebug() << "23strefa" << i << "status" <<statuses[i];
            }
            for(int i = 0; i < 5; i++)
            {
                (*zone)[i][statuses[i+sensorScale]].show();
            qDebug() << "2pokazuje strefę" << i  << "(" << i+sensorScale <<")"<<"o statusie" << statuses[i+sensorScale]<<  "widoku" << viewTo<< "| sensorScale" << sensorScale;
            }
            for(int i=0; i<10; i++)
            {
                qDebug() << "24strefa" << i << "status" <<statuses[i];
            }
        }
        else if(viewTo == bothSidesViewMode)
        {
            zone = &bothSidesFrontView;
            for(int i = 0; i < 5; i++)
            {
                (*zone)[i][statuses[i]].show();
                qDebug() << "32pokazuje strefę" << i << "o statusie" << statuses[i]<<  "widoku" << bothSidesFrontViewMode;
            }
            zone = &bothSidesBackView;
            for(int i = 1; i < 5; i++)
            {
                (*zone)[i][statuses[i+5]].show();
                qDebug() << "3pokazuje strefę" << i << "o statusie" << statuses[i+5]<<  "widoku" << bothSidesBackViewMode;
            }
        }
        //schowaj stary widok

        //pokaz nowy widok
    }

    /*switch(thisViewMode)
    {
    case frontViewMode:

        if(hiddenView() == frontViewMode)
        {
            for(int i = 0; i < 5; i++)
            {
                frontView[i]
            }
        }
        else
        {
            schowaj strefę hiddenview()
        }
        //if(!frontView[1]->isHidden())
        //    frontView->hide();
        break;
    }

    thisViewMode = viewMode;
}*/

/*
void View::updateView(int viewMode)
{
    switch(thisViewMode)
    {
    case frontViewMode:

        if(hiddenView() == frontViewMode)
        {
            for(int i = 0; i < 5; i++)
            {
                frontView[i]
            }
        }
        else
        {
            schowaj strefę hiddenview()
        }
        //if(!frontView[1]->isHidden())
        //    frontView->hide();
        break;
    }

    thisViewMode = viewMode;*/
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

/*bool View::hiddenView()
{
    return viewHidden;
}*/

void View::hideImg(QGraphicsPixmapItem* viewImg)
{
    viewImg->moveBy(0, 2000);
}

void View::showImg(QGraphicsPixmapItem* viewImg)
{
    viewImg->moveBy(0, -2000);
}

