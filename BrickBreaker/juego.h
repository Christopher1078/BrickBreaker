#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <QColor>

#include "pelota.h"
#include "paleta.h"
#include "bloque.h"

class Juego : public QObject
{
    Q_OBJECT

private:
    static const int FILAS=3;
    static const int COLUMNAS=8;

    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;

    Pelota* pelota;
    Paleta* paleta;

    Bloque* bloques[FILAS][COLUMNAS];

public:
    Juego(QGraphicsScene* escena, QGraphicsView* vista);

    void actualizar();

protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};

#endif // JUEGO_H
