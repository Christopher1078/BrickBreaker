#ifndef NIVEL1_H
#define NIVEL1_H

#include "juego.h"
#include "usermanager.h"

class Nivel1: public Juego
{
public:
    Nivel1(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
};

#endif // NIVEL1_H
