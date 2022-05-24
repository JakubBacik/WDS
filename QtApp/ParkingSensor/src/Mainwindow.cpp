#include "../inc/Mainwindow.hh"
#include "ui_mainwindow.h"

/*!
 * \brief Konstruktor klasy
 * Konstruktor klasy MainWindow w którym ustawiane jest ui, konfigurowany jest timer, animacja przed samochodem i etykiety wyświetlające wartości
 * \param[in] parent - klasa bazowa
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setAttribute(Qt::WA_DeleteOnClose, false);
    setAttribute(Qt::WA_QuitOnClose);
    ui->setupUi(this);
    initFrontAnimationConfiguration();
    connect(_qTimer, SIGNAL(timeout()), this, SLOT(onStopertimeout()));
    _qTimer->setInterval(100);
    _qTimer->setSingleShot(true);
    _qTimer->start();
    initSensorLabelConfiguration();
    deleteSensorLabelConfiguration();
}

/*!
 * \brief Destruktor klasy
 * Destruktor klasy MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Naciśniecie przycisku konfiguracja
 * Metoda wywołana, po naciśnięty przycisku połącz na rozwijanej liscie po naciśnięciu przycisku ustawienia, wyowłująca metode, odpowiedzialna za przeszukiwanie aktywnych portów.
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
 * \brief Naciśniecie przycisku połącz
 * Metoda wywołana po naciśnięciu przycisku połacz w oknie dialogowym
 * \param[in] portName - nazwa portu np. ttyACM0
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
 * \brief Naciśniecie przycisku rozłącz
 * Metoda wywołana po naciśnięciu przycisku rozłącz w oknie dialogowym
 */
void MainWindow::DisconnectDevices(){
    _communication->Stop();
    _isConnection=false;
    deleteFrontAnimationonfiguration();
    ui->MainWindowStatusBar->showMessage(tr("Urządzenie zostało rozłączone"), 2000);
}

/*!
 * \brief Zamknięcie okna
 * Metoda wywoływana podczas zamnknięcia okna
 * \param[in] pEvent - wskaźnik na obiekt klasy QCloseEvent
 */
void MainWindow::closeEvent(QCloseEvent *pEvent){
    _communication->Stop();
    _isConnection=false;
    pEvent->accept();

}

/*!
 * \brief Po przepełnieniu timera
 * Metoda wywoływana cyklicznie co określony czas za pomoca QTimer, odpowiedzialna za pobieranie danych oraz wstawianie aktualnych wartości do etykiet.
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
 * \brief Parsowanie danych
 * Metoda odpowiedzialna za parsowanie danych wejściowych.
 * \param[in] pDataFrame - dane wejściowe
 * \param[in] sensor - tablica sensorów
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
 * \brief Jeden byte konwersja
 * Funkcja odpowiedzialna za konwersje jednego znaku.
 * \param[in] data - jeden znak do konwersji
 * \param[in] crc - wartość po konwersji
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
 * \brief konwersja do CRC16
 * Funkcja odpowiedzialna za obliczenie sumy kontrolnej
 * \param[in] data_p - łancuch znakowy
 * \param[in] length - długość łancucha zankowego
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
 * \brief Aktualizowanie danych
 * Metoda odpowiedzialna za aktualizowanie wartości etykiet w oknie głównym, danych w wykresie oraz odpowiedniej bitmapy przed samochodem.
 */
void MainWindow::showData(){
    _second++;

    sensorLabel[0]->setNum(_sensor[0]);
    sensorLabel[1]->setNum(_sensor[1]);
    sensorLabel[2]->setNum(_sensor[2]);
    sensorLabel[3]->setNum(_sensor[3]);
    _myQChart->updateData(_sensor, _second);
    ui->labelSensorView1->setPixmap(_frontAnimation->WhichRangeLOn(_sensor));
    ui->labelSensorView2->setPixmap(_frontAnimation->WhichRangePOn(_sensor));
    ui->labelSensorView1->setScaledContents(true);
    ui->labelSensorView2->setScaledContents(true);

}

/*!
 * \brief Inicjalizacja animacji przed samochodem
 * Metoda odpowiedzialna za zainicjowanie wykresów oraz początkowej bitmapy przed samochodem
 */
void MainWindow::initFrontAnimationConfiguration(){
    _myQChart->initChart();
    ui->graphicsViewPlot1->setChart(_myQChart->getChart(0));
    ui->graphicsViewPlot2->setChart(_myQChart->getChart(1));
    ui->graphicsViewPlot3->setChart(_myQChart->getChart(2));
    ui->graphicsViewPlot4->setChart(_myQChart->getChart(3));
    ui->labelSensorView1->setPixmap(_frontAnimation->SetCurrentRange(1,0,1));
    ui->labelSensorView2->setPixmap(_frontAnimation->SetCurrentRange(2,0,1));
    ui->labelSensorView1->setScaledContents(true);
    ui->labelSensorView2->setScaledContents(true);


}

/*!
 * \brief Usuwanie danych
 * Metoda odpowiedzialna za wyczyszczenie wykresów z danych oraz ustawie podstawowych bitmap
 */
void MainWindow::deleteFrontAnimationonfiguration(){
    _second=0;
    _myQChart->clearChart();
    deleteSensorLabelConfiguration();
    ui->labelSensorView1->setPixmap(_frontAnimation->SetCurrentRange(1,0,1));
    ui->labelSensorView2->setPixmap(_frontAnimation->SetCurrentRange(2,0,1));
    ui->labelSensorView1->setScaledContents(true);
    ui->labelSensorView2->setScaledContents(true);
}


/*!
 * \brief Zmiana języka na polski
 * Metoda która zostanie wywołana po naciśnięciu przycisku z menu wysuwanego
 * zmniejacy jezyk aplikacji na polski
 */
void MainWindow::on_actionPolski_triggered()
{
    qApp->removeTranslator(translator);
    ui->retranslateUi(this);
    _myQChart->translateChart();
}
/*!
 * \brief Zmania języka na angielski
* Metoda która zostanie wywołana po naciśnięciu przycisku z menu wysuwanego
* zmniejacy jezyk aplikacji na angielski
*/
void MainWindow::on_actionAngielski_triggered()
{
    if(translator->load(":/translate/translation/ParkingSensor_en_150.qm", ".")){
        qApp->installTranslator(translator);
    }else{
        std::cerr << "Plik nie został załadowany" << std::endl;
    }
    ui->retranslateUi(this); 
    _myQChart->translateChart();
}

/*!
 * \brief Zmiana okna dialogowego
 * Metoda odpowiedzialna za zmiane położenia etykiet odpowiedzialnych za wyświetlanie wartości dla czujników.
 */
void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   sensorLabel[0]->setGeometry((this->width() - this->width()/1.5), (this->height() - this->height()/2.45), 40, 40);
   sensorLabel[1]->setGeometry((this->width() - this->width()/1.8), (this->height() - this->height()/2.2), 40, 40);
   sensorLabel[2]->setGeometry((this->width() - this->width()/2.2), (this->height() - this->height()/2.2), 40, 40);
   sensorLabel[3]->setGeometry((this->width() - this->width()/2.9), (this->height() - this->height()/2.45), 40, 40);
}

/*!
 * \brief Naciśnięcie zakładki w oknie głównym
 * Metoda wywołana po naciśnięciu jednej z zakładki, powoduje wyświetlanie albo ukrycie etykiet odpowiedzialnych za wyświetlanie odpowiedniej wartości dla czujnika.
 */
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 1){
        sensorLabel[0]->hide();
        sensorLabel[1]->hide();
        sensorLabel[2]->hide();
        sensorLabel[3]->hide();
    }
    if(index == 0){
        sensorLabel[0]->show();
        sensorLabel[1]->show();
        sensorLabel[2]->show();
        sensorLabel[3]->show();
    }
}

/*!
 * \brief Inicjalizacja etykiet
 * Metoda odpowiedzalna za wstępną konfiguracje etykiet odpowiedzialnych za wyświetlanie wartości dla czujników
 */
void MainWindow::initSensorLabelConfiguration(){
    sensorLabel[0]=new QLabel(this);
    sensorLabel[0]->setGeometry((this->width() - 350), (this->height() - 150), 20, 20);
    sensorLabel[0]->show();
    sensorLabel[1]=new QLabel(this);
    sensorLabel[1]->setGeometry((this->width() - 290), (this->height() - 200), 20, 20);
    sensorLabel[1]->show();
    sensorLabel[2]=new QLabel(this);
    sensorLabel[2]->setGeometry((this->width() - 250), (this->height() - 200), 20, 20);
    sensorLabel[2]->show();
    sensorLabel[3]=new QLabel(this);
    sensorLabel[3]->setGeometry((this->width() - 200), (this->height() - 150), 20, 20);
    sensorLabel[3]->show();
}

/*!
 * \brief Usuwanie danych z etykiet
 * Metoda odpowiedzialna za wyzerowanie wartości etykiet odpowiedzialnych za wyświetlanie wartości dla czujników
 */
void MainWindow::deleteSensorLabelConfiguration(){
    sensorLabel[0]->setNum(0);
    sensorLabel[1]->setNum(0);
    sensorLabel[2]->setNum(0);
    sensorLabel[3]->setNum(0);
}

