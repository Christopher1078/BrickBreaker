#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QVector2D>

class Pelota
{
private:
    QGraphicsPixmapItem* grafico;

    float velocidadX;
    float velocidadY;

public:
    Pelota();
    ~Pelota();

    QGraphicsPixmapItem* getGrafico();

    void mover();
    void comprobarParedes();
    void reflejar(QVector2D normal);
    bool colisionaCon(QGraphicsItem* objeto);
    void rebotarVertical();
    bool estaBajando();
    void rebotarPaleta(float porcentaje);
    void rebotarBloque(QGraphicsItem* bloque);
    void reiniciarMovimiento();
};

#endif // PELOTA_H
