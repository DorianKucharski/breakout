#include "gra.h"
#include "pilka.h"
#include "paletka.h"
#include "blok.h"
#include <QDebug>


QVector <Pilka*> pilki;

Gra::Gra(QWidget *parent): QGraphicsView(parent){

    rozdzielczoscx = 800;
    rozdzielczoscy = 600;
    this->setGeometry(0,0,rozdzielczoscx-50,rozdzielczoscy-100);
    scene = new QGraphicsScene(0,0,rozdzielczoscx-50, rozdzielczoscy-100);
    setScene(scene);
    setMouseTracking(true);
    poziom_trudnosci = 1;
}

void Gra::start(){
    pilki.clear();
    wynik = 0;
    ilosc_zyc = 3;

    Pilka* pilka = new Pilka();
    pilka->id = 0;
    pilka->setPos(this->width()/2,this->height()-100);
    pilki << pilka;
    scene->addItem(pilki.at(pilka->id));

    paletka = new Paletka();
    paletka->setPos(this->width()/2,this->height()-50);
    scene->addItem(paletka);
    paletka->grabMouse();

    losuj_plansze();

}

void Gra::przegrana(int id){
    pilki.at(id)->zniszcz();
    pilki.at(0)->kolejna_pilka();
    ilosc_zyc--;
    if (ilosc_zyc <=0)  {
        for (int i = 0; i < pilki.length(); ++i)
            pilki[i]->zniszcz();
            delete paletka;
    }
}

void Gra::wygrana(){
    for (int i = 0; i < pilki.length(); ++i)
        pilki[i]->setPos(this->width()/2,this->height()-100);
    bloki_na_planszy = zniszczone_bloki = 0;
    losuj_plansze();
}

void Gra::losuj_plansze(){
    qsrand(time(NULL));
    int i = (qrand() % 5)+1;
    if (i == 1) plansza1();
    if (i == 2) plansza2();
    if (i == 3) plansza3();
    if (i == 4) plansza4();
    if (i == 5) plansza_losowa();
}

void Gra::plansza1(){
    for (size_t i = 0; i < 12; ++i){
        for (size_t j = 0; j < 10; ++j){
            Blok* blok = new Blok();
            blok->setPos(i*63,j*30);
            scene->addItem(blok);
            bloki_na_planszy++;
         }
    }
}

void Gra::plansza2(){
    for (size_t i = 0; i < 12; ++i){
        for (size_t j = 0; j < 10; ++j){
            if (((i+j) % 2) == 0){
                Blok* blok = new Blok();
                blok->setPos(i*63,j*30);
                scene->addItem(blok);
                bloki_na_planszy++;
                }
        }
    }
}

void Gra::plansza3(){
    for (size_t i = 0; i < 12; ++i){
        for (size_t j = 0; j < 8; j+=2){

                Blok* blok = new Blok();
                blok->setPos(i*63,j*30);
                scene->addItem(blok);
                bloki_na_planszy++;
        }
    }
}

void Gra::plansza4(){
    for (size_t i = 0; i < 12; i+=2){
        for (size_t j = 0; j < 8; ++j){

                Blok* blok = new Blok();
                blok->setPos(i*63,j*30);
                scene->addItem(blok);
                bloki_na_planszy++;
        }
    }
}

void Gra::plansza_losowa(){
    for (size_t i = 0; i < 12; ++i){
        for (size_t j = 0; j < 10; ++j){
            qsrand(qrand());
            if ((qrand() % 2) == 1 )
            {
                Blok* blok = new Blok();
                blok->setPos(i*63,j*30);
                scene->addItem(blok);
                bloki_na_planszy++;
            }
         }
    }
}

