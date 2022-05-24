#ifndef MYQCHART_H
#define MYQCHART_H
#include <QtCharts>
#include <QLineSeries>
#include <QValueAxis>
#include <QTranslator>
#include <QString>
#include <QObject>


/*!
 * \brief Klasa modelująca obsługe, inicjalizacje wykresów
 * Klasa modelująca wykresy w zakładce wykresy okna głównego.
 * Posiada atrybuty niezbędne do skofigurowania wykresów.
 */
class MyQChart{
    /*!
     * \brief Przechowywanie danych
     * Tablica wskaźników na obiekt klasy QLineSeries, przechowująca dane które wypełnią wykres
     */
    QLineSeries* _series[4];
    /*!
     * \brief Wykresy
     * Tablica wskaźników na obiekt klasy QChart, definująca cztery wykresy w zakładce plot
     */
    QChart* _chart[4];
    /*!
     * \brief Oś pozioma
     * Tablica wskaźników na obiekt QValueAxis, która definuje oś poziomą
     */
    QValueAxis* _axisX[4];
    /*!
     * \brief Oś pionowa
     * Tablica obiektów QValueAxis, która definuje oś pionową
     */
    QValueAxis* _axisY[4];

public:
    ~MyQChart();
    void initChart();
    void updateData(int sensor[4], int second);
    /*!
     * \brief Pobranie wykresu
     * Pobieranie wskaźnika na obiekt klasy Qchart w tablicy
     * \param number - indeks w tabeli który chcemy pobrać element
     * \return zwraca obiekt klasy QChart będący pod odpowiednim indeksem
     */
    QChart* getChart(int number){return _chart[number];};
    void clearChart();
    void translateChart();
};

#endif // MYQCHART_HH
