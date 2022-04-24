/********************************************************************************
** Form generated from reading UI file 'connectionwitharduino.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONNECTIONWITHARDUINO_H
#define CONNECTIONWITHARDUINO_H

#include <QtCore/QVariant>
#include <QtSerialPort>
#include <QDialog>
#include "ui_connectionwitharduino.hh"

class ConnectionWithArduino : public QDialog
{
    Q_OBJECT
public:
    ConnectionWithArduino(QWidget *parent = 0);

private:
    Ui::ConnectionWithArduinoClass ui;

signals:
    void SendTo(QString portName);

private slots:
    void changePortName();
};

#endif // UI_CONNECTIONWITHARDUINO_H
