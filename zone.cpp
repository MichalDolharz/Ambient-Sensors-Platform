#include "zone.h"
#include <QFileDialog>

Zone::Zone(QGraphicsScene* scene, int viewMode)
{
    sceneTMP = scene;

    int Xcenters[] = {240, 320, 400, 480, 560};
    int Ycenters[] = {100, 145, 190, 235};
    int numberOfBlocks[] = {4, 3, 2, 1};
    int blockColors[] = {0, 1, 2, 3};

    zone = new Blocks*[5];
    for(int x = 0; x < 5; x++)
    {
        zone[x] = new Blocks[5];
        for(int y = 0; y < 4; y++)
        {
            zone[x][y] = Blocks(scene, Xcenters[x], Ycenters[y], numberOfBlocks[y], blockColors[y]);
            if(y > 0)
            {
               zone[x][y].hide();
            }
        }
    }

    QGraphicsPixmapItem *img;
    int width, height;
    switch(viewMode)
    {
    case 0:
        this->view = frontView;
        img = new QGraphicsPixmapItem(QPixmap("D:/Qt_workspace/WDS_testy/front.png"));
        width = img->boundingRect().width();
        height = img->boundingRect().height();
        img->setPos(400-width/2, 600-height);//moveBy(400-330/2,600-289);
        scene->addItem(img);

        statuses = new int[5];
        for(int i = 0; i < 5; i++)
        {
            statuses[i] = 0;
        }

        break;
    case 1:
        this->view = backView;
        break;
    case 2:
        this->view = bothSidesView;
        break;
    default:
        this->view = frontView;
        break;
    }
}

Zone::setStatus(int sensor, int status)
{
    zone[sensor][statuses[sensor]];

    zone[sensor][statuses[sensor]].hide();

    this->statuses[sensor] = status;

    zone[sensor][statuses[sensor]].show();
}

void Zone::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
    {
    case Qt::Key_1:
        this->setStatus(0, 0);
        break;
    case Qt::Key_2:
        this->setStatus(0, 1);
        break;
    case Qt::Key_3:
        this->setStatus(0, 2);
        break;
    case Qt::Key_4:
        this->setStatus(0, 3);
        break;
    case Qt::Key_Q:
        this->setStatus(1, 0);
        break;
    case Qt::Key_W:
        this->setStatus(1, 1);
        break;
    case Qt::Key_E:
        this->setStatus(1, 2);
        break;
    case Qt::Key_R:
        this->setStatus(1, 3);
        break;
    case Qt::Key_A:
        this->setStatus(2, 0);
        break;
    case Qt::Key_S:
        this->setStatus(2, 1);
        break;
    case Qt::Key_D:
        this->setStatus(2, 2);
        break;
    case Qt::Key_F:
        this->setStatus(2, 3);
        break;
    case Qt::Key_Z:
        this->setStatus(3, 0);
        break;
    case Qt::Key_X:
        this->setStatus(3, 1);
        break;
    case Qt::Key_C:
        this->setStatus(3, 2);
        break;
    case Qt::Key_V:
        this->setStatus(3, 3);
        break;
    case Qt::Key_U:
        this->setStatus(4, 0);
        break;
    case Qt::Key_I:
        this->setStatus(4, 1);
        break;
    case Qt::Key_O:
        this->setStatus(4, 2);
        break;
    case Qt::Key_P:
        this->setStatus(4, 3);
        break;
    default:
        break;
    }

    sceneTMP->update();
}

void Zone::move(int sensor, int status, int x, int y)
{
    zone[sensor][status].move(x, y);
}
