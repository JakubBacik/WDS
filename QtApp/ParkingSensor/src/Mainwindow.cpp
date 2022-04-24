#include "../inc/Mainwindow.hh"
#include "ui_mainwindow.h"

/*!
 * \brief Konstruktor klasy MainWindow w ktorym ustawiane jest ui oraz konfigurowany timer
 * \param parent - klasa bazowa
 */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(_qTimer, SIGNAL(timeout()), this, SLOT(onStopertimeout()));
  _qTimer->setInterval(5000);
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
 * \brief Metoda wywolana gdy zostanie nacisniety przycisk
 * na pasku okna.
 */
void MainWindow::on_actionConfiguration_triggered()
{
    _connectionDialog = new ConnectionDialog(this);
    _connectionDialog->show();
    connect(_connectionDialog, SIGNAL(SendTo(QString)), this, SLOT(ConnectDevices(QString)));
}

/*!
 * \brief Metoda wywolana po nacisnieciu przycisku polacz w oknie dialogowym
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
 * \brief Metoda wywolana po nacisnieciu przycisku rozlacz w oknie dialogowym
 */
void MainWindow::DisconnectDevices(){
    communication->Stop();
    _isConnection=false;
}

/*!
 * \brief Metoda wywolywana podczas zamnkniecia okna
 * \param pEvent
 */
void MainWindow::closeEvent(QCloseEvent *pEvent){
    communication->Stop();
    pEvent->accept();

}

/*!
 * \brief Metoda wywolywana cyklicznie co okreslony czas za pomoca QTimer
 */
void MainWindow::onStopertimeout(){
    std::string string;
    if(_isConnection){
        while(communication->GetConstDataBuffer().IsString()){
            if(!communication->GetDataBuffer().GetString(string))continue;
               std::cout << string.c_str();
        }
        std::cout << std::endl;
    }
    _qTimer->start();
}

