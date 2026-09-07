#ifndef NIVEL4_H
#define NIVEL4_H

#include "juego.h"
#include "usermanager.h"

class Nivel4:public Juego
{
public:
    Nivel4(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
};

#endif // NIVEL4_H
