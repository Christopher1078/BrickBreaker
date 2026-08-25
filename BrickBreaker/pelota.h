#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

class Pelota
{
private:
    QGraphicsEllipseItem* grafico;

    float velocidadX;
    float velocidadY;

public:
    Pelota();

    QGraphicsEllipseItem* getGrafico();

    void mover();
    void comprobarParedes();
    void rebotarHorizontal();
    void rebotarVertical();
    bool colisionaCon(QGraphicsItem* objeto);
    bool estaBajando();
};

#endif // PELOTA_H
