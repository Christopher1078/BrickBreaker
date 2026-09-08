#include "paleta.h"

Paleta::Paleta()
{
    QPixmap imagen(":/imagenes/paleta.png");
    imagen=imagen.scaled(180,45,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(350, 530);
    grafico->setScale(1);

}

QGraphicsPixmapItem* Paleta::getGrafico(){
    return grafico;
}

void Paleta::moverIzquierda(){
    if (grafico->x() > 20){
        grafico->moveBy(-20, 0);
    }
}

void Paleta::moverDerecha(){
    if (grafico->x() + grafico->boundingRect().width() < 790){
        grafico->moveBy(20, 0);
    }
}

void Paleta::reiniciar(){
    grafico->setPos(350,530);
}

Paleta::~Paleta(){
    delete grafico;
}

void Paleta::hacerGrande(){
    float nuevoAncho=350*1.1;
    grafico->setPixmap(grafico->pixmap().scaled(nuevoAncho,45));
}

void Paleta::hacerNormal(){
    grafico->setPixmap(grafico->pixmap().scaled(180,45));
}
