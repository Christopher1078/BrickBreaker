#ifndef NIVEL2_H
#define NIVEL2_H

#include "juego.h"
#include "usermanager.h"

class Nivel2: public Juego
{
public:
    Nivel2(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
};

#endif // NIVEL2_H
