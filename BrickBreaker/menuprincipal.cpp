#include "menuprincipal.h"
#include "menuinicio.h"
#include "menuniveles.h"

MenuPrincipal::MenuPrincipal(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager) {
    QPixmap fondo(":/imagenes/menuprincipal.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    btnJugar=new QPushButton(vista);
    btnJugar->setGeometry(270,260,285,55);
    btnJugar->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });
    btnJugar->show();
    connect(btnJugar,&QPushButton::clicked,this,[this, escena, vista, manager](){
        btnJugar->hide();
        btnInstrucciones->hide();
        btnRecords->hide();
        btnCerrar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menuNiveles=new MenuNiveles(escena,vista,manager);
    });

    btnInstrucciones=new QPushButton(vista);
    btnInstrucciones->setGeometry(270,320,285,55);
    btnInstrucciones->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });
    btnInstrucciones->show();
    connect(btnInstrucciones,&QPushButton::clicked,this,[this](){

    });

    btnRecords=new QPushButton(vista);
    btnRecords->setGeometry(270, 380, 285, 55);
    btnRecords->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });
    btnRecords->show();
    connect(btnRecords, &QPushButton::clicked,this,[this](){

    });

    btnCerrar=new QPushButton(vista);
    btnCerrar->setGeometry(270,445,285,55);
    btnCerrar->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });
    btnCerrar->show();
    connect(btnCerrar,&QPushButton::clicked,this,[this, manager, vista, escena](){
        manager->cerrarSesion();
        btnJugar->hide();
        btnInstrucciones->hide();
        btnRecords->hide();
        btnCerrar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menuInicio=new MenuInicio(escena,vista);
    });

    vista->show();
}

MenuPrincipal::~MenuPrincipal(){
    delete btnJugar;
    delete btnInstrucciones;
    delete btnRecords;
    delete btnCerrar;
}
