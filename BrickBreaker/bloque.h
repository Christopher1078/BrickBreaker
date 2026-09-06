#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace std;

class Bloque
{
private:
    QGraphicsPixmapItem* grafico;
    bool destruido;

public:
    Bloque();
    ~Bloque();

    QGraphicsPixmapItem* getGrafico();
    void destruir();
    bool estaDestruido();
    void inicializar(float x, float y, string rutaImagen);
};

#endif // BLOQUE_H
