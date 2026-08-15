#include "blok.h"
#include <QBrush>

Blok::Blok(QGraphicsItem *parent): QGraphicsRectItem(parent){
    setRect(0,0,50,20);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}
