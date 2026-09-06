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

    float distanciaIzquierda=pelotaRect.right()-bloqueRect.left();
    float distanciaDerecha=bloqueRect.right()-pelotaRect.left();
    float distanciaArriba=pelotaRect.bottom()-bloqueRect.top();
    float distanciaAbajo=bloqueRect.bottom()-pelotaRect.top();
    float menorHorizontal=std::min(distanciaIzquierda, distanciaDerecha);
    float menorVertical=std::min(distanciaArriba, distanciaAbajo);

    if(menorHorizontal<menorVertical){
        velocidadX=-velocidadX;
    }else{
        velocidadY=-velocidadY;
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

Pelota::~Pelota(){
    delete grafico;
}