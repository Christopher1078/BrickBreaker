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
    bool aumentado;
    bool ralentizado;
    float xAnterior;
    float yAnterior;

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
    void rebotarPaleta(QGraphicsItem* paleta);
    void rebotarBloque(QGraphicsItem* bloque);
    void reiniciarMovimiento();
    void aumentarVelocidad();
    void disminuirVelocidad();
    void ralentalizar();

    float getVelocidadX() const;
    float getVelocidadY() const;
    bool estaAumentada() const;
    bool estaRalentizada() const;
    void restaurarEstado(float x, float y, float vx, float vy, bool aumentada, bool ralentizada);
};

#endif // PELOTA_H
