/**
* @file main.cpp
* @brief Główny plik programu
*
* @author Michał Dołharz
*
*/

#include "mainwindow.h"
#include "sensorsfront.h"

#include <QApplication>

/*!
 * \brief qMain Funkcja main() programu.
 * \param argc Liczba parametrów wejściowych.
 * \param argv Parametry wejściowe.
 * \return Działanie programu.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    SensorsFront s;

    w.setWindowTitle("Configuration");
    s.setWindowTitle("Front sensors");

    w.show();
    s.show();
    return app.exec();
}
