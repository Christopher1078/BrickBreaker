#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>

class UserManager;
class MenuPrincipal;

class Music : public QObject
{
    Q_OBJECT

public:
    Music(
        QGraphicsScene* escena,
        QGraphicsView* vista,
        UserManager* manager
        );

    ~Music();

private:
    void actualizarValores();
    void actualizarBotonMute();

    QGraphicsScene* escena;
    QGraphicsView* vista;
    UserManager* manager;

    QPushButton* btnMusicaMenos;
    QPushButton* btnMusicaMas;

    QPushButton* btnEfectosMenos;
    QPushButton* btnEfectosMas;

    QPushButton* btnMute;
    QPushButton* btnVolver;

    QLabel* lblMusica;
    QLabel* lblEfectos;

    MenuPrincipal* menuPrincipal;
};

#endif