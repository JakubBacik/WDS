#ifndef BUFORDANYCH_HH
#define BUFORDANYCH_HH

#include <string>
#include <list>
#include <thread>
#include <mutex>


/*!
 *\brief Klasa definujaca pojecie bufforu.
 * Atrybuty klasy to:
 * strinfList - lista elementow
 * mutableMutex - mutex
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
