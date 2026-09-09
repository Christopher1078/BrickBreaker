#include "bloque.h"

Bloque::Bloque(){
    golpes=1;
    grafico=nullptr;
    destruido=false;
    powerUp=0;
    tipoBloque=NORMAL;
}

void Bloque::inicializar(float x,float y, std::string rutaImagen){
    QPixmap imagen;

    switch(tipoBloque){
    case NORMAL:{
        imagen=QPixmap(rutaImagen.c_str());
        break;
    case BLINDADO:{
        imagen=QPixmap(":/imagenes/blindado_0.png");
        break;
    }
    case METALICO:{
        imagen=QPixmap(":/imagenes/metalico.png");
    }
    }
    }
    imagen=imagen.scaled(75,45,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(x, y);
}

Bloque::~Bloque(){
    delete grafico;
}

QGraphicsPixmapItem* Bloque::getGrafico()
{
    return grafico;
}

void Bloque::destruir()
{
    if(tipoBloque==METALICO){
        return;
    }
    golpes--;
    switch(golpes){
    case 0:{
        destruido=true;
        break;
    }
    case 1:{
        QPixmap imagen(":/imagenes/blindado_2.png");
        imagen=imagen.scaled(75,45,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        grafico->setPixmap(imagen);
        break;
    }
    case 2:{
        QPixmap imagen(":/imagenes/blindado_1.png");
        imagen=imagen.scaled(75,45,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        grafico->setPixmap(imagen);
        break;
    }
    }
}

bool Bloque::estaDestruido()
{
    return destruido;
}

void Bloque::setBlindado(){
    tipoBloque=BLINDADO;
    golpes=3;
}

void Bloque::setMetalico(){
    tipoBloque=METALICO;
}

int Bloque::getPowerUp(){
    return powerUp;
}

void Bloque::setPowerUp(int powerUp){
    this->powerUp=powerUp;
}

TipoBloque Bloque::getTipoBloque(){
    return tipoBloque;
}
