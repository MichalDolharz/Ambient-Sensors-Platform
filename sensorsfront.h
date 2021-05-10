#ifndef SENSORSFRONT_H
#define SENSORSFRONT_H

#include <QMainWindow>
#include <QPainter>
#include <QRadialGradient>
#include <QPointF>
#include <QColor>
#include <QPainterPath>

#define X_START 50
#define Y_START 150
#define X_WIDTH 100
#define Y_HEIGHT 50
#define X_CENTER X_START+X_WIDTH/2
#define Y_CENTER Y_START+Y_HEIGHT/2

// in px (not mm)
#define GREEN_BLOCK_TOP 400
#define GREEN_BLOCK_BOTTOM 365
#define YELLOW_BLOCK_TOP 355
#define YELLOW_BLOCK_BOTTOM 320
#define ORANGE_BLOCK_TOP 310
#define ORANGE_BLOCK_BOTTOM 275
#define RED_BLOCK_TOP 265
#define RED_BLOCK_BOTTOM 230

#define SENSOR_0_ANGLE -131.5
#define SENSOR_1_ANGLE -114.5
#define SENSOR_2_ANGLE -97.5
#define SENSOR_3_ANGLE -80.5
#define SENSOR_4_ANGLE -63.5


namespace Ui {
class SensorsFront;
}

class SensorsFront : public QMainWindow
{
    Q_OBJECT

public:
    explicit SensorsFront(QWidget *parent = nullptr);
    ~SensorsFront();

    virtual void paintEvent(QPaintEvent *event);
    struct GradColors
    {
        static QColor DarkBlue;
        static QColor Blue;

        static QColor DarkGreen;
        static QColor Green;

        static QColor DarkYellow;
        static QColor Yellow;

        static QColor DarkOrange;
        static QColor Orange;

        static QColor DarkRed;
        static QColor Red;
    };

    static double Angles[];
    static int BlocksRanges[];


private:
    Ui::SensorsFront *ui;


};

#endif // SensorsFront_H
