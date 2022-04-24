#include "inc/BuforDanych.hh"

using namespace std;


#define  MAX_SIZE_OF_LIST  10

/*!
 *\brief
 * Funkcja umozliwiajaca dodawanie elementow do buffora oraz
 * kontrolujaca wielkosc bufory do wielkosci MAX_SIZE_OF_LIST
 */
void DataBuffer::AddString(const std::string &constString)
{
  std::lock_guard<std::mutex>  guard(mutableMutex);

  stringList.push_back(constString);
  while (stringList.size() > MAX_SIZE_OF_LIST) {
    stringList.pop_front();
  }
}


/*!
 *\brief
 * Funkcja umozliwiajaca pobierania elementu z frontu
 * buffora
 */
bool DataBuffer::GetString(std::string &temporaryString)
{
  std::lock_guard<std::mutex>  guard(mutableMutex);

  if (stringList.empty()) return false;
  temporaryString = stringList.front();
  stringList.pop_front();
  return true;
}

/*!
 *\brief
 * Funkcja umozliwiajaca sprawdzenie czy wystepuja
 * elementy w bufforze
 */
bool DataBuffer::IsString() const
{
  std::lock_guard<std::mutex>  Guard(mutableMutex);
  return !stringList.empty();
}
