#include "bloque.h"

Bloque::Bloque(float x, float y)
{
    grafico = new QGraphicsRectItem(0, 0, 60, 20);

    grafico->setPos(x, y);

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
