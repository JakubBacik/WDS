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

#include "inc/CommunicationAndMyQThread.hh"

using namespace std;

/*!
 * \brief Metoda odpowiedzialna za otwarcie portu
 * \param[in] serialPort - nazwa portu, ktory ma zostac otwarty
 * \retval true - jesli zostanie otwarte polaczenie
 * \retval false - w przypdaku przeciwnym
 */
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
        cerr << "Port opening error" << serialPort << endl;
        return false;
    }
  }else{
      cerr << "Port has been already open" << serialPort << endl;
  }


  return true;
}

/*!
 * \brief Metoda odpowiedzialna za pobranie jednej linii danych
 * z wybranego portu/
 * \retval false - jesli nie ma dostepnych danych
 * \retval true - w przeciwnym przypadku
 */
bool Communication::GetOneLine()
{
#define  LINE_SIZE 50
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


/*!
 * \brief Metoda odpowiadajaca za pobieranie danych gdy zostala
 * ustawiona flaga oraz sa dostepne dane
 */
void Communication::ReceiveData()
{
  while (Continue()) {
    if (!GetOneLine()) return;
  }

}

/*!
 * \brief Metoda odpowiedzialna za zamkniecie portu
 * \retval false - jesli port nie zostal otwarty
 * \retval true - jesli port zostal zamkniety
 */
bool Communication::ClosePort(){
    if(_qSerialPort->isOpen()){
        _qSerialPort->close();
        return true;
    }else{
        return false;
    }
}

/*!
 * \brief Metoda nadpisana z klasy Qthread, ustawiajaca port oraz
 * sprawdzajaca czy port jest otwarty, nastepnie wywolujaca funkcje
 * ReceiceData jesli dane zostaly odczytane, port zostanie zamkniety.
 */
void MyQThread::run()
{
  QSerialPort   qSerialPort;

  _communication->SetQSerialPort(&qSerialPort);
  if (!_communication->OpenPort()) {
     cerr << ":OpenPort error" << endl;
     return;
  }

  cerr<< "Create a threat" << endl;
  _communication->ReceiveData();
  qSerialPort.close();
  cerr << "Destroy threat" << endl;
}




