#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

enum TipoBloque{
    NORMAL,
    BLINDADO,
    METALICO,
    MOVIL
};

class Bloque
{
private:
    QGraphicsPixmapItem* grafico;
    bool destruido;
    int golpes;
    int powerUp;
    TipoBloque tipoBloque;
    float velocidad;
    float limIzq;
    float limDer;

public:
    Bloque();
    ~Bloque();

    QGraphicsPixmapItem* getGrafico();
    void destruir();
    bool estaDestruido();
    void inicializar(float x, float y, std::string rutaImagen);
    void setBlindado();
    void setMetalico();
    void setMovil(float limIzq, float limDer);
    int getPowerUp();
    void setPowerUp(int powerUp);
    TipoBloque getTipoBloque();
    void mover();
};

#endif // BLOQUE_H
