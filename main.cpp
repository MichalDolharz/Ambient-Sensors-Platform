/**
* @file main.cpp
* @brief Główny plik programu
*
* @author Michał Dołharz
*
*/

#include "mainwindow.h"
//#include "sensorsfront.h"
#include "blocks.h"
#include <QtGui>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include "block.h"
#include <QPixmap>
#include <QDebug>
#include "zone.h"


/*!
 * \brief qMain Funkcja main() programu.
 * \param argc Liczba parametrów wejściowych.
 * \param argv Parametry wejściowe.
 * \return Działanie programu.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QGraphicsView sensorView;
    QGraphicsScene* scene = new QGraphicsScene(0, 0, 800, 600, &sensorView);

    // Background color
    QRadialGradient backgroundGradient(400, 300, 370);
    backgroundGradient.setColorAt(0, QColor(109, 118, 183));
    backgroundGradient.setColorAt(1, QColor(6, 35, 105));
    scene->setBackgroundBrush(backgroundGradient);
    sensorView.setScene(scene);

    //Zone *front = new Zone(scene, frontView);
    Zone front(scene, frontView);

    MainWindow w(front);
    //front->move(2, 0, 0, -50);
    //front->setStatus(2, 2);

    w.setWindowTitle("Configuration");
    sensorView.setWindowTitle("Sensors");
    //s.setWindowTitle("Front sensors");

    w.show();
    sensorView.show();
    return app.exec();
}
