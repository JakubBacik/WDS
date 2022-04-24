#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include "ConnectionDialog.hh"
#include "inc/DataBuffer.hh"
#include "inc/CommunicationAndMyQThread.hh"
#include <QTimer>
#include <QCloseEvent>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 *\brief Definicja okna glownego
 * Klasa ta jest definicja okna glownego odpowiedzalne za wizualizacje.
 *
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
