#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <QColor>
#include <qgraphicsitem.h>

#include "juego.h"

class MenuInicio:public QObject
{
public:
    MenuInicio();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    Juego* juego;

protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};

#endif // MENUINICIO_H
