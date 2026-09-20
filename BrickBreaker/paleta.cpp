#include "paleta.h"

Paleta::Paleta()
{
    QPixmap imagen(":/imagenes/paleta.png");
    imagen=imagen.scaled(180,45,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(350, 530);
    grafico->setScale(1);

    mini=false;
    grande=false;
    ralentizado=false;
}

QGraphicsPixmapItem* Paleta::getGrafico(){
    return grafico;
}

void Paleta::moverIzquierda(){
    if (grafico->x() > 20){
        if(ralentizado){
            grafico->moveBy(-5,0);
            return;
        }
        grafico->moveBy(-20, 0);
    }
}

void Paleta::moverDerecha(){
    if (grafico->x() + grafico->boundingRect().width() < 790){
        if(ralentizado){
            grafico->moveBy(5,0);
            return;
        }
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
    if(mini){
        hacerNormal();
        return;
    }
    float nuevoAncho=180*1.25;
    grafico->setPixmap(grafico->pixmap().scaled(nuevoAncho,45));
    grande=true;
}

void Paleta::hacerNormal(){
    grafico->setPixmap(grafico->pixmap().scaled(180,45));
}

void Paleta::hacerMini(){
    if(grande){
        hacerNormal();
        return;
    }
    float nuevoAncho=180*0.75;
    grafico->setPixmap(grafico->pixmap().scaled(nuevoAncho,45));
    mini=true;
}

void Paleta::ralentizar(){
    ralentizado=true;
}

void Paleta::derralentizar(){
    ralentizado=false;
}
