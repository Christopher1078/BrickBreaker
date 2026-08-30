#ifndef INICIARSESION_H
#define INICIARSESION_H

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

class IniciarSesion: public QObject
{
    Q_OBJECT
public:
    IniciarSesion(QGraphicsScene* escena, QGraphicsView* vista);
private:
    QLineEdit* txtNombre;
    QLineEdit* txtPassword;
    QPushButton* btnIniciar;
    QPushButton* btnRegresar;
    QPushButton* btnMostrar;
    UserManager manager;
    MenuInicio* menu;
};

#endif // INICIARSESION_H
