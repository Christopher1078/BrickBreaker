#ifndef PANTALLARECORDS_H
#define PANTALLARECORDS_H

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

class PantallaRecords: public QObject{
    Q_OBJECT
public:
    PantallaRecords(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
    ~PantallaRecords();
private:
    QPushButton* btnRegresar;
    QGraphicsTextItem* nivel1;
    QGraphicsTextItem* nivel2;
    QGraphicsTextItem* nivel3;
    QGraphicsTextItem* nivel4;
    QGraphicsTextItem* nivel5;
    MenuPrincipal* menuPrincipal;
};

#endif // PANTALLARECORDS_H
