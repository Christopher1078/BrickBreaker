#ifndef NIVEL1_H
#define NIVEL1_H

#include "juego.h"

class UserManager;

class Nivel1: public Juego
{
public:
    Nivel1(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
private:
};

#endif // NIVEL1_H
