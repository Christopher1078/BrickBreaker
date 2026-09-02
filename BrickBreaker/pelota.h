#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

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
    void rebotarHorizontal();
    void rebotarVertical();
    bool colisionaCon(QGraphicsItem* objeto);
    bool estaBajando();
};

#endif // PELOTA_H
