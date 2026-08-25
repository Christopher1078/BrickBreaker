#ifndef PALETA_H
#define PALETA_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class Paleta
{
private:
    QGraphicsRectItem* grafico;

public:
    Paleta();

    QGraphicsRectItem* getGrafico();

    void moverIzquierda();
    void moverDerecha();
};

#endif // PALETA_H
