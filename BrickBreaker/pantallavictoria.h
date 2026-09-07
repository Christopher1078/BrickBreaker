#ifndef PANTALLAVICTORIA_H
#define PANTALLAVICTORIA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <QColor>
#include <qgraphicsitem.h>
#include <QPushButton>

class UserManager;
class MenuPrincipal;

class PantallaVictoria: public QObject
{
    Q_OBJECT
public:
    PantallaVictoria(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager, int puntosFinal, int base, int bonusTiempo, int bonusVida, int estrellas);
    ~PantallaVictoria();

private:
    QPushButton* btnSiguiente;
    QPushButton* btnVolver;
    QGraphicsTextItem* txtVidas;
    QGraphicsTextItem* txtBase;
    QGraphicsTextItem* txtTiempo;
    QGraphicsTextItem* txtFinal;
    QGraphicsPixmapItem* estrella[3];
    MenuPrincipal* menuPrincipal;
};

#endif // PANTALLAVICTORIA_H
