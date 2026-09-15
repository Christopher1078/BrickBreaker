#include "powerup.h"

PowerUp::PowerUp(Tipo tipo) {
    this->tipo=tipo;
    velocidadY=3;

    QPixmap imagen;

    switch(tipo){
    case PALETA_LARGA:{
        imagen=QPixmap(":/imagenes/paleta_larga.png");
        break;
    }
    case VELOCIDAD_EXTRA:{
        imagen=QPixmap(":/imagenes/pelota_veloz.png");
        break;
    }
    case VIDA_EXTRA:{
        imagen=QPixmap(":/imagenes/vida_extra.png");
        break;
    }
    case PELOTA_EXTRA:{
        imagen=QPixmap(":/imagenes/pelota_extra.png");
        break;
    }
    }
    imagen=imagen.scaled(30,30,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(390, 500);

}

void PowerUp::mover(){
    grafico->moveBy(0,velocidadY);
}

Tipo PowerUp::getTipo(){
    return tipo;
}

QGraphicsPixmapItem* PowerUp::getGrafico(){
    return grafico;
}
