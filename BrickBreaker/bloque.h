#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

enum TipoBloque{
    NORMAL,
    BLINDADO,
    METALICO
};

class Bloque
{
private:
    QGraphicsPixmapItem* grafico;
    bool destruido;
    int golpes;
    int powerUp;
    TipoBloque tipoBloque;

public:
    Bloque();
    ~Bloque();

    QGraphicsPixmapItem* getGrafico();
    void destruir();
    bool estaDestruido();
    void inicializar(float x, float y, std::string rutaImagen);
    void setBlindado();
    void setMetalico();
    int getPowerUp();
    void setPowerUp(int powerUp);
    TipoBloque getTipoBloque();
};

#endif // BLOQUE_H
