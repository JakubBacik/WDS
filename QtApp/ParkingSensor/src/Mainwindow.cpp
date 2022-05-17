#include "../inc/Mainwindow.hh"
#include "ui_mainwindow.h"

/*!
 * Konstruktor klasy MainWindow w którym ustawiane jest ui oraz skonfigurowany został timer
 * \param parent - klasa bazowa
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setAttribute(Qt::WA_DeleteOnClose, false);
    setAttribute(Qt::WA_QuitOnClose);
    ui->setupUi(this);
    initConfiguration();
    connect(_qTimer, SIGNAL(timeout()), this, SLOT(onStopertimeout()));
    _qTimer->setInterval(100);
    _qTimer->setSingleShot(true);
    _qTimer->start();
}

/*!
 * Destruktor klasy MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * Metoda wywołana gdy zostanie naciśnięty przycisk polaczenia na pasku.
 */
void MainWindow::on_actionConfiguration_triggered()
{
    if(_numberOfDialogWindow == 0){
        _connectionDialog = new ConnectionDialog(this);
        _connectionDialog->show();
        connect(_connectionDialog, SIGNAL(SendTo(QString)), this, SLOT(ConnectDevices(QString)));
        connect(_connectionDialog, SIGNAL(ChangeNumberOfWindow()), this, SLOT(ChangeNumber()));
        _numberOfDialogWindow = 1;
    }
}

/*!
 * Metoda wywołana po naciśnięciu przycisku połacz w oknie dialogowym
 * \param portName - nazwa portu
 */
void MainWindow::ConnectDevices(QString portName){
    _communication->Start();
    _communication->SetPortName(portName.toStdString());
    _myQThread = new MyQThread(_communication);
    _myQThread->start();
    _isConnection=true;
    ui->MainWindowStatusBar->showMessage(tr("Urządzenie zostało połączone"), 2000);

}

/*!
 * Metoda wywołana po naciśnięciu przycisku rozłącz w oknie dialogowym
 */
void MainWindow::DisconnectDevices(){
    _communication->Stop();
    _isConnection=false;
    deleteConfiguration();
    ui->MainWindowStatusBar->showMessage(tr("Urządzenie zostało rozłączone"), 2000);
}

/*!
 * Metoda wywoływana podczas zamnknięcia okna
 * \param pEvent
 */
void MainWindow::closeEvent(QCloseEvent *pEvent){
    _communication->Stop();
    _isConnection=false;
    pEvent->accept();

}

/*!
 * Metoda wywoływana cyklicznie co określony czas za pomoca QTimer
 */
void MainWindow::onStopertimeout(){
    std::string stringToParse;
    std::string string;
    int sensor[4];

    if(_isConnection){
        while(_communication->GetConstDataBuffer().IsString()){
            if(!_communication->GetDataBuffer().GetString(string))continue;
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
 * Metoda odpowiedzialna za parsowanie danych wejściowych.
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
 * Metoda odpowiedzialna za ustawienie wartości labelów w oknie głównym.
 */
void MainWindow::showData(){
    _second++;

    ui->labelSensor1->setNum(_sensor[0]);
    ui->labelSensor2->setNum(_sensor[1]);
    ui->labelSensor3->setNum(_sensor[2]);
    ui->labelSensor4->setNum(_sensor[3]);
    if(((_second%10) ==0)){
        std::cerr<<_second << std::endl;
        _myQChart->updateData(_sensor, _second/10);
    }
    ui->labelSensorView1->setPixmap(_frontAnimation->WhichRangeLOn(_sensor));
    ui->labelSensorView2->setPixmap(_frontAnimation->WhichRangePOn(_sensor));


}

/*!
 * Metoda odpowiedzialna za zainicjowanie wykresów oraz bitmap
 */
void MainWindow::initConfiguration(){
    _myQChart->initChart();
    ui->graphicsViewPlot1->setChart(_myQChart->getChart(0));
    ui->graphicsViewPlot2->setChart(_myQChart->getChart(1));
    ui->graphicsViewPlot3->setChart(_myQChart->getChart(2));
    ui->graphicsViewPlot4->setChart(_myQChart->getChart(3));
    ui->labelCar->setPixmap(_frontAnimation->SetCurrentRange(0,0,1).scaled(ui->labelCar->width(), ui->labelCar->height(), Qt::KeepAspectRatio));
    ui->labelSensorView1->setPixmap(_frontAnimation->SetCurrentRange(1,0,1).scaled(ui->labelSensorView1->width(), ui->labelSensorView1->height(), Qt::KeepAspectRatio));
    ui->labelSensorView2->setPixmap(_frontAnimation->SetCurrentRange(2,0,1).scaled(ui->labelSensorView2->width(), ui->labelSensorView2->height(), Qt::KeepAspectRatio));
}

/*!
 * Metoda odpowiedzialna za wyczyszczenie wykresów z danych oraz ustawie podstawowych bitmap
 */
void MainWindow::deleteConfiguration(){
    ui->labelSensor1->setNum(0);
    ui->labelSensor2->setNum(0);
    ui->labelSensor3->setNum(0);
    ui->labelSensor4->setNum(0);
    _second=0;
    _myQChart->clearChart();
    ui->labelSensorView1->setPixmap(_frontAnimation->SetCurrentRange(1,0,1).scaled(ui->labelSensorView1->width(), ui->labelSensorView1->height(), Qt::KeepAspectRatio));
    ui->labelSensorView2->setPixmap(_frontAnimation->SetCurrentRange(2,0,1).scaled(ui->labelSensorView2->width(), ui->labelSensorView2->height(), Qt::KeepAspectRatio));
}


/*!
 * Metoda która zostanie wywołana po naciśnięciu przycisku z menu wysuwanego
 * zmniejacy jezyk na polski
 */
void MainWindow::on_actionPolski_triggered()
{
    qApp->removeTranslator(translator);
    ui->retranslateUi(this);
    initConfiguration();
}
/*!
* Metoda która zostanie wywołana po naciśnięciu przycisku z menu wysuwanego
* zmniejacy jezyk na angielski
*/
void MainWindow::on_actionAngielski_triggered()
{
    if(translator->load(":/translate/translation/ParkingSensor_en_150.qm", ".")){
        qApp->installTranslator(translator);
    }else{
        std::cerr << "Plik nie został załadowany" << std::endl;
    }
    ui->retranslateUi(this); 
    initConfiguration();
}

