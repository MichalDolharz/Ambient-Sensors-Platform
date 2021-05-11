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
    Q_OBJECT //<! Główny obiekt klasy

public:
    /*! \brief Konstruktor klasy MainWindow
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief MainWindow constructor with View object handle.
     */
    MainWindow(View &view, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*! \brief Odczytuje dane przychodzące z mikrokontrolera poprzez komunikację UART.
     */
    void readFromPort();

    // Currently not used, but might be used in the future
    //void demandRepeat();

    /*! \brief Slot przycisku "Szukaj".
     *  Wyszukuje dostępne porty COM.
     */
    void on_pushButtonSearch_clicked();

    /*! \brief Slot przycisku "Połącz".
     *  Łączy z portem wyświetlanym w zakładce obok.
     */
    void on_pushButtonConnect_clicked();

    /*! \brief Slot przycisku "Rozłącz".
     *  Kończy połączenie z portem.
     */
    void on_pushButtonClose_clicked();

private:
    Ui::MainWindow *ui; /**< \brief Główne okno programu. */
    QSerialPort *device; /**< \brief Urządzenie, z którym aplikacja komunikuje się poprzez UART. */

    /** @brief Funkcja wysyła wiadomość do okna z logami.
     *  @param[in] message Wiadomość do wysłania.
    */
    void addToLogs(QString message);
    /** @brief Funkcja wysyła wiadomość do okna z wiadomościami komunikacji.
     *  @param[in] message Wiadomość do wysłania.
    */
    void addToComm(QString message);

    View *front; //!< Handle to a View object.
};
#endif // MAINWINDOW_H
