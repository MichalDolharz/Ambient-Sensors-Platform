/**
* @file main.cpp
* @brief Główny plik programu
*
* @author Michał Dołharz
*
*/

#include "mainwindow.h"
//#include "sensorsfront.h"
//#include "blocks.h"
//#include <QtGui>
#include <QApplication>
//#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QGraphicsRectItem>
//#include <QGraphicsItem>
//#include "block.h"
//#include <QPixmap>
//#include <QDebug>
#include "view.h"


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
    QGraphicsScene* scene = new QGraphicsScene(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, &sensorView);

    // Background color
    QRadialGradient backgroundGradient(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 370); // 370 is gradient radius
    QColor DarkBlue(109, 118, 183); // color for outer
    QColor Blue(6, 35, 105); // color for center point
    backgroundGradient.setColorAt(0, DarkBlue);
    backgroundGradient.setColorAt(1, Blue);
    scene->setBackgroundBrush(backgroundGradient); // set background color

    sensorView.setScene(scene); // sets the scene

    View front(scene, frontView); // defines front view (so all the blocks and view in general)

    MainWindow w(front); // must be defined after View (cause it's its parameter)

    w.setWindowTitle("Configuration"); // sets title to configuration window
    sensorView.setWindowTitle("Sensors"); // sets title to sensors view

    w.show();
    sensorView.show();
    return app.exec();
}
