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
#include "inc/CircleAnimation.hh"
#include <QPixmap>
#include "inc/FrontAnimation.hh"
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
    QTranslator *translator = new QTranslator();
    FrontAnimation* _frontAnimation = new FrontAnimation();
    MyQChart* _myQChart = new MyQChart();
    Communication* _communication =new Communication();
    MyQThread* _myQThread;
    int number1 = 0;
    int number2 = 0;
    int _sensor[4] = {0,0,0,0};
    int _second = 0;
    int _numberOfDialogWindow = 0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool ParseDataFrame(const char* pDataFrame, int *sensor);
    uint16_t processBuffer(const char *data_p, uint16_t length);
    uint16_t processByte(uint8_t data, uint16_t& crc);
    void initConfiguration();
    void deleteConfiguration();
    void showData();
    void defaultSetUp();

private:
    Ui::MainWindow *ui;
    ConnectionDialog *_connectionDialog;

public slots:
    void ConnectDevices(QString portName);
    void DisconnectDevices();
    void onStopertimeout();
    void ChangeNumber(){_numberOfDialogWindow =0;}

private slots:
    void on_actionConfiguration_triggered();
    void on_actionPolski_triggered();
    void on_actionAngielski_triggered();

protected:
    void closeEvent(QCloseEvent *pEvent)override;

};
#endif // MAINWINDOW_H
