#ifndef GRA_H
#define GRA_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QObject>
#include "paletka.h"

class Gra: public QGraphicsView{

public:
    Gra(QWidget* parent=nullptr);

    void start();
    void przegrana(int id);
    void wygrana();
    void losuj_plansze();
    void plansza1();
    void plansza2();
    void plansza3();
    void plansza4();
    void plansza_losowa();
    double poziom_trudnosci;

    QGraphicsScene* scene;
    Paletka *paletka;

    int wynik;
    int ilosc_zyc;
    int bloki_na_planszy;
    int zniszczone_bloki;
    int rozdzielczoscx;
    int rozdzielczoscy;

};

#endif // GRA_H
