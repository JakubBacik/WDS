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
 * \brief Otwarcie portu
 * Metoda odpowiedzialna za otwarcie portu
 * \param[in] serialPort - nazwa portu, ktory ma zostać otwarty np. tty
 * \retval true - jeśli zostanie otwarte połączenie
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
 * \brief Pobranie jednej linii
 * Metoda odpowiedzialna za pobranie jednej linii danych
 * z wybranego portu
 * \retval false - jeśli nie ma dostępnych danych
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
 * \brief Otrzymane dane
 * Metoda odpowiadajaca za pobieranie danych gdy została
 * ustawiona flaga oraz są dostępne dane
 */
void Communication::ReceiveData()
{
  while (Continue()) {
    if (!GetOneLine()) return;
  }

}

/*!
 * \brief Zamykanie portu
 * Metoda odpowiedzialna za zamknięcie portu
 * \retval false - jeśli port nie został otwarty
 * \retval true - jeśli port został zamknięty
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
 * \brief Uruchomienie portu
 * Metoda przeciążona z klasy Qthread, ustawiająca port oraz
 * sprawdzająca czy port jest otwarty, następnie wywołujaca funkcje
 * ReceiceData jeśli dane zostały odczytane, port zostanie zamknięty.
 */
void MyQThread::run()
{
  QSerialPort   qSerialPort;

  _communication->SetQSerialPort(&qSerialPort);
  if (!_communication->OpenPort()) {
     return;
  }
  _communication->ReceiveData();
  qSerialPort.close();
}




