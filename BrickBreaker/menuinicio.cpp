#include "menuinicio.h"
#include "crearcuenta.h"
#include "iniciarsesion.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QApplication>

MenuInicio::MenuInicio(){
    escena=new QGraphicsScene;
    escena->setSceneRect(0,0,800,600);

    vista=new QGraphicsView(escena);
    vista->setFixedSize(820,620);

    mostrarMenu();
    vista->show();
}

MenuInicio::MenuInicio(QGraphicsScene* escena, QGraphicsView* vista) {
    this->escena=escena;
    this->vista=vista;

    mostrarMenu();

    vista->show();
}

void MenuInicio::mostrarMenu(){
    escena->clear();
    QPixmap fondo(":/imagenes/menu.png");
    fondo = fondo.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen = escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0, 0);

    btnCrear=new QPushButton(vista);
    btnCrear->setGeometry(250, 270, 320, 60);
    btnCrear->setStyleSheet(
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
        );
    connect(btnCrear,&QPushButton::clicked,this,[this](){
        btnCrear->hide();
        btnInicio->hide();
        btnSalir->hide();
        escena->clear();
        vista->removeEventFilter(this);
        crear=new CrearCuenta(escena,vista);
    });
    btnCrear->show();

    btnInicio=new QPushButton(vista);
    btnInicio->setGeometry(250, 350, 320, 60);
    btnInicio->setStyleSheet(
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
        );
    connect(btnInicio,&QPushButton::clicked,this,[this](){
        btnCrear->hide();
        btnInicio->hide();
        btnSalir->hide();
        escena->clear();
        vista->removeEventFilter(this);
        iniciar=new IniciarSesion(escena, vista);
    });
    btnInicio->show();

    btnSalir=new QPushButton(vista);
    btnSalir->setGeometry(250, 430, 320, 60);
    btnSalir->setStyleSheet(
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
        );
    connect(btnSalir,&QPushButton::clicked,qApp,&QApplication::quit);
    btnSalir->show();
}



