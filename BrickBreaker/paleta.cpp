#include "paleta.h"

Paleta::Paleta()
{
    grafico = new QGraphicsRectItem(0, 0, 100, 20);
    grafico->setPos(350, 550);
    grafico->setBrush(QBrush(QColor(40, 220, 255)));
    grafico->setPen(QPen(QColor(180, 250, 255), 2));
}

QGraphicsRectItem* Paleta::getGrafico(){
    return grafico;
}

void Paleta::moverIzquierda(){
    if (grafico->x() > 0){
        grafico->moveBy(-20, 0);
    }
}

void Paleta::moverDerecha(){
    if (grafico->x() + grafico->rect().width() < 800){
        grafico->moveBy(20, 0);
    }
}
