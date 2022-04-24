#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <cassert>

#ifdef __GNUG__
  #pragma interface
  #pragma implementation
#endif



#include "inc/WatekOdbioru.hh"

using namespace std;



bool Communication::OpenPort(const char *serialPort)
{
  _qSerialPort->setPortName(serialPort);
  if(!_qSerialPort->isOpen()){
    _qSerialPort->setBaudRate(QSerialPort::Baud9600);
     _qSerialPort->setFlowControl(QSerialPort::NoFlowControl);
     _qSerialPort->setStopBits(QSerialPort::OneStop);
     _qSerialPort->setDataBits(QSerialPort::Data8);
    _qSerialPort->setParity(QSerialPort::NoParity);
    if (!_qSerialPort->open(QSerialPort::ReadOnly)) {
        qDebug() << "Port opening error" << serialPort << endl;
        return false;
    }
  }else{
      qDebug() << "Port has been already open" << serialPort << endl;
  }


  return true;
}



bool Communication::GetOneLine()
{
#define  LINE_SIZE 10
  char line[LINE_SIZE+1];
  qint64  amountOfReveiceData;

  amountOfReveiceData = _qSerialPort->readLine(line, LINE_SIZE); // Czeka az bedzie pelna linia.
  if (amountOfReveiceData== 0 && !_qSerialPort->waitForReadyRead()) return false;
  
  if (amountOfReveiceData > 0) {
    if (line[strlen(line)-1] == '\n') {
       line[strlen(line)-1] = 0;
    }

    _dataBuffer.AddString(line);
  }
  return true;
}




void Communication::ReceiveData()
{
  while (Continue()) {
    if (!GetOneLine()) return;
  }

}

bool Communication::ClosePort(){
    if(_qSerialPort->isOpen()){
        _qSerialPort->close();
        return true;
    }else{
        return false;
    }
}



void MyQThread::run()
{
  QSerialPort   qSerialPort;

  _communication->SetQSerialPort(&qSerialPort);
  if (!_communication->OpenPort()) {
     cerr << ":( Operacja otwarcia portu nie powiodla sie." << endl;
     cerr << ":( Watek odbioru zakonczony." << endl;
     return;
  }

  qDebug() << "Start watku" << endl;
  _communication->ReceiveData();
  qSerialPort.close();
  qDebug() << "Koniec watku" << endl;
}




