#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include "ConnectionDialog.hh"
#include "inc/DataBuffer.hh"
#include "inc/CommunicationAndMyQThread.hh"
#include "inc/MyQChart.hh"
#include <QTimer>
#include <QCloseEvent>
#include <iostream>
#include <sstream>
#include <string>
#include <QtCharts>
#include <QLineSeries>
#define POLY 0x1021

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 *\brief Definicja okna głownego
 * Klasa ta jest definicją okna głownego odpowiedzalnego za wizualizacje.
 *
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer *_qTimer = new QTimer(this);
    bool _isConnection = false;

public:
    int second = 0;
    MyQChart* myQChart = new MyQChart();
    int _sensor[4] = {0,0,0,0};
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Communication *communication =new Communication();
    MyQThread* myQThread;
    bool ParseDataFrame(const char* pDataFrame, int *sensor);
    uint16_t processBuffer(const char *data_p, uint16_t length);
    uint16_t processByte(uint8_t data, uint16_t& crc);
    void showData();
    void defaultSetUp();

private:
    Ui::MainWindow *ui;
    ConnectionDialog *_connectionDialog;

public slots:
    void ConnectDevices(QString portName);
    void DisconnectDevices();
    void onStopertimeout();

private slots:
    void on_actionConfiguration_triggered();
protected:
    void closeEvent(QCloseEvent *pEvent)override;
};
#endif // MAINWINDOW_H
