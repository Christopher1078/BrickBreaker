#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Bloque
{
private:
    QGraphicsPixmapItem* grafico;
    bool destruido;
    int golpes;
    int tipo;
    int powerUp;

public:
    Bloque();
    ~Bloque();

    QGraphicsPixmapItem* getGrafico();
    void destruir();
    void setTipo(int tipo);
    bool estaDestruido();
    void inicializar(float x, float y, std::string rutaImagen);
    int getPowerUp();
    void setPowerUp(int powerUp);
};

#endif // BLOQUE_H
