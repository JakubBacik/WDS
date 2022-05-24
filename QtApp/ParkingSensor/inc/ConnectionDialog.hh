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
#include <QCloseEvent>
#include "ui_connectionwitharduino.hh"

/*!
 * \brief Klasa modelująca pojęcie ConnectionDialog
 * Klasa modelująca okno dialogowe umożliwiające
 * konfigurowanie połączenia.
 */
class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectionDialog(QWidget *parent = 0);

private:
    /*!
     * \brief Ui okno dialogowe
     * ui okna dialogowego konfigurowania połączenia
     */
    Ui::ConnectionWithArduinoClass ui;

signals:
    /*!
     * \brief Wysłanie nazwy portu
     * Sygnał odpowiedzialny za wysłanie nazwy portu do głównego okna
     */
    void SendTo(QString portName);
    /*!
     * \brief Wysłane po zamknięciu okna dialogowego
     * Sygnał odpowiedzialny za wysłanie informacji o zmniejszeniu się liczby
     * otwartych okien dialogowych po zamknięciu okna dialogowego
     */
    void ChangeNumberOfWindow();

private slots:
    void setPortName();
    void closeEvent(QCloseEvent *event);
};

#endif // UI_CONNECTIONWITHARDUINO_H
