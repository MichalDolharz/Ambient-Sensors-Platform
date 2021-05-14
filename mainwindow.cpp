#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OSOS_CRC8.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}

MainWindow::MainWindow(View &view, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    front = &view;
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

// Przycisk "Szukaj"
void MainWindow::on_pushButtonSearch_clicked()
{
    // informacja do logow
    this->addToLogs("Szukanie urządzeń...");

    // Lista przechowuje urządzenia na portach COM, dane dostarczane z funkcji
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();

    // Usuwa wszystkie elementy z comboBoxDevices
    ui->comboBoxDevices->clear();

    // Wypisuje dostepne porty do comboBoxDevices
    if (devices.isEmpty())
    {
        this->addToLogs("Nie wykryto żadnych urządzeń.");
    }
    else
    {
        for (int i = 0; i < devices.count(); i++)
        {
            this->addToLogs("Znaleziono urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
            ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
        }
    }
}

// Dodawanie wiadomosci do pola tekstowego "Logi"
void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}

// Dodawanie wiadomosci do pola tekstowego "Komunikacja"
void MainWindow::addToComm(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEditCommunication->append(currentDateTime + "\t" + message);
}

// Laczenie z mikrokontrolerem przyciskiem "Polacz"
void MainWindow::on_pushButtonConnect_clicked()
{
    // Sprawdza, czy sa dostepne urzadzenia w comboBoxDevices
    if (ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("Brak dostępnych urządzeń.");
    }

    // Pobiera numer portu COM (rozdzielajac nazwe i opis)
    // z aktualnie wyswietlanego pola z comboBoxDevices
    QString portName = ui->comboBoxDevices->currentText().split(" ").first();
    this->device->setPortName(portName);

    // Sprawdza, czy jakis port nie jest juz otworzony
    if (!device->isOpen())
    {
        // Otwiera port. Jezeli z powodzeniem, to konfiguruje go wedlug podanych parametrow
        if (device->open(QSerialPort::ReadWrite))
        {
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            // laczenie sygnalu ze slotem
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));

            // informacja do logow
            this->addToLogs("Otwarto port szeregowy " + portName);
        }
        // Jezeli otwarcie portu sie nie powiodlo
        else
        {
            this->addToLogs("Otwarcie portu szeregowego nieudane.");
        }
    }
    else
    {
        this->addToLogs("Port jest już otworzony.");
    }
}

// Zamyka polaczenie przyciskiem "Rozlacz i zamknij"
void MainWindow::on_pushButtonClose_clicked()
{
    // Sprawdza, czy port jest otwarty. Jezeli tak, to zamyka.
    if(this->device->isOpen()) {
      this->device->close();

      this->addToLogs("Zamknięto połączenie.");
    }
    // Informacja o braku otwartego portu
    else {
      this->addToLogs("Port nie jest otwarty.");
    }
}

// Currently not used, but might be used in the future
/*void MainWindow::demandRepeat() {
  if(this->device->isOpen() && this->device->isWritable()) {
    //this->addToLogs("Sending repeat demand");
    this->device->write("REPEAT");
  } else {
    this->addToLogs("Can't send repeat command. The port is closed.");
  }
}*/

// Czytanie danych z otworzonego potru
void MainWindow::readFromPort() {
  while(this->device->canReadLine()) {
    QString msg = this->device->readAll();

    // Informacja o odebraniu danych
    //qDebug() << "Odebrano dane: " <<msg;

    //QString terminator = "\r\n";
    int pos = msg.lastIndexOf("\r\n"); // zwraca numer pozycji \r\n w stringu
    msg = msg.left(pos); // "ucina" wszystkie znaki poczawszy od zadanego indeksu

    int sensor, status;

    if(ParseDataFrame(msg.toLocal8Bit().data(), sensor, status))
    {
        //qDebug() << "Parsowanie ramki |" + msg + "| udane";
        this->addToLogs("Parsowanie ramki |" + msg + "| udane");
        this->addToComm("Sensor: " + QString::number(sensor) + " status: " + QString::number(status));
        if(sensor<5)
            front->setStatus(sensor, status);

    }
    else
    {
        //qDebug() << "PARSOWANIE RAMKI |" + msg + "| NIEUDANE";
        this->addToLogs("PARSOWANIE RAMKI |" + msg + "| NIEUDANE");
        //this->demandRepeat();
    }
  }
}


