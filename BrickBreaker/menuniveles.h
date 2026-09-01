#ifndef MENUNIVELES_H
#define MENUNIVELES_H

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

class MenuNiveles: public QObject
{
    Q_OBJECT
public:
    MenuNiveles(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);
private:
    QPushButton* btnNivel1;
    QPushButton* btnNivel2;
    QPushButton* btnNivel3;
    QPushButton* btnNivel4;
    QPushButton* btnNivel5;
    QPushButton* btnRegresar;
    MenuPrincipal* menuPrincipal;
};

#endif // MENUNIVELES_H
