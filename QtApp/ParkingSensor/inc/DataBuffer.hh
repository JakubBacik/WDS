#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <string>
#include <list>
#include <thread>
#include <mutex>


/*!
 *\brief Klasa definująca pojęcie bufforu.
 */
class DataBuffer {
   std::list<std::string>     _stringList;
   mutable std::mutex         _mutableMutex;
  
  public:

   void AddString(const std::string &constString);
   bool GetString(std::string &temporaryString);
   bool IsString() const;
};

#endif
