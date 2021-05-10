#ifndef SENSORVIEW_H
#define SENSORVIEW_H

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

namespace Ui {
class SensorView;
}

class SensorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SensorView(QWidget *parent = nullptr);
    ~SensorView();

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
private:
    Ui::SensorView *ui;


};

#endif // SENSORVIEW_H
