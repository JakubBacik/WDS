#include "inc/MyQChart.hh"

void MyQChart::initChart(){
    for(int i=0; i<4; i++){
        series[i] = new QLineSeries();
        chart[i] = new QChart();
        axisY[i] = new QValueAxis();
        axisY[i]->setRange(0,500);
        axisY[i]->setTickCount(5);
        axisX[i] = new QValueAxis();
        axisX[i]->setRange(-4,0);
        axisX[i]->setTickCount(1);

    }

    for(int i=0; i<4; i++){
        for(int j=-4; j<1; j++){
            series[i]->append(j,0);
        }
    }

    for(int i=0; i<4; i++){
        chart[i]->legend()->hide();
        chart[i]->addSeries(series[i]);
        chart[i]->setAxisX(axisX[i], series[i]);
        chart[i]->setAxisY(axisY[i], series[i]);
    }
}


void MyQChart::updateData(int sensor[4], int second){
    for(int i=0; i<4; i++){
        axisX[i]->setRange(second-4 ,second);
        axisX[i]->setTickCount(1);
        series[i]->remove(4);
        series[i]->append(second, sensor[i]);
    }
    for(int i=0; i<4; i++){
      chart[i]->update();
    }

}

MyQChart::~MyQChart(){
    for(int i=0; i<4; i++){
        delete series[i];
        delete chart[i];
        delete axisY[i];
        delete axisX[i];
    }
}


