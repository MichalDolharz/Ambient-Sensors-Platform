#ifndef ZONE_H
#define ZONE_H

#include "blocks.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QKeyEvent>

enum viewModes{
    frontView,
    backView,
    bothSidesView
};

class Zone
{
public:
    Zone(QGraphicsScene* scene, int viewMode = frontView);
    setStatus(int sensor, int status);
    void keyPressEvent(QKeyEvent *event);
    void move(int sensor, int status, int x, int y);

private:
    QGraphicsScene* sceneTMP;
    int view;
    Blocks** zone;
    int *statuses;
};

#endif // ZONE_H
