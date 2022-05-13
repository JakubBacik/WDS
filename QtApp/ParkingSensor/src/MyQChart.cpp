#include "inc/MyQChart.hh"

/*!
 * \brief MyQChart::initChart
 * Metoda inicjująca cztery wykresy.
 */
void MyQChart::initChart(){
    for(int i=0; i<4; i++){
        _series[i] = new QLineSeries();
        _chart[i] = new QChart();
        _chart[i]->setTitle("Sensor " + QString::number(i+1));
        _axisY[i] = new QValueAxis();
        _axisY[i]->setRange(0,500);
        _axisY[i]->setTickCount(5);
        _axisY[i]->setTitleText("Length [cm]");
        _axisX[i] = new QValueAxis();
        _axisX[i]->setRange(-4,0);
        _axisX[i]->setRange(-20,0);
        _axisX[i]->setTickCount(1);
        _axisX[i]->setTitleText("Time [s]");
    }

    for(int i=0; i<4; i++){
        for(int j=-20; j<1; j++){
            _series[i]->append(j,0);
        }
    }

    for(int i=0; i<4; i++){
        _chart[i]->legend()->hide();
        _chart[i]->addSeries(_series[i]);
        _chart[i]->setAxisX(_axisX[i], _series[i]);
        _chart[i]->setAxisY(_axisY[i], _series[i]);
    }
}

/*!
 * \brief MyQChart::updateData
 * Metoda aktualizująca dane w czterech wykresach
 * \param sensor - tablica zawierająca cztery wartości z czujników
 * \param second - liczba sekund od momentu włączenia
 */
void MyQChart::updateData(int sensor[4], int second){
    for(int i=0; i<4; i++){
        _axisX[i]->setRange(second-20 ,second);
        _axisX[i]->setTickCount(1);
        _series[i]->remove(4);
        _series[i]->append(second, sensor[i]);
    }
    for(int i=0; i<4; i++){
      _chart[i]->update();
    }

}

/*!
 * \brief MyQChart::~MyQChart
 * Deskruktor klasy
 */
MyQChart::~MyQChart(){
    for(int i=0; i<4; i++){
        delete _series[i];
        delete _chart[i];
        delete _axisY[i];
        delete _axisX[i];
    }
}

/*!
 * \brief MyQChart::clearChart
 * Metoda odpowiedzialna za wyczyszczenie danych w wykresie
 */
void MyQChart::clearChart(){
    int tab[4]={0,0,0,0};

    for(int j=-20; j<1; j++){
        updateData(tab, j);
    }
}


