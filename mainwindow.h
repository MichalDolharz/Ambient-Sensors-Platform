/**
* @file mainwindow.h
* @brief Plik nagłówkowy dla mainwindow.cpp
*
* @author Michał Dołharz
*
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "QtDebug"
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include "view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*! \file mainwindow.h
 */

/*!
 * \brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT //<! Main class object.

public:
    /*! \brief MainWindow class constructor
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief MainWindow class constructor with View object handle.
     */
    MainWindow(View &view, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*! \brief Reads data from UART communication from sensors platform.
     */
    void readFromPort();

    /*! \brief Slot of "Search" button.
     *  Searches for available COM ports.
     */
    void on_pushButtonSearch_clicked();

    /*! \brief Slot of "Connect" button.
     *  Connects with the port being displayed in the comboBox nearby.
     */
    void on_pushButtonConnect_clicked();

    /*! \brief Slot of "Disconnect" button.
     *  Closes connection with COM port.
     */
    void on_pushButtonClose_clicked();

private:
    Ui::MainWindow *ui; //!< Application main window.
    QSerialPort *device; //!< The device with which the communication is set.
    View *view; //!< Handle to a View object.

    /** @brief Sends info to logs.
     *  @param[in] message Message to be sent.
    */
    void addToLogs(QString message);
    /** @brief Sends info to communications.
     *  @param[in] message Message to be sent.
    */
    void addToComm(QString message);
};
#endif // MAINWINDOW_H
