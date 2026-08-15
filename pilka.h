#ifndef PILKA_H
#define PILKA_H

#include <QGraphicsRectItem>

class Pilka: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    Pilka(QGraphicsItem* parent=nullptr);

    double srodek_x();
    void kolejna_pilka();
    void zniszcz();
    int id;

public slots:

    void fizyka();

private:

    double xPredkosc;
    double yPredkosc;

    void odbijanie_od_scian();
    void kolizja_z_paletka();
    void kolizja_z_blokami();
};

#endif // PILKA_H
