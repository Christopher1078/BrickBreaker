#ifndef PANTALLADERROTA_H
#define PANTALLADERROTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <QColor>
#include <qgraphicsitem.h>
#include <QPushButton>

#include "usermanager.h"

class MenuPrincipal;
class Nivel1;
class Nivel2;
class Nivel3;
class Nivel4;
class Nivel5;

class PantallaDerrota: public QObject
{
    Q_OBJECT
public:
    PantallaDerrota(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager, int puntos, int tiempo, int bloques, int nivel);
    ~PantallaDerrota();
private:
    QPushButton* btnReintentar;
    QPushButton* btnVolver;
    QGraphicsTextItem* txtPuntos;
    QGraphicsTextItem* txtTiempo;
    QGraphicsTextItem* txtBloques;
    MenuPrincipal* menuPrincipal;
    Nivel1* nivel1;
    Nivel2* nivel2;
    Nivel3* nivel3;
    Nivel4* nivel4;
    Nivel5* nivel5;
};

#endif // PANTALLADERROTA_H
