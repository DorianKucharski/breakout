#include "pilka.h"
#include "gra.h"
#include "paletka.h"
#include "blok.h"
#include <QTimer>
#include <QBrush>
#include <QDebug>

extern Gra* gra;
extern QVector <Pilka*> pilki;
Pilka::Pilka(QGraphicsItem *parent): QGraphicsEllipseItem(parent){

    setRect(0,0,20,20);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    xPredkosc = 0;
    yPredkosc = -5 * gra->poziom_trudnosci;

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(fizyka()));
    timer->start(15);

}

void Pilka::kolejna_pilka(){
    Pilka* pilka = new Pilka();
    pilka->id = pilki.length();
    pilka->setPos(gra->width()/2,gra->height()-100);
    pilki << pilka;
    gra->scene->addItem(pilki.at(pilka->id));
}

void Pilka::zniszcz(){
    gra->scene->removeItem(this);

    xPredkosc = 0;
    yPredkosc = 0;
    moveBy(-10,-10);

}
double Pilka::srodek_x(){
    return x() + rect().width()/2;
}

void Pilka::fizyka(){
    odbijanie_od_scian();
    kolizja_z_paletka();
    kolizja_z_blokami();
    moveBy(xPredkosc,yPredkosc);


}

void Pilka::odbijanie_od_scian()
{
    if (this->x()  <= 0)    xPredkosc = -1 * xPredkosc;
    if (this->x() + 20 >= gra->width())     xPredkosc = -1 * xPredkosc;
    if (this->y() <= 0)     yPredkosc = -1 * yPredkosc;
    if (this->y() +20 >= gra->height())    gra->przegrana(id);
}

void Pilka::kolizja_z_paletka(){

    QList<QGraphicsItem*> kolizje = collidingItems();
    for (int i = 0, n = kolizje.size(); i < n; ++i){
        Paletka* paletka = dynamic_cast<Paletka*>(kolizje[i]);
        if (paletka){
            double pilka_x = srodek_x();
            double paletka_x = paletka->srodek_x();

            if (pilka_x + 10 < paletka_x - 50 + 5) yPredkosc = -1 * yPredkosc;
            if (pilka_x - 10 > paletka_x + 50 - 5) yPredkosc = -1 * yPredkosc;

            double roznica_x = pilka_x - paletka_x;
            xPredkosc = (xPredkosc + roznica_x)/15;
            yPredkosc = -1 * yPredkosc;

            return;
        }
    }
}

void Pilka::kolizja_z_blokami(){
    QList<QGraphicsItem*> kolizje = collidingItems();
    for (int i = 0, n = kolizje.size(); i < n; ++i){
        Blok* blok = dynamic_cast<Blok*>(kolizje[i]);
        if (blok){
            double margines_y = 15;
            double margines_x = 15;
            double pilka_x = pos().x();
            double pilka_y = pos().y();
            double blok_x = blok->pos().x();
            double blok_y = blok->pos().y();

            if (pilka_y > blok_y + margines_y && yPredkosc < 0)     yPredkosc = -1 * yPredkosc;
            if (blok_y > pilka_y + margines_y && yPredkosc > 0)     yPredkosc = -1 * yPredkosc;
            if (pilka_x > blok_x + margines_x && xPredkosc < 0)     xPredkosc = -1 * xPredkosc;
            if (blok_x > pilka_x + margines_x && xPredkosc > 0)     xPredkosc = -1 * xPredkosc;

            gra->scene->removeItem(blok);
            delete blok;
            gra->wynik++;
            gra->zniszczone_bloki++;
            if (gra->zniszczone_bloki == gra ->bloki_na_planszy) {gra->wygrana(); yPredkosc *= 1.2;}


        }
    }

}
