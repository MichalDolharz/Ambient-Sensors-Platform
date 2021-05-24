#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OSOS_CRC8.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}

MainWindow::MainWindow(View &view_ref, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    view = &view_ref;
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

// "Search" button
void MainWindow::on_pushButtonSearch_clicked()
{
    this->addToLogs("Looking for devices...");

    // Contain found devices
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();

    // Clear comboBoxDevices (some might be old)
    ui->comboBoxDevices->clear();

    // Write newly found devices
    if (devices.isEmpty())
    {
        this->addToLogs("No available devices found.");
    }
    else
    {
        for (int i = 0; i < devices.count(); i++)
        {
            this->addToLogs("Device found: " + devices.at(i).portName() + " " + devices.at(i).description());
            ui->comboBoxDevices->addItem(devices.at(i).portName() + " " + devices.at(i).description());
        }
    }
}

// Add info to logs
void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEditLogs->append(currentDateTime + "\t" + message);
}

// Add info to communications
void MainWindow::addToComm(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    ui->textEditCommunication->append(currentDateTime + "\t" + message);
}

// Slot for "Connect button"
void MainWindow::on_pushButtonConnect_clicked()
{
    // Check if there are available devices in comboBoxDevices
    if (ui->comboBoxDevices->count() == 0)
    {
        this->addToLogs("No available devices found.");
    }

    // Get COM from string (from comboBoxDevices), splitting it with a space
    QString portName = ui->comboBoxDevices->currentText().split(" ").first();
    this->device->setPortName(portName);

    // Check if there is any open port.
    if (!device->isOpen())
    {
        // Open ports. If succesfull, configure it.
        if (device->open(QSerialPort::ReadWrite))
        {
            this->device->setBaudRate(QSerialPort::Baud9600);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);

            // Connecting slot with signal
            connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));

            // Information to logs
            this->addToLogs("Port " + portName + " is opened.");
        }
        // If opening port failed
        else
        {
            this->addToLogs("Opening the port failed.");
        }
    }
    else
    {
        this->addToLogs("The port is already open.");
    }
}

// Close connection with "Disconnect" button.
void MainWindow::on_pushButtonClose_clicked()
{
    // If a port is open, close it.
    if(this->device->isOpen()) {
      this->device->close();

      this->addToLogs("Connection closed.");
    }
    // No open port information to logs.
    else {
      this->addToLogs("None of the ports is open.");
    }
}

// Reading from open port.
void MainWindow::readFromPort() {
  while(this->device->canReadLine()) {
    QString msg = this->device->readAll();

    int pos = msg.lastIndexOf("\r\n"); // returns \r\n position in string index
    msg = msg.left(pos); // cuts all signs starting with \r\n

    int sensor, status;

    if(ParseDataFrame(msg.toLocal8Bit().data(), sensor, status))
    {
        this->addToLogs("Data frame |" + msg + "| parsing successful");
        this->addToComm("Sensor: " + QString::number(sensor) + " status: " + QString::number(status));

        view->updateScreen(sensor, status);


    }
    else
    {
        this->addToLogs("DATA FRAME |" + msg + "| PARSING FAILED");
    }
  }
}


