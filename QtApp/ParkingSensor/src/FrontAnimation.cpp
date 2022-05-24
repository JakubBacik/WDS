#include "inc/FrontAnimation.hh"

/*!
 * \brief Ustawienie odpowiedniej bitmapy
 * Metoda odpowiedzialna za zwrócenie odpowiedniej bitmapy poprzez odpowiednią konfiguracje argumentów
 * \param[in] number - numer wiersza w tabeli
 * \param[in] numberTwo - numer kolumny w tabeli
 * \param[in] whichTable - która tabela
 * \return zwrócenie odpowiedniej bitmapy
 */
QPixmap FrontAnimation::SetCurrentRange(int number, int numberTwo, int whichTable){
    const char* DefaultSetUp[3] ={":/View/img/car/caricon.png", ":/View/img/sensorView/SensorViewDefaultL1.png", ":/View/img/sensorView/SensorViewDefaultP1.png"};

    const char* SetUpRangeLeft[6][6]= {
                                   {":/View/img/sensorView/SensorViewDefaultL2.png",":/View/img/sensorView/SensorViewDefaultL3.png", ":/View/img/sensorView/SensorViewDefaultL4.png",":/View/img/sensorView/SensorViewDefaultL5.png",
                                    ":/View/img/sensorView/SensorViewDefaultL6.png",":/View/img/sensorView/SensorViewDefaultL7.png"},
                                   { ":/View/img/sensorView/SensorViewDefaultL8.png",":/View/img/sensorView/SensorViewDefaultL9.png",":/View/img/sensorView/SensorViewDefaultL10.png",":/View/img/sensorView/SensorViewDefaultL11.png",
                                     ":/View/img/sensorView/SensorViewDefaultL12.png",":/View/img/sensorView/SensorViewDefaultL13.png"},
                                   {":/View/img/sensorView/SensorViewDefaultL14.png",":/View/img/sensorView/SensorViewDefaultL15.png", ":/View/img/sensorView/SensorViewDefaultL16.png",":/View/img/sensorView/SensorViewDefaultL17.png",
                                    ":/View/img/sensorView/SensorViewDefaultL18.png",":/View/img/sensorView/SensorViewDefaultL19.png"},
                                   {":/View/img/sensorView/SensorViewDefaultL20.png",":/View/img/sensorView/SensorViewDefaultL21.png",":/View/img/sensorView/SensorViewDefaultL22.png", ":/View/img/sensorView/SensorViewDefaultL23.png",
                                    ":/View/img/sensorView/SensorViewDefaultL24.png",":/View/img/sensorView/SensorViewDefaultL25.png"},
                                   {":/View/img/sensorView/SensorViewDefaultL26.png", ":/View/img/sensorView/SensorViewDefaultL27.png",":/View/img/sensorView/SensorViewDefaultL28.png",":/View/img/sensorView/SensorViewDefaultL29.png",""
                                    ":/View/img/sensorView/SensorViewDefaultL30.png",":/View/img/sensorView/SensorViewDefaultL31.png"},
                                   {":/View/img/sensorView/SensorViewDefaultL31.png", ":/View/img/sensorView/SensorViewDefaultL32.png", ":/View/img/sensorView/SensorViewDefaultL33.png", ":/View/img/sensorView/SensorViewDefaultL34.png",
                                    ":/View/img/sensorView/SensorViewDefaultL35.png", ":/View/img/sensorView/SensorViewDefaultL36.png"}
                                  };
    const char* SetUpRangeRight[6][6]= {
                                   {":/View/img/sensorView/SensorViewDefaultP2.png", ":/View/img/sensorView/SensorViewDefaultP3.png", ":/View/img/sensorView/SensorViewDefaultP4.png",":/View/img/sensorView/SensorViewDefaultP5.png",
                                    ":/View/img/sensorView/SensorViewDefaultP6.png",":/View/img/sensorView/SensorViewDefaultP7.png"},
                                   {":/View/img/sensorView/SensorViewDefaultP8.png", ":/View/img/sensorView/SensorViewDefaultP9.png",":/View/img/sensorView/SensorViewDefaultP10.png",":/View/img/sensorView/SensorViewDefaultP11.png",
                                     ":/View/img/sensorView/SensorViewDefaultP12.png",":/View/img/sensorView/SensorViewDefaultP13.png"},
                                   {":/View/img/sensorView/SensorViewDefaultP14.png", ":/View/img/sensorView/SensorViewDefaultP15.png", ":/View/img/sensorView/SensorViewDefaultP16.png",":/View/img/sensorView/SensorViewDefaultP17.png",
                                    ":/View/img/sensorView/SensorViewDefaultP18.png",":/View/img/sensorView/SensorViewDefaultP19.png"},
                                   {":/View/img/sensorView/SensorViewDefaultP20.png", ":/View/img/sensorView/SensorViewDefaultP21.png",":/View/img/sensorView/SensorViewDefaultP22.png",":/View/img/sensorView/SensorViewDefaultP23.png",
                                    ":/View/img/sensorView/SensorViewDefaultP24.png",":/View/img/sensorView/SensorViewDefaultP25.png"},
                                   {":/View/img/sensorView/SensorViewDefaultP26.png", ":/View/img/sensorView/SensorViewDefaultP27.png",":/View/img/sensorView/SensorViewDefaultP28.png",":/View/img/sensorView/SensorViewDefaultP29.png",""
                                    ":/View/img/sensorView/SensorViewDefaultP30.png", ":/View/img/sensorView/SensorViewDefaultP31.png"},
                                   {":/View/img/sensorView/SensorViewDefaultP31.png", ":/View/img/sensorView/SensorViewDefaultP32.png",":/View/img/sensorView/SensorViewDefaultP33.png",":/View/img/sensorView/SensorViewDefaultP34.png",""
                                    ":/View/img/sensorView/SensorViewDefaultP35.png", ":/View/img/sensorView/SensorViewDefaultP36.png"},
                                  };

   if(whichTable == 1){
       return QPixmap(QString::fromUtf8(DefaultSetUp[number]));
   }
   if(whichTable == 2){
        return QPixmap(QString::fromUtf8(SetUpRangeLeft[number][numberTwo]));
   }
   if(whichTable == 3){
        return QPixmap(QString::fromUtf8(SetUpRangeRight[number][numberTwo]));
   }

}

/*!
 * \brief Sprawdzenie zakresu dla czujnika z lewej strony
 * Funkcja odowiedzialna za odpowiednią konfiguracje metody SetCurrentRange w zależności od odległości od czujnika numer 0.
 * W efekcie tego ulegnie zapalenie odpowiedniego pola.
 * \param[in] _sensor - tablica zawierająca dane z czujników
 * \return zwrócenie odpowiedniej mapy w zależności od czujnika 1
 */
QPixmap FrontAnimation::WhichRangeLOn(int _sensor[4]){
    int number = CheckSecondSensor(_sensor[1]);
    if(_sensor[0] <= 50 && _sensor[0] > 40){
        return SetCurrentRange(0,number,2);
    }
    else if(_sensor[0] <= 40 && _sensor[0] > 30){
        return SetCurrentRange(1,number,2);
    }
    else if(_sensor[0] <= 30 && _sensor[0] > 20){
        return SetCurrentRange(2,number,2);
    }
    else if(_sensor[0] <= 20 && _sensor[0] > 10){
        return SetCurrentRange(3,number,2);
    }
    else if(_sensor[0] <= 10 && _sensor[0] >= 0){
        return SetCurrentRange(4,number,2);
    }
    else if(_sensor[0] > 50 && _sensor[1] <=50){
        return SetCurrentRange(5, number, 2);

    }
    return SetCurrentRange(1, 0, 1);

}

/*!
 * \brief Sprawdzenie zakresu dla czujnika z prawej strony
 * Funkcja odowiedzialna za odpowiednią konfiguracje metody SetCurrentRange w zależności od odległości od czujnika numer 4.
 * W efekcie tego ulegnie zapalenie odpowiedniego pola.
 * \param[in] _sensor - tablica zawierająca dane z czujników
 * \return zwrócenie odpowiedniej mapy w zależności od czujnika 4
 */
QPixmap FrontAnimation::WhichRangePOn(int _sensor[4]){
    int number = CheckSecondSensor(_sensor[2]);
    if(_sensor[3] <= 50 && _sensor[3] > 40){
        return SetCurrentRange(0,number,3);
    }
    else if(_sensor[3] <= 40 && _sensor[3] > 30){
        return SetCurrentRange(1,number,3);
    }
    else if(_sensor[3] <= 30 && _sensor[3] > 20){
        return SetCurrentRange(2,number,3);
    }
    else if(_sensor[3] <= 20 && _sensor[3] > 10){
        return SetCurrentRange(3,number,3);
    }
    else if(_sensor[3] <= 10 && _sensor[3] >= 0){
        return SetCurrentRange(4,number,3);
    }else if(_sensor[3] > 50 && _sensor[2] <=50){
        return SetCurrentRange(5, number, 3);
    }
    return SetCurrentRange(2, 0, 1);
}


/*!
 * \brief Sprawdzenie zakresu dla dwóch czujników na środku
 * Funkcja odowiedzialna za odpowiednią konfiguracje metody SetCurrentRange w zależności od odległości od czujnika numer 2 lub 3.
 * \param[in] number - liczba odpowiadająca odległości jednego czujnika
 * \return zwrócenie odpowiedniej wartości w zależności od czujnika 2 lub 3
 */
int FrontAnimation::CheckSecondSensor(int number){
    if(number <= 50 && number > 40){
        return 1;
    }
    else if(number <= 40 && number > 30){
        return 2;
    }
    else if(number <= 30 && number > 20){
        return 3;
    }
    else if(number <= 20 && number > 10){
        return 4;
    }
    else if(number <= 10 && number >= 0){
        return 5;
    }

    return 0;

}

