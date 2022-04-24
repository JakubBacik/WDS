/********************************************************************************
** Form generated from reading UI file 'connectionwitharduino.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtSerialPort>
#include <QDialog>
#include "ui_connectionwitharduino.hh"

/*!
 * \brief Klasa definujaca wybor portu poprzez okno dialogowe
 */
class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectionDialog(QWidget *parent = 0);

private:
    Ui::ConnectionWithArduinoClass ui;

signals:
    void SendTo(QString portName);

private slots:
    void setPortName();
};

#endif // UI_CONNECTIONWITHARDUINO_H
