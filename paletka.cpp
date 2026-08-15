#include "paletka.h"
#include <QBrush>

Paletka::Paletka(QGraphicsItem *parent){
    setRect(0,0,100,15);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
}

double Paletka::srodek_x(){
    return x()+rect().width()/2;
}

void Paletka::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    double mouseX = mapToScene(event->pos()).x();
    setPos(mouseX-50,y());

}
