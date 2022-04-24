#include "../inc/mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(_qTimer, SIGNAL(timeout()), this, SLOT(onStopertimeout()));
  _qTimer->setInterval(5000);
  _qTimer->setSingleShot(true);
  _qTimer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConfiguration_triggered()
{
    connectionWithArduino = new ConnectionWithArduino(this);
    connectionWithArduino->show();
    connect(connectionWithArduino, SIGNAL(SendTo(QString)), this, SLOT(ChangeCurrentPort(QString)));
}


void MainWindow::ChangeCurrentPort(QString portName){
    communication->Start();
    communication->SetPortName(portName.toStdString());
    myQThread = new MyQThread(communication);
    myQThread->start();
    _isConnection=true;

}
void MainWindow::DisconnectDevices(){
    communication->Stop();
    _isConnection=false;
}

void MainWindow::closeEvent(QCloseEvent *pEvent){
    communication->Stop();
    pEvent->accept();

}

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

