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

class Juego : public QObject
{
    Q_OBJECT

protected:
    const int FILAS=5;
    const int COLUMNAS=12;
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;
    Pelota* pelota;
    Paleta* paleta;
    Bloque** bloques;

    bool eventFilter(QObject* objeto, QEvent* evento) override;
    void actualizar();
    void iniciarTimer();
public:
    Juego(QGraphicsScene* escena, QGraphicsView* vista);
    virtual ~Juego();
};

#endif // JUEGO_H
