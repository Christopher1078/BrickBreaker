#ifndef CREARCUENTA_H
#define CREARCUENTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <windows.h>

#include "usermanager.h"

class MenuInicio;

using namespace std;

class CrearCuenta: public QObject
{
    Q_OBJECT
public:
    CrearCuenta(QGraphicsScene* escena, QGraphicsView* vista);
private:
    QLineEdit* txtNombre;
    QLineEdit* txtPassword;
    QPushButton* btnCrear;
    QPushButton* btnRegresar;
    QPushButton* btnMostrar;
    UserManager manager;
    MenuInicio* menu;
};

#endif // CREARCUENTA_H
