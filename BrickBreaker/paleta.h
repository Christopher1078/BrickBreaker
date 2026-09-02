#ifndef PALETA_H
#define PALETA_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Paleta
{
private:
    QGraphicsPixmapItem* grafico;

public:
    Paleta();
    ~Paleta();

    QGraphicsPixmapItem* getGrafico();

    void moverIzquierda();
    void moverDerecha();
};

#endif // PALETA_H
