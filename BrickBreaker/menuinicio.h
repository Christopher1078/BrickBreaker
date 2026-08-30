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

class CrearCuenta;

class MenuInicio:public QObject
{
    Q_OBJECT
public:
    MenuInicio(QGraphicsScene* escena, QGraphicsView* vista);
    MenuInicio();
    void mostrarMenu();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    CrearCuenta* crear;
    QPushButton* btnInicio;
    QPushButton* btnCrear;
    QPushButton* btnSalir;
};

#endif // MENUINICIO_H
