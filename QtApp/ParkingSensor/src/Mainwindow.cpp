#include "../inc/Mainwindow.hh"
#include "ui_mainwindow.h"

/*!
 * \brief Konstruktor klasy MainWindow w którym ustawiane jest ui oraz skonfigurowany został timer
 * \param parent - klasa bazowa
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setAttribute(Qt::WA_DeleteOnClose, false);
    setAttribute(Qt::WA_QuitOnClose);
    ui->setupUi(this);

    connect(_qTimer, SIGNAL(timeout()), this, SLOT(onStopertimeout()));
    _qTimer->setInterval(1000);
    _qTimer->setSingleShot(true);
    _qTimer->start();
}

/*!
 * \brief Destruktor klasy MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Metoda wywołana gdy zostanie naciśnięty przycisk
 * na pasku okna.
 */
void MainWindow::on_actionConfiguration_triggered()
{
    _connectionDialog = new ConnectionDialog(this);
    _connectionDialog->show();
    connect(_connectionDialog, SIGNAL(SendTo(QString)), this, SLOT(ConnectDevices(QString)));
}

/*!
 * \brief Metoda wywołana po naciśnięciu przycisku połacz w oknie dialogowym
 * \param portName - nazwa portu
 */
void MainWindow::ConnectDevices(QString portName){
    communication->Start();
    communication->SetPortName(portName.toStdString());
    myQThread = new MyQThread(communication);
    myQThread->start();
    _isConnection=true;

}

/*!
 * \brief Metoda wywołana po naciśnięciu przycisku rozłacz w oknie dialogowym
 */
void MainWindow::DisconnectDevices(){
    communication->Stop();
    _isConnection=false;
}

/*!
 * \brief Metoda wywoływana podczas zamnkniecia okna
 * \param pEvent
 */
void MainWindow::closeEvent(QCloseEvent *pEvent){
    communication->Stop();
    _isConnection=false;
    pEvent->accept();

}

/*!
 * \brief Metoda wywoływana cyklicznie co określony czas za pomoca QTimer
 */
void MainWindow::onStopertimeout(){
    std::string stringToParse;
    std::string string;
    int sensor[4];

    if(_isConnection){
        while(communication->GetConstDataBuffer().IsString()){
            if(!communication->GetDataBuffer().GetString(string))continue;   
            stringToParse += string;
        }
        if(ParseDataFrame(stringToParse.c_str(), sensor)){
            for(int i=0; i<4; i++){
                _sensor[i] = sensor[i];
            }
        }
        showData();
     }

    _qTimer->start();
}

/*!
 * \brief Metoda odpowiedzialna za parsowanie danych wejściowych.
 * \param pDataFrame - dane wejściowe
 * \param sensor - tablica sensorów
 * \retval false - jeśli dane wejściowe nie są w formie zakładanej ramki
 * \retval true - w przeciwnym przypadku
 */
bool MainWindow::ParseDataFrame(const char* pDataFrame, int *sensor){
    std::istringstream iStrm(pDataFrame);
    char fHeader;
    uint16_t  cRC16;

    iStrm >> fHeader >> sensor[0] >> sensor[1] >> sensor[2] >> sensor[3] >> std::hex >> cRC16;

    if(fHeader != 'X' || iStrm.fail()){
        return false;
    }
    return cRC16 == processBuffer(pDataFrame, strlen(pDataFrame)-5);
}

/*!
 * \brief MainWindow::processByte
 * Funkcja odpowiedzialna za konwersje jednego znaku.
 * \param data - jeden znak do konwersji
 * \param crc - wartość po konwersji
 * \return zwrócony jest jeden
 */
uint16_t MainWindow::processByte(uint8_t data, uint16_t& crc) {
  uint8_t i;

  crc = crc ^ ((uint16_t)data << 8);
  for (i = 0; i < 8; i++) {
    if (crc & 0x8000)
      crc = (crc << 1) ^ POLY;
    else
      crc <<= 1;
  }
  return crc;
}

/*!
 * \brief MainWindow::processBuffer
 * Funkcja odpowiedzialna za obliczenie sumy kontrolnej
 * \param data_p - łancuch znakowy
 * \param length - długość łancucha zankowego
 * \return zwrócona jest suma kontrolna CRC16
 */
uint16_t MainWindow::processBuffer(const char *data_p, uint16_t length) {
  uint16_t crc= 0;
  while(length--) {
    processByte(*data_p++, crc);
  }

  return crc;
}

/*!
 * \brief MainWindow::showData
 * Funkcja odpowiedzialna za ustawienie wartości labelów w oknie głównym.
 */
void MainWindow::showData(){
    second++;
    ui->labelSensor1->setNum(_sensor[0]);
    ui->labelSensor2->setNum(_sensor[1]);
    ui->labelSensor3->setNum(_sensor[2]);
    ui->labelSensor4->setNum(_sensor[3]);
    myQChart->updateData(_sensor, second);
    ui->labelSensorView1->setPixmap(_frontAnimation->WhichRangeLOn(_sensor));
    ui->labelSensorView34->setPixmap(_frontAnimation->WhichRangePOn(_sensor));
}

void MainWindow::initConfiguration(){
    myQChart->initChart();
    ui->graphicsViewPlot1->setChart(myQChart->getChart(0));
    ui->graphicsViewPlot2->setChart(myQChart->getChart(1));
    ui->graphicsViewPlot3->setChart(myQChart->getChart(2));
    ui->graphicsViewPlot4->setChart(myQChart->getChart(3));
    int w = ui->labelCar->width();
    int h = ui->labelCar->height();
    ui->labelCar->setPixmap(_frontAnimation->SetCurrentRange(0,0,1).scaled(w,h,Qt::KeepAspectRatio));
    int w1= ui->labelSensorView1->width();
    int h1 = ui->labelSensorView1->height();
    ui->labelSensorView1->setPixmap(_frontAnimation->SetCurrentRange(1,0,1).scaled(w1,h1,Qt::KeepAspectRatio));
    int w2= ui->labelSensorView34->width();
    int h2 = ui->labelSensorView34->height();
    ui->labelSensorView34->setPixmap(_frontAnimation->SetCurrentRange(2,0,1).scaled(w2,h2,Qt::KeepAspectRatio));
}


void MainWindow::deleteConfiguration(){
    int w1= ui->labelSensorView1->width();
    int h1 = ui->labelSensorView1->height();
    ui->labelSensorView1->setPixmap(_frontAnimation->SetCurrentRange(1,0,1).scaled(w1,h1,Qt::KeepAspectRatio));
    int w2= ui->labelSensorView34->width();
    int h2 = ui->labelSensorView34->height();
    ui->labelSensorView34->setPixmap(_frontAnimation->SetCurrentRange(2,0,1).scaled(w2,h2,Qt::KeepAspectRatio));
}


