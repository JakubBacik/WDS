#ifndef MYQCHART_H
#define MYQCHART_H
#include <QtCharts>
#include <QLineSeries>
#include <QValueAxis>

class MyQChart{
    QLineSeries *series[4];
    QChart *chart[4];
    QValueAxis *axisX[4];
    QValueAxis *axisY[4];
public:
    ~MyQChart();
    void initChart();
    void updateData(int sensor[4], int second);
    QChart* getChart(int number){return chart[number];};

};

#endif // MYQCHART_HH
