#ifndef FRONTANIMATION_H
#define FRONTANIMATION_H
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <iostream>

/*!
 * \brief Klasa modelująca obsługę podświetlania pól przed samochodem.
 * Klasa modelująca obsługę pól przed samochodzem, odpowiednie włączanie
 * lub wyłączenie zależnie od odległości pochodzących z czujników
 * ultradźwiękowych
 */
class FrontAnimation{
public:
    QPixmap SetCurrentRange(int number, int numberTwo, int whichTable);
    QPixmap WhichRangeLOn(int senor[4]);
    QPixmap WhichRangePOn(int senor[4]);
    int CheckSecondSensor(int number);

};

#endif // FRONTANIMATION_HH
