#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <string>
#include <list>
#include <thread>
#include <mutex>


/*!
 *\brief Klasa definujaca pojecie bufforu.
 */
class DataBuffer {
   std::list<std::string>     stringList;
   mutable std::mutex         mutableMutex;
  
  public:

   void AddString(const std::string &constString);
   bool GetString(std::string &temporaryString);
   bool IsString() const;
};

#endif
