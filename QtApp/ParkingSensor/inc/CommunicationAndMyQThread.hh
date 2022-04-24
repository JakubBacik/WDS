#ifndef COMMUNICATIONANDMYQTHREAD_H
#define COMMUNICATIONANDMYQTHREAD_H

#ifdef __GNUG__
  #pragma interface
  #pragma implementation
#endif

#include <QThread>
#include <QSerialPort>
#include "DataBuffer.hh"
#include <QDebug>


/*!
 *\brief Klasa definujaca polaczenie z urzadzeniem zewnetrznym
 *
 */

class Communication {
     QSerialPort  *_qSerialPort = new QSerialPort();
     DataBuffer   _dataBuffer;
     bool          _continue = true;
     std::string   _portName;
  
   public:

     void SetPortName(const std::string &portName) { _portName = portName; }
     void SetQSerialPort(QSerialPort  *qSerialPort) { _qSerialPort = qSerialPort; }

     bool OpenPort(const char* serialPort);
     bool OpenPort() { return OpenPort(_portName.c_str()); }
     bool ClosePort();
  
     DataBuffer &GetDataBuffer() { return _dataBuffer; }
     const DataBuffer &GetConstDataBuffer() const { return _dataBuffer; }
     bool Continue() const { return _continue; }
     void Stop() { _continue = false; }
     void Start() {_continue = true;}
  
     bool GetOneLine();
     void ReceiveData();
};



/*!
 * \brief Klasa definujaca wykorzystany watek, dziedziczy z klasy QThread
 */
class MyQThread: public QThread {
   Q_OBJECT
   Communication  *_communication = nullptr;

  public:
   MyQThread(Communication *communication) { _communication= communication; }
   void run() override; 
};





#endif
