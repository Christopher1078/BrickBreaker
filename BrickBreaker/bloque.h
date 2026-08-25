#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QColor>

class Bloque
{
private:
    QGraphicsRectItem* grafico;
    bool destruido;

public:
    Bloque(float x, float y, QColor color);

    QGraphicsRectItem* getGrafico();

    void destruir();
    bool estaDestruido();
};

#endif // BLOQUE_H
