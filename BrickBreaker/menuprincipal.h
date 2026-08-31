#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

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

class MenuInicio;

class MenuPrincipal: public QObject
{
    Q_OBJECT
public:
    MenuPrincipal(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager);

private:
    QPushButton* btnJugar;
    QPushButton* btnInstrucciones;
    QPushButton* btnRecords;
    QPushButton* btnCerrar;
    MenuInicio* menuInicio;
};

#endif // MENUPRINCIPAL_H
