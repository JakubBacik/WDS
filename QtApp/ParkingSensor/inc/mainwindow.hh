#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QtSerialPort>
#include "connectionwitharduino.hh"
#include "inc/BuforDanych.hh"
#include "inc/WatekOdbioru.hh"
#include <QTimer>
#include <QCloseEvent>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 *\brief Definicja okna glownego
 *
 *Klasa ta jest definicja okna glownego
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer *_qTimer = new QTimer(this);
    bool _isConnection = false;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Communication *communication =new Communication();
    MyQThread* myQThread;

private:
    Ui::MainWindow *ui;
    ConnectionWithArduino *connectionWithArduino;

public slots:
    void ChangeCurrentPort(QString portName);
    void DisconnectDevices();
    void onStopertimeout();

private slots:
    void on_actionConfiguration_triggered();
protected:
    void closeEvent(QCloseEvent *pEvent)override;
};
#endif // MAINWINDOW_HH
