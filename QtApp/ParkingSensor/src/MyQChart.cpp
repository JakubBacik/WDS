#include "inc/MyQChart.hh"

/*!
 * /brief Metoda tłumacząca
 * Metoda wywoływania przy tłumaczeniu, odpowiedzialna za tłumaczenie zakładki wykres
 */
void MyQChart::translateChart(){
    for(int i=0; i<4; i++){
        QString title = QObject::tr("Czujnik %1").arg(i+1);
        _chart[i]->setTitle(title);
        QString axisYTitleText = QObject::tr("Odległość [cm]");
        _axisY[i]->setTitleText(axisYTitleText);
        QString axisXTitleText = QObject::tr("Czas [ms]");
        _axisX[i]->setTitleText(axisXTitleText);
    }
}

/*!
 * \brief Inicjalizacja wykresów
 * Metoda inicjująca oraz konfigurująca cztery wykresy.
 */
void MyQChart::initChart(){
    for(int i=0; i<4; i++){
        _series[i] = new QLineSeries();
        _chart[i] = new QChart();
        QString title = QObject::tr("Czujnik %1").arg(i+1);
        _chart[i]->setTitle(title);
        _axisY[i] = new QValueAxis();
        _axisY[i]->setRange(0,500);
        _axisY[i]->setTickCount(5);
        QString axisYTitleText = QObject::tr("Odległość [cm]");
        _axisY[i]->setTitleText(axisYTitleText);
        _axisX[i] = new QValueAxis();
        _axisX[i]->setRange(-200,0);
        _axisX[i]->setTickCount(1);
        _axisX[i]->setLabelFormat("%g0");
        QString axisXTitleText = QObject::tr("Czas [ms]");
        _axisX[i]->setTitleText(axisXTitleText);
    }

    for(int i=0; i<4; i++){
        for(int j=-200; j<1; j++){
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
 * \brief Uaktualnianie danych
 * Metoda aktualizująca dane w czterech wykresach
 * \param[in] sensor - tablica zawierająca cztery wartości z czujników
 * \param[in] second - liczba sekund od momentu włączenia
 */
void MyQChart::updateData(int sensor[4], int second){
    for(int i=0; i<4; i++){
        _axisX[i]->setRange(second-200 ,second);
        _axisX[i]->setTickCount(1);
        _series[i]->remove(1);
        _series[i]->append(second, sensor[i]);
    }
    for(int i=0; i<4; i++){
      _chart[i]->update();
    }

}

/*!
 * \brief Destruktor
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
 * \brief Wyczyszczenie danych z wykresu
 * Metoda odpowiedzialna za wyczyszczenie danych aktualnie znajdujących się w  wykresie
 */
void MyQChart::clearChart(){
    int tab[4]={0,0,0,0};

    for(int j=-200; j<1; j++){
        updateData(tab, j);
    }
}





