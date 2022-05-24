#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <string>
#include <list>
#include <thread>
#include <mutex>

/*!
 * \brief Klasa modelująca pojęcie bufforu
 * Klasa modelująca pojęcie bufforu, składowane
 * są dane pochodzące z portu szeregowego.
 */
class DataBuffer {
    /*!
     * \brief Przechowuje dane
    * Lista stringów odpowiedzialna za przechowywanie informacji pochodzących z komunikacji
    */
   std::list<std::string>     _stringList;
   /*!
    * \brief Mutex
    * Mutex odpowiedzialny za kontrolne modyfikacji wartości
    */
   mutable std::mutex         _mutableMutex;
  
  public:
   void AddString(const std::string &constString);
   bool GetString(std::string &temporaryString);
   bool IsString() const;
};

#endif
