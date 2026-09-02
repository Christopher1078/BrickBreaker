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
class IniciarSesion;

class MenuInicio:public QObject
{
    Q_OBJECT
public:
    MenuInicio(QGraphicsScene* escena, QGraphicsView* vista);
    MenuInicio();
    ~MenuInicio();
    void mostrarMenu();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    CrearCuenta* crear;
    IniciarSesion* iniciar;
    QPushButton* btnInicio;
    QPushButton* btnCrear;
    QPushButton* btnSalir;
};

#endif // MENUINICIO_H
