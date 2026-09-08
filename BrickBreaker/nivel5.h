#ifndef NIVEL5_H
#define NIVEL5_H

#include "juego.h"
#include "usermanager.h"

class Nivel5:public Juego
{
public:
    Nivel5(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
};

#endif // NIVEL5_H
