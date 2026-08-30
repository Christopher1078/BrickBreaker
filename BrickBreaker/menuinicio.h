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
#include <QPushButton>

#include "crearcuenta.h"

class MenuInicio:public QObject
{
public:
    MenuInicio();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    CrearCuenta* crear;
    QPushButton* btnInicio;
    QPushButton* btnCrear;
    QPushButton* btnSalir;
};

#endif // MENUINICIO_H
