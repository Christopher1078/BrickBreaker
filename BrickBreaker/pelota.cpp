#include "pelota.h"

Pelota::Pelota()
{
    grafico = new QGraphicsEllipseItem(0, 0, 20, 20);
    grafico->setBrush(QBrush(Qt::white));
    grafico->setPen(QPen(QColor(180, 220, 255), 2));
    grafico->setPos(390, 500);

    velocidadX = 4;
    velocidadY = -4;
}

QGraphicsEllipseItem* Pelota::getGrafico()
{
    return grafico;
}

void Pelota::mover()
{
    grafico->moveBy(velocidadX, velocidadY);
}

void Pelota::comprobarParedes()
{
    QRectF limites = grafico->sceneBoundingRect();

    if (limites.left() <= 0)
    {
        grafico->setX(0);
        rebotarHorizontal();
    }

    if (limites.right() >= 800)
    {
        grafico->setX(780);
        rebotarHorizontal();
    }

    if (limites.top() <= 0)
    {
        grafico->setY(0);
        rebotarVertical();
    }

    if (limites.bottom() >= 600)
    {
        grafico->setY(580);
        rebotarVertical();
    }
}

void Pelota::rebotarHorizontal()
{
    velocidadX = -velocidadX;
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