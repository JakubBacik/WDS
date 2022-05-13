#ifndef MYQCHART_H
#define MYQCHART_H
#include <QtCharts>
#include <QLineSeries>
#include <QValueAxis>

/*!
 * \brief The MyQChart class
 * Klasa definująca obsługe, inicjalizacje wykresów
 */
class MyQChart{
    QLineSeries* _series[4];
    QChart* _chart[4];
    QValueAxis* _axisX[4];
    QValueAxis* _axisY[4];
public:
    ~MyQChart();
    void initChart();
    void updateData(int sensor[4], int second);
    QChart* getChart(int number){return _chart[number];};
    void clearChart();
};

#endif // MYQCHART_HH
