#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>

#include "pelota.h"
#include "paleta.h"

class Juego : public QObject
{
    Q_OBJECT

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;

    Pelota* pelota;
    Paleta* paleta;

public:
    Juego();

    void actualizar();
    void keyPressEvent(QKeyEvent* evento);

protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};

#endif // JUEGO_H
