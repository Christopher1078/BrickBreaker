#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsRectItem>

class Bloque
{
private:
    QGraphicsRectItem* grafico;
    bool destruido;

public:
    Bloque(float x, float y);

    QGraphicsRectItem* getGrafico();

    void destruir();
    bool estaDestruido();
};

#endif // BLOQUE_H
