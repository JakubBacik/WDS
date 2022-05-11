#ifndef CIRCLEANIMATION_H
#define CIRCLEANIMATION_H
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <iostream>


class CircleAnimation : public QLabel{
    Q_OBJECT
public:
    CircleAnimation();
public:
    enum StateOfArea{
        SOA_TurnedOn,
        SOA_TurnedOff
    };

private:
    StateOfArea _State;
public:
    void SetTurnOffColor(int numberOfArea);
    //void SetTurnOnArea(){_State = SOA_TurnedOff;}
    //void SetTurnOffArea(){_State = SOA_TurnedOn;}
};



#endif // CIRCLEANIMATION_HH
