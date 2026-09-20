#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

class UserManager;
class MenuPrincipal;

class Instrucciones : public QObject
{
    Q_OBJECT

public:
    Instrucciones(
        QGraphicsScene* escena,
        QGraphicsView* vista,
        UserManager* manager
        );

    ~Instrucciones();

private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    UserManager* manager;

    QPushButton* btnRegresar;

    MenuPrincipal* menuPrincipal;
};

#endif // INSTRUCCIONES_H