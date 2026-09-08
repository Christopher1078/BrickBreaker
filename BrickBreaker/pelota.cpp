#include "pelota.h"

Pelota::Pelota()
{
    QPixmap imagen(":/imagenes/pelota.png");
    imagen=imagen.scaled(20,20,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(390, 500);

    velocidadX = 4;
    velocidadY = -4;
}

QGraphicsPixmapItem* Pelota::getGrafico()
{
    return grafico;
}

void Pelota::reflejar(QVector2D normal){
    QVector2D velocidad(velocidadX, velocidadY);
    normal.normalize();
    velocidad=velocidad-2*QVector2D::dotProduct(velocidad,normal)*normal;

    velocidadX=velocidad.x();
    velocidadY=velocidad.y();
}

void Pelota::rebotarBloque(QGraphicsItem* bloque){
    QRectF pelotaRect = grafico->sceneBoundingRect();
    QRectF bloqueRect = bloque->sceneBoundingRect();

    float solapamientoX = std::min(pelotaRect.right(), bloqueRect.right()) - std::max(pelotaRect.left(), bloqueRect.left());
    float solapamientoY = std::min(pelotaRect.bottom(), bloqueRect.bottom()) - std::max(pelotaRect.top(), bloqueRect.top());

    if(solapamientoX <= 0 || solapamientoY <= 0){
        return;
    }

    float direccionX = velocidadX;
    float direccionY = velocidadY;

    if(solapamientoX < solapamientoY){
        if(direccionX > 0){
            grafico->moveBy(-solapamientoX, 0);
        }else{
            grafico->moveBy(solapamientoX, 0);
        }
        velocidadX = -velocidadX;
    }

    else{
        if(direccionY > 0){
            grafico->moveBy(0, -solapamientoY);
        }else{
            grafico->moveBy(0, solapamientoY);
        }
        velocidadY = -velocidadY;
    }
}

void Pelota::rebotarPaleta(float porcentaje){
    if(porcentaje<-1){
        porcentaje = -1;
    }
    if(porcentaje>1){
        porcentaje=1;
    }

    velocidadX=porcentaje*6;
    velocidadY=-6;
}

void Pelota::mover()
{
    grafico->moveBy(velocidadX, velocidadY);
}

void Pelota::comprobarParedes()
{

    if (grafico->x() <= 20)
    {
        reflejar(QVector2D(1,0));
    }

    if (grafico->x() >= 770)
    {
        reflejar(QVector2D(-1,0));
    }

    if (grafico->y()<= 20)
    {
        reflejar(QVector2D(0,1));
    }

    if (grafico->y() >= 590)
    {
        reflejar(QVector2D(0,-1));
    }

    if(grafico->x() > 770){
        grafico->setX(770);
    }else if(grafico->x() < 20){
        grafico->setX(20);
    }

    if(grafico->y() < 20){
        grafico->setY(20);
    }
}

void Pelota::rebotarVertical()
{
    velocidadY = -velocidadY;
}

bool Pelota::colisionaCon(QGraphicsItem* objeto)
{
    return grafico->collidesWithItem(objeto);
}

bool Pelota::estaBajando()
{
    return velocidadY > 0;
}

void Pelota::reiniciarMovimiento(){
    velocidadX=4;
    velocidadY=-4;
}

void Pelota::aumentarVelocidad(){
    velocidadX*=1.5;
    velocidadY*=1.5;
    if(velocidadX>10 || velocidadX<-10){
        velocidadX=(velocidadX>0)? 10 : -10;
    }
    if(velocidadY>10 || velocidadY<-10){
        velocidadY=(velocidadY>0)? 10:-10;
    }
}

void Pelota::disminuirVelocidad(){
    velocidadX = (velocidadX>0)?4:-4;
    velocidadY = (velocidadY>0)?4:-4;
}

Pelota::~Pelota(){
    delete grafico;
}