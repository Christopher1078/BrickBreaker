#include "pelota.h"

Pelota::Pelota()
{
    QPixmap imagen(":/imagenes/pelota.png");
    imagen=imagen.scaled(20,20,Qt::IgnoreAspectRatio,Qt::FastTransformation);
    grafico = new QGraphicsPixmapItem(imagen);
    grafico->setPos(390, 500);

    velocidadX = 0;
    velocidadY = -6;
    aumentado=false;
    ralentizado=false;
    xAnterior=390;
    yAnterior=500;
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
    QRectF p = grafico->sceneBoundingRect();
    QRectF b = bloque->sceneBoundingRect();
    QRectF antes(xAnterior, yAnterior, p.width(), p.height());

    float solapX = std::min(p.right(), b.right()) - std::max(p.left(), b.left());
    float solapY = std::min(p.bottom(), b.bottom()) - std::max(p.top(), b.top());
    if(solapX <= 0 || solapY <= 0){
        return;
    }

    bool antesEnX = antes.right() > b.left() && antes.left() < b.right();
    bool antesEnY = antes.bottom() > b.top() && antes.top() < b.bottom();

    bool vertical;
    if(antesEnX && !antesEnY){
        vertical = true;
    }else if(antesEnY && !antesEnX){
        vertical = false;
    }else{
        vertical = (solapY <= solapX);
    }

    if(vertical){
        if(p.center().y() < b.center().y()){
            grafico->moveBy(0, -solapY);
            velocidadY = -std::abs(velocidadY);
        }else{
            grafico->moveBy(0, solapY);
            velocidadY = std::abs(velocidadY);
        }
    }else{
        if(p.center().x() < b.center().x()){
            grafico->moveBy(-solapX, 0);
            velocidadX = -std::abs(velocidadX);
        }else{
            grafico->moveBy(solapX, 0);
            velocidadX = std::abs(velocidadX);
        }
    }
}

void Pelota::rebotarPaleta(QGraphicsItem* paleta){
    float mitadPaleta=paleta->boundingRect().width()/2;
    float centroPaleta=paleta->x()+mitadPaleta;

    float centroPelota=getGrafico()->x()+getGrafico()->boundingRect().width()/2;

    float distancia=centroPelota-centroPaleta;
    float porcentaje=distancia/mitadPaleta;

    QVector2D direccion(porcentaje,-1);
    direccion.normalize();

    if(aumentado==ralentizado){
        direccion*=6;
    }else if(aumentado){
        direccion*=8;
    }else if(ralentizado){
        direccion*=4;
    }

    velocidadX=direccion.x();
    velocidadY=direccion.y();
}

void Pelota::mover()
{
    float fraccion=1.0f;
    xAnterior = grafico->x();
    yAnterior = grafico->y();
    grafico->moveBy(velocidadX * fraccion, velocidadY * fraccion);
}

void Pelota::comprobarParedes()
{

    if (grafico->x() <= 20){
        reflejar(QVector2D(1,0));
    }

    if (grafico->x() >= 770){
        reflejar(QVector2D(-1,0));
    }

    if (grafico->y()<= 20){
        reflejar(QVector2D(0,1));
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
    return grafico->sceneBoundingRect().intersects(objeto->sceneBoundingRect());
}

bool Pelota::estaBajando()
{
    return velocidadY > 0;
}

void Pelota::reiniciarMovimiento(){
    velocidadX=0;
    velocidadY=-6;
}

void Pelota::aumentarVelocidad(){
    if(ralentizado){
        disminuirVelocidad();
        return;
    }
    QVector2D velocidad(velocidadX, velocidadY);
    velocidad.normalize();
    velocidad *= 8;
    velocidadX = velocidad.x();
    velocidadY = velocidad.y();
    aumentado=true;
}

void Pelota::disminuirVelocidad(){
    QVector2D velocidad(velocidadX, velocidadY);
    velocidad.normalize();
    velocidad *= 6;
    velocidadX = velocidad.x();
    velocidadY = velocidad.y();
    aumentado=false;
    ralentizado=false;
}

void Pelota::ralentalizar(){
    if(aumentado){
        disminuirVelocidad();
        return;
    }
    QVector2D velocidad(velocidadX,velocidadY);
    velocidad.normalize();
    velocidad *= 4;
    velocidadX = velocidad.x();
    velocidadY = velocidad.y();
    ralentizado=true;
}

Pelota::~Pelota(){
    delete grafico;
}
float Pelota::getVelocidadX() const{
    return velocidadX;
}

float Pelota::getVelocidadY() const{
    return velocidadY;
}

bool Pelota::estaAumentada() const{
    return aumentado;
}

bool Pelota::estaRalentizada() const{
    return ralentizado;
}

void Pelota::restaurarEstado(float x, float y, float vx, float vy, bool aumentada, bool ralentizada){
    grafico->setPos(x, y);
    velocidadX = vx;
    velocidadY = vy;
    aumentado = aumentada;
    ralentizado = ralentizada;
}
