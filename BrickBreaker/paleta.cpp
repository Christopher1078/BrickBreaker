#include "paleta.h"

Paleta::Paleta()
{
    QPixmap imagen(":/imagenes/paleta.png");
    imagen=imagen.scaled(180,45,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(350, 530);

}

QGraphicsPixmapItem* Paleta::getGrafico(){
    return grafico;
}

void Paleta::moverIzquierda(){
    if (grafico->x() > 0){
        grafico->moveBy(-20, 0);
    }
}

void Paleta::moverDerecha(){
    if (grafico->x() + grafico->boundingRect().width() < 800){
        grafico->moveBy(20, 0);
    }
}

Paleta::~Paleta(){
    delete grafico;
}
