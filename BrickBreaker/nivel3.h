#ifndef NIVEL3_H
#define NIVEL3_H

#include "juego.h"
#include "usermanager.h"

class Nivel3:public Juego
{
public:
    Nivel3(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
};

#endif // NIVEL3_H
