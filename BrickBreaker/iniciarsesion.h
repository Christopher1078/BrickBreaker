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
class MenuPrincipal;

using namespace std;

class IniciarSesion: public QObject
{
    Q_OBJECT
public:
    IniciarSesion(QGraphicsScene* escena, QGraphicsView* vista);
    ~IniciarSesion();
private:
    QLineEdit* txtNombre;
    QLineEdit* txtPassword;
    QPushButton* btnIniciar;
    QPushButton* btnRegresar;
    QPushButton* btnMostrar;
    UserManager* manager;
    MenuInicio* menu;
    MenuPrincipal* menuPrincipal;
};

#endif // INICIARSESION_H
