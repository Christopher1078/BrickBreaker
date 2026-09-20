#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

#include "usermanager.h"

class MenuNiveles;
class PantallaRecords;
class Music;
class Instrucciones;

class MenuPrincipal : public QObject
{
    Q_OBJECT

public:
    MenuPrincipal(QGraphicsScene* escena,QGraphicsView* vista, UserManager* manager );

    ~MenuPrincipal();

private:
    void ocultarBotones();

    QPushButton* btnJugar;
    QPushButton* btnInstrucciones;
    QPushButton* btnRecords;
    QPushButton* btnMusica;
    QPushButton* btnCerrar;

    MenuNiveles* menuNiveles;
    PantallaRecords* pantallaRecords;
    Music* music;
    Instrucciones* instrucciones;
};

#endif