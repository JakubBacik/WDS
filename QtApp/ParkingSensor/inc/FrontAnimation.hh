#ifndef FRONTANIMATION_H
#define FRONTANIMATION_H
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <iostream>
class FrontAnimation{
public:
    QPixmap SetCurrentRange(int number, int numberTwo, int whichTable);
    QPixmap WhichRangeLOn(int _senor[4]);
    QPixmap WhichRangePOn(int _senor[4]);
    int CheckSecondSensor(int number);

};

#endif // FRONTANIMATION_HH
