#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <QColor>
#include <qgraphicsitem.h>

#include "pelota.h"
#include "paleta.h"
#include "bloque.h"

class UserManager;

class Juego : public QObject
{
    Q_OBJECT

protected:
    const int FILAS=5;
    const int COLUMNAS=12;
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QGraphicsTextItem* txtVidas;
    QGraphicsTextItem* txtPuntos;
    QGraphicsTextItem* txtTiempo;
    QTimer* timer;
    Pelota* pelota;
    Paleta* paleta;
    Bloque** bloques;
    int vidas;
    int puntos;
    int tiempo;
    int frames;

    bool eventFilter(QObject* objeto, QEvent* evento) override;
    void actualizar();
    void iniciarTimer();
    void crearBarraSuperior();
    void actualizarBarra();
    void perderVida();
    void reiniciarPelota();
public:
    Juego(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
    virtual ~Juego();
};

#endif // JUEGO_H
