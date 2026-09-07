#include "bloque.h"

Bloque::Bloque(){
    grafico=nullptr;
    destruido=false;
}

void Bloque::inicializar(float x,float y, std::string rutaImagen){
    QPixmap imagen(rutaImagen.c_str());
    imagen=imagen.scaled(55,25,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
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
    destruido = true;
}

bool Bloque::estaDestruido()
{
    return destruido;
}
