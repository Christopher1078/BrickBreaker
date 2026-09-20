#include "menuprincipal.h"

#include "menuniveles.h"
#include "pantallarecords.h"
#include "music.h"

#include "instrucciones.h"
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QPixmap>

MenuPrincipal::MenuPrincipal(QGraphicsScene* escena,QGraphicsView* vista,UserManager* manager)
{
    menuNiveles = nullptr;
    pantallaRecords = nullptr;
    music = nullptr;
    instrucciones = nullptr;

    QPixmap fondo(
        ":/imagenes/menuprincipal.png"
        );

    fondo = fondo.scaled(
        800,
        600,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    QGraphicsPixmapItem* imagen =
        escena->addPixmap(fondo);

    imagen->setZValue(-1);
    imagen->setPos(0, 0);

    QString transparente =
        "QPushButton {"
        "background: transparent;"
        "border: none;"
        "}";

    btnJugar = new QPushButton(vista);

    btnJugar->setGeometry(
        260,
        250,
        285,
        52
        );

    btnJugar->setStyleSheet(
        transparente
        );

    btnJugar->show();

    connect(
        btnJugar,
        &QPushButton::clicked,
        this,
        [this, escena, vista, manager]()
        {
            ocultarBotones();

            escena->clear();

            vista->removeEventFilter(this);

            menuNiveles =
                new MenuNiveles(
                    escena,
                    vista,
                    manager
                    );
        }
        );

    btnInstrucciones =
        new QPushButton(vista);

    btnInstrucciones->setGeometry(
        260,
        310,
        285,
        52
        );

    btnInstrucciones->setStyleSheet(
        transparente
        );

    btnInstrucciones->show();

    connect(
        btnInstrucciones, &QPushButton::clicked,this,[this, escena, vista, manager]() {
            ocultarBotones();escena->clear();
vista->removeEventFilter(this);
 instrucciones =new Instrucciones( escena, vista, manager );
        }
        );

    btnRecords =
        new QPushButton(vista);

    btnRecords->setGeometry(
        260,
        370,
        285,
        52
        );

    btnRecords->setStyleSheet(
        transparente
        );

    btnRecords->show();

    connect(
        btnRecords,
        &QPushButton::clicked,
        this,
        [this, escena, vista, manager]()
        {
            ocultarBotones();

            escena->clear();

            vista->removeEventFilter(this);

            pantallaRecords =
                new PantallaRecords(
                    escena,
                    vista,
                    manager
                    );
        }
        );

    btnMusica =
        new QPushButton(vista);

    btnMusica->setGeometry(
        260,
        430,
        285,
        52
        );

    btnMusica->setStyleSheet(
        transparente
        );

    btnMusica->show();

    connect(
        btnMusica,
        &QPushButton::clicked,
        this,
        [this, escena, vista, manager]()
        {
            ocultarBotones();

            escena->clear();

            vista->removeEventFilter(this);

            music =
                new Music(
                    escena,
                    vista,
                    manager
                    );
        }
        );

    btnCerrar =
        new QPushButton(vista);

    btnCerrar->setGeometry(
        260,
        486,
        285,
        52
        );

    btnCerrar->setStyleSheet(
        transparente
        );

    btnCerrar->show();

    connect(
        btnCerrar,
        &QPushButton::clicked,
        this,
        [manager]()
        {
            manager->cerrarSesion();

            QApplication::quit();
        }
        );

    vista->show();
}

void MenuPrincipal::ocultarBotones()
{
    btnJugar->hide();
    btnInstrucciones->hide();
    btnRecords->hide();
    btnMusica->hide();
    btnCerrar->hide();
}

MenuPrincipal::~MenuPrincipal()
{
    delete btnJugar;
    delete btnInstrucciones;
    delete btnRecords;
    delete btnMusica;
    delete btnCerrar;
}