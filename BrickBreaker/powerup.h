#ifndef POWERUP_H
#define POWERUP_H

#include <qgraphicsitem.h>

enum Tipo{
    PALETA_LARGA,
    VELOCIDAD_EXTRA,
    VIDA_EXTRA,
    PELOTA_EXTRA
};

class PowerUp: public QGraphicsPixmapItem
{
public:
    PowerUp(Tipo tipo);
    void mover();
    Tipo getTipo();
    QGraphicsPixmapItem* getGrafico();
private:
    QGraphicsPixmapItem* grafico;
    Tipo tipo;
    float velocidadY;
};

#endif // POWERUP_H
