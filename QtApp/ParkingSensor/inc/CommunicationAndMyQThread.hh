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
 * \brief Modeluje pojęcie Communication
 * Klasa modelująca połaczenie z urządzeniem zewnętrznym.
 * Posiada atrybuty przechowujące nazwe portu, flage odpowiedzialna
 * za kontynowanie komunikacji, buffor danych oraz port.
 */
class Communication {
    /*!
     * \brief Port
      * Wskaźnik na obiekt klasy QSerialPort
      */
     QSerialPort  *_qSerialPort = new QSerialPort();
     /*!
      * \brief Buffor
      * Obiekt klasy DataBuffer, który definuje pojęcie bufforu
      */
     DataBuffer    _dataBuffer;
     /*!
      * \brief Trwanie komunikacji
      * Zmienna odpowiadająca za kontynuowanie komunikacji lub zaniechanie jej
      */
     bool          _continue = true;
     /*!
      * \brief Nazwa portu
      * Nazwa przechowująca nazwe portu, który chcemy otworzy np. "ttyACM0"
      */
     std::string   _portName;
  
   public:
     /*!
      * \brief Ustawia nazwe portu
      * Metoda ustawiająca wartość zmiennej _portName czyli nazwe portu, który
      * ma zostać otwarty.
      * \param[in] portName - nazwa portu który chcemy otworzyć np. "ttyACM0"
      */
     void SetPortName(const std::string &portName) { _portName = portName; }

     /*!
      * \brief Ustawienie portu
      * Metoda ustawiająca wartość obiektu klasy QSerialPort
      * \param[in] qSerialPort - wartość na którą ma być ustawiony atrybut _qSerialPort klasy.
      */
     void SetQSerialPort(QSerialPort  *qSerialPort) { _qSerialPort = qSerialPort; }
     bool OpenPort(const char* serialPort);
     bool OpenPort() { return OpenPort(_portName.c_str()); }
     bool ClosePort();
  
     /*!
      * \brief Pobranie obiektu klasy dataBuffor
      * Metoda zwaracająca obiekt klasy dataBuffor, który modeluje buffor
      * \return obiet klasy DataBuffer
      */
     DataBuffer &GetDataBuffer() { return _dataBuffer; }

     /*!
      * \brief Pobranie obiektu klady dataBuffor, metoda stała
      * Metoda stała zwracająca obiekt klasy DataBuffer, który modeluje bufor
      * \return obiet klasy DataBuffer
      */
     const DataBuffer &GetConstDataBuffer() const { return _dataBuffer; }

     /*!
      * \brief Zwraca wartość zmiennej _continue
      * Metoda zwracajacy aktualną wartość zmiennej _conitnue
      * \return wartość zmiennej _continue
      */
     bool Continue() const { return _continue; }
     /*!
      * \brief Ustawia wartość false
      * Metoda zmieniająca wartość zmiennej _continue na wartość false,
      * zaprzestanie transmisji.
      */
     void Stop() { _continue = false; }
     /*!
      * \brief Ustawia wartość true
      * Metoda zmieniająca wartość zmiennej _continue na wartość true,
      * zaniechanie transmisji.
      */
     void Start() {_continue = true;}
     bool GetOneLine();
     void ReceiveData();
};


/*!
 * \brief Modeluje pojęcie MyQThread
 * Klasa modelująca wątek odpowiedzialny za komunikacje,
 * dziedziczy z klasy QThread. Posiada atrybut Communication
 */
class MyQThread: public QThread {
   Q_OBJECT
    /*!
     * \brief Komunikacja
     * Wskaźnik na obiekt klasy Communication
     */
   Communication  *_communication = nullptr;

  public:
   /*!
    * \brief Konstruktor
    * Konstruktor, ustawiający wartość obiekt klasy Comunication, odpowiedzialny za połączenie z urządzeniem zewnętrznym.
    */
   MyQThread(Communication *communication) { _communication= communication; }
   void run() override; 
};





#endif
