#include "bloque.h"

Bloque::Bloque(){
    golpes=1;
    grafico=nullptr;
    destruido=false;
    powerUp=0;
    tipoBloque=NORMAL;
    velocidad=3;
}

void Bloque::inicializar(float x,float y, std::string rutaImagen){
    QPixmap imagen;

    switch(tipoBloque){
    case NORMAL:{
        imagen=QPixmap(rutaImagen.c_str());
        break;
    }
    case BLINDADO:{
        imagen=QPixmap(":/imagenes/blindado_0.png");
        break;
    }
    case METALICO:{
        imagen=QPixmap(":/imagenes/metalico.png");
        break;
    }
    case MOVIL:
        imagen=QPixmap(rutaImagen.c_str());
        break;
    }
    imagen=imagen.scaled(75,45,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(x, y);
}

Bloque::~Bloque(){
    delete grafico;
}

QGraphicsPixmapItem* Bloque::getGrafico(){
    return grafico;
}

void Bloque::destruir(){
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

bool Bloque::estaDestruido(){
    return destruido;
}

void Bloque::setBlindado(){
    tipoBloque=BLINDADO;
    golpes=3;
}

void Bloque::setMetalico(){
    tipoBloque=METALICO;
}

void Bloque::setMovil(float limIzq, float limDer){
    tipoBloque=MOVIL;
    this->limIzq=limIzq;
    this->limDer=limDer;
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

void Bloque::mover(){
    if(tipoBloque!=MOVIL){
        return;
    }
    grafico->moveBy(velocidad,0);
    if(grafico->sceneBoundingRect().left() <= limIzq){
        velocidad = -velocidad;
    }

    if(grafico->sceneBoundingRect().right() >= limDer){
        velocidad = -velocidad;
    }
}

int Bloque::getGolpes() const{
    return golpes;
}

float Bloque::getVelocidad() const{
    return velocidad;
}

void Bloque::restaurarEstado(bool estadoDestruido, int golpesRestantes, float x, float y, float nuevaVelocidad){
    destruido = estadoDestruido;
    golpes = golpesRestantes;
    velocidad = nuevaVelocidad;

    if(grafico == nullptr){
        return;
    }

    grafico->setPos(x, y);

    if(tipoBloque == BLINDADO && !destruido){
        QString ruta = ":/imagenes/blindado_0.png";
        if(golpes == 2){
            ruta = ":/imagenes/blindado_1.png";
        }else if(golpes == 1){
            ruta = ":/imagenes/blindado_2.png";
        }

        QPixmap imagen(ruta);
        imagen = imagen.scaled(75, 45, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        grafico->setPixmap(imagen);
    }
}
