#include "view.h"

View::View(QGraphicsScene* scene, int viewType)
{
    sceneHandle = scene;

    int Xcenters[] = {240, 320, 400, 480, 560};
    int Ycenters[] = {100, 145, 190, 235};
    int numberOfZone[] = {4, 3, 2, 1};
    int blockColors[] = {0, 1, 2, 3};

    view = new Zone*[5];
    for(int x = 0; x < 5; x++)
    {
        view[x] = new Zone[5];
        for(int y = 0; y < 4; y++)
        {
            view[x][y] = Zone(scene, Xcenters[x], Ycenters[y], y);
            if(y > 0)
            {
               view[x][y].hide();
            }
        }
    }

    QGraphicsPixmapItem *img;
    int width, height;
    switch(viewType)
    {
    case 0:
        this->viewMode = frontView;
        img = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/front.png"));
        width = img->boundingRect().width();
        height = img->boundingRect().height();
        img->setPos(400-width/2, 600-height);
        scene->addItem(img);

        statuses = new int[5];
        for(int i = 0; i < 5; i++)
        {
            statuses[i] = 0;
        }

        break;
    case 1:
        this->viewMode = backView;
        break;
    case 2:
        this->viewMode = bothSidesView;
        break;
    default:
        this->viewMode = frontView;
        break;
    }
}

View::setStatus(int sensor, int status)
{
    // Can't rememeber what was it for, looks unnecessary, but I'm not brave enough to delete, I like not spending hours for debugging
    //view[sensor][statuses[sensor]];

    // Hides previous zone
    view[sensor][statuses[sensor]].hide();

    // Saves new zone
    this->statuses[sensor] = status;

    // Shows new zone
    view[sensor][statuses[sensor]].show();
}
