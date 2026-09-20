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
#include <QPushButton>
#include <QWidget>
#include <QString>

#include "pelota.h"
#include "paleta.h"
#include "bloque.h"
#include "powerup.h"

class UserManager;
class PantallaVictoria;
class PantallaDerrota;
class MenuNiveles;
class QLabel;

struct NodoPowerUp
{
    PowerUp* powerUp = nullptr;
    NodoPowerUp* siguiente = nullptr;
    NodoPowerUp* anterior = nullptr;
};

struct NodoPelota
{
    Pelota* pelota;
    NodoPelota* siguiente;
    NodoPelota* anterior;
};

class Juego : public QObject{
    Q_OBJECT

protected:
    const int FILAS = 5;
    const int COLUMNAS = 8;

    QGraphicsScene* escena;
    QGraphicsView* vista;

    UserManager* manager;

    QGraphicsTextItem* txtVidas;
    QGraphicsTextItem* txtPuntos;
    QGraphicsTextItem* txtTiempo;

    QGraphicsPixmapItem* corazones[4];

    PantallaVictoria* victoria;
    PantallaDerrota* derrota;

    QTimer* timer;

    QPushButton* btnPausa;
    QWidget* menuPausa;
    QPushButton* btnRendirse;
    QPushButton* btnResumir;
    QLabel* lblEspera;
    bool pausado;
    bool saliendoDelNivel;
    bool esperandoInicio;

    Pelota* pelota;
    Paleta* paleta;

    Bloque** bloques;

    NodoPowerUp* inicio;
    NodoPowerUp* fin;

    NodoPelota* pelotaInicio;
    NodoPelota* pelotaFin;

    int vidas;
    int puntos;
    int tiempo;
    int frames;
    int cantBloques;

    int tiempoObjetivo;
    int bonusObjetivo;
    int nivel;

    int tiempoPaleta;
    int tiempoVeloz;
    int tiempoLento;
    int tiempoMini;
    int tiempoRalentizado;

    bool eventFilter(QObject* objeto,QEvent* evento) override;

    void actualizar();

    void iniciarTimer();

    void crearBarraSuperior();

    void crearMenuPausa();

    void pausarJuego();

    void resumirJuego();

    void rendirse();

    void ocultarControlesPausa();

    void mostrarEspera(const QString& mensaje);

    void comenzarTrasEspera();

    void actualizarBarra();

    void perderVida();

    void reiniciarPelota();

    void verificarVictoria();

    void limpiarNivel();

    void calcularPuntaje(int& bonusTiempo,int& bonusVida,int& puntoFinal,int& estrellas);

    void activarPowerUp(Tipo tipo);

    void eliminarPowerUp(NodoPowerUp* nodo);

    void crearPelotaExtra();

    void eliminarPelota(NodoPelota* nodo);

    void revisarColisionBloques(Pelota* p);

public:
    Juego(QGraphicsScene* escena,QGraphicsView* vista,UserManager* manager);

    virtual ~Juego();
};

#endif