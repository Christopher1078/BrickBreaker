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

class PantallaDerrota: public QObject
{
    Q_OBJECT
public:
    PantallaDerrota(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager, int puntos, int tiempo, int bloques);
    ~PantallaDerrota();
private:
    QPushButton* btnReintentar;
    QPushButton* btnVolver;
    QGraphicsTextItem* txtPuntos;
    QGraphicsTextItem* txtTiempo;
    QGraphicsTextItem* txtBloques;
    MenuPrincipal* menuPrincipal;
};

#endif // PANTALLADERROTA_H
