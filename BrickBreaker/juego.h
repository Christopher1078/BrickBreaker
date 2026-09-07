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
class PantallaVictoria;
class PantallaDerrota;

class Juego : public QObject
{
    Q_OBJECT

protected:
    int FILAS;
    int COLUMNAS;
    QGraphicsScene* escena;
    QGraphicsView* vista;
    UserManager* manager;
    QGraphicsTextItem* txtVidas;
    QGraphicsTextItem* txtPuntos;
    QGraphicsTextItem* txtTiempo;
    QGraphicsPixmapItem* corazones[3];
    PantallaVictoria* victoria;
    PantallaDerrota* derrota;
    QTimer* timer;
    Pelota* pelota;
    Paleta* paleta;
    Bloque** bloques;
    int vidas;
    int puntos;
    int tiempo;
    int frames;
    int cantBloques;
    int tiempoObjetivo;
    int bonusObjetivo;
    int nivel;

    bool eventFilter(QObject* objeto, QEvent* evento) override;
    void actualizar();
    void iniciarTimer();
    void crearBarraSuperior();
    void actualizarBarra();
    void perderVida();
    void reiniciarPelota();
    void verificarVictoria();
    void limpiarNivel();
    void calcularPuntaje(int &bonusTiempo, int &bonusVida, int &puntoFinal, int &estrellas);
public:
    Juego(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
    virtual ~Juego();
};

#endif // JUEGO_H
