#include "inc/DataBuffer.hh"

using namespace std;

#define  MAX_SIZE_OF_LIST  10

/*!
 * \brief Dodawanie stringa
 * Metoda umożliwiająca dodawanie elementów do buffora oraz
 * kontrolująca wielkość buforu do wielkości MAX_SIZE_OF_LIST
 * \param[in] constString - string który zostanie dodany
 */
void DataBuffer::AddString(const std::string &constString)
{
  std::lock_guard<std::mutex>  guard(_mutableMutex);

  _stringList.push_back(constString);
  while (_stringList.size() > MAX_SIZE_OF_LIST) {
    _stringList.pop_front();
  }
}


/*!
 * \brief Pobranie stringa
 * Metoda umożliwiająca pobranie elementu z frontu
 * buffora
 * \param[in] temporaryString - zwrócenie stringa z bufforu
 */
bool DataBuffer::GetString(std::string &temporaryString)
{
  std::lock_guard<std::mutex>  guard(_mutableMutex);

  if (_stringList.empty()) return false;
  temporaryString = _stringList.front();
  _stringList.pop_front();
  return true;
}

/*!
 * \brief Jest string
 * Metoda umożliwiająca sprawdzenie czy występują
 * elementy w bufforze
 */
bool DataBuffer::IsString() const
{
  std::lock_guard<std::mutex>  Guard(_mutableMutex);
  return !_stringList.empty();
}
