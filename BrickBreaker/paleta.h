#ifndef PALETA_H
#define PALETA_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Paleta
{
private:
    QGraphicsPixmapItem* grafico;
    bool ralentizado;
    bool mini;
    bool grande;

public:
    Paleta();
    ~Paleta();

    QGraphicsPixmapItem* getGrafico();

    void moverIzquierda();
    void moverDerecha();
    void reiniciar();
    void hacerGrande();
    void hacerNormal();
    void hacerMini();
    void ralentizar();
    void derralentizar();

    bool estaGrande() const;
    bool estaMini() const;
    bool estaRalentizada() const;
    void restaurarEstado(float x, float y, bool grande, bool mini, bool ralentizada);
};

#endif // PALETA_H
