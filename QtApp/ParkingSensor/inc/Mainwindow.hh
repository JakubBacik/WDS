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
#include <QPixmap>
#include "inc/FrontAnimation.hh"
#define POLY 0x1021

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 *\brief Klasa modelująca okno głównego
 * Klasa modelująca okno główne wyświetlające animacje, zakładke wykres,
 * gdzie znajdują się cztery wykresy.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*!
     * \brief Timer
     * Wskaźnik na obiekt klasy QTimer, opowiedzialny za zliczanie czasu
     */
    QTimer *_qTimer = new QTimer(this);
    /*!
     * \brief Połączenie
     * Zmienna, definująca czy połączenie się odbywa czy zostało zaniechane
     */
    bool _isConnection = false;

public:
    /*!
     * \brief Etykieta
     * Wskaźnik na obiekt klasy QLabel, definująca etykiety wyświetlające odległości
     */
    QLabel *sensorLabel[4];
    /*!
     * \brief Tłumaczenie
     * Wskaźnik na obiekt klasy QTranslator, odpowiedzialna za tłumaczenia
     */
    QTranslator *translator = new QTranslator();
    /*!
     * \brief Animacja przed samochodem
     * Wskaźnik na obiekt klasy FrontAnimation, odpowiedzialna za animacje przed samochodem
     */
    FrontAnimation* _frontAnimation = new FrontAnimation();
    /*!
     * \brief Wykresy
     * Wskaźnik na obiekt klasy MyQChart, definująca wykresy
     */
    MyQChart* _myQChart = new MyQChart();
    /*!
     * \brief Komunikacja
     * Wskaźnik na obiekt klasy Communication, odpowiedzialny za komunikacje
     */
    Communication* _communication =new Communication();
    /*!
     * \brief Wątek
     * Wskaźnik na obiekt klasy MyQThread, odpowiedzialny za osobny wątek
     */
    MyQThread* _myQThread;
    /*!
     * \brief Czujnik
     * Tablica przechowująca cztery wartości typu int.
     */
    int _sensor[4] = {0,0,0,0};
    /*!
     * \brief Czas
     * Zmienna przechowująca liczbe sekund od momentu włączenia aplikacji
     */
    int _second = 0;
    /*!
     * \brief Liczba okien dialogowych
     * Zmienna odpowiedzialna za przechowywanie liczby otwartych okienek dialogowych
     */
    int _numberOfDialogWindow = 0;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool ParseDataFrame(const char* pDataFrame, int *sensor);
    uint16_t processBuffer(const char *data_p, uint16_t length);
    uint16_t processByte(uint8_t data, uint16_t& crc);
    void initFrontAnimationConfiguration();
    void initSensorLabelConfiguration();
    void deleteFrontAnimationonfiguration();
    void showData();
    void deleteSensorLabelConfiguration();
    void resizeEvent(QResizeEvent* event) override;

private:
    /*!
     * \brief Interfejs użytkownika
     * Interfejs użytkowanika okna głównego
     */
    Ui::MainWindow *ui;
    /*!
     * \brief Okno dialogowe
     * Wskaźnik na obiekt klasy ConnectionDialog, definująca okno dialogowe
     */
    ConnectionDialog *_connectionDialog;

public slots:
    void ConnectDevices(QString portName);
    void DisconnectDevices();
    void onStopertimeout();
    /*!
     * \brief Zamknięcie okna dialogowego
     * Metoda odpowiedzialna za zmiane wartości zmiennej przechowującej aktualną liczbe otwartych okien na wartość zero czy brak otwartych okien.
     */
    void ChangeNumber(){_numberOfDialogWindow =0;}

private slots:
    void on_actionConfiguration_triggered();
    void on_actionPolski_triggered();
    void on_actionAngielski_triggered();
    void on_tabWidget_tabBarClicked(int index);

protected:
    void closeEvent(QCloseEvent *pEvent)override;

};
#endif // MAINWINDOW_H
