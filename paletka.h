#ifndef PALETKA_H
#define PALETKA_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paletka: public QGraphicsRectItem{
public:

    Paletka(QGraphicsItem* parent=nullptr);

    double srodek_x();

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PALETKA_H
