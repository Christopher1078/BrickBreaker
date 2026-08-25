#include "bloque.h"

Bloque::Bloque(float x, float y, QColor color)
{
    grafico = new QGraphicsRectItem(0, 0, 80, 25);

    grafico->setPos(x, y);

    grafico->setBrush(QBrush(color));

    grafico->setPen(QPen(Qt::white, 2));

    destruido = false;
}
QGraphicsRectItem* Bloque::getGrafico()
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
