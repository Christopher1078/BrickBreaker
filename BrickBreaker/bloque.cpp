#include "bloque.h"

Bloque::Bloque(){
    tipo=0;
    golpes=1;
    grafico=nullptr;
    destruido=false;
    powerUp=0;
}

void Bloque::inicializar(float x,float y, std::string rutaImagen){
    QPixmap imagen(rutaImagen.c_str());
    if(tipo==1){
        imagen=QPixmap(":/imagenes/blindado_0.png");
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

void Bloque::setTipo(int tipo){
    this->tipo=tipo;
    switch(tipo){
    case 0:{
        golpes=1;
    }
    case 1:{
        golpes=3;
    }
    }
}

int Bloque::getPowerUp(){
    return powerUp;
}

void Bloque::setPowerUp(int powerUp){
    this->powerUp=powerUp;
}
