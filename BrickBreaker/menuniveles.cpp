#include "menuniveles.h"
#include "juego.h"
#include "menuprincipal.h"

MenuNiveles::MenuNiveles(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager) {
    QPixmap fondo(":/imagenes/menuniveles.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    btnNivel1=new QPushButton(vista);
    btnNivel1->setGeometry(70,250,138,155);
    /*btnNivel1->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });*/
    btnNivel1->show();
    connect(btnNivel1,&QPushButton::clicked,this,[this, escena, vista](){
        btnNivel1->hide();
        btnNivel2->hide();
        btnNivel3->hide();
        btnNivel4->hide();
        btnNivel5->hide();
        btnRegresar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        juego=new Juego(escena,vista);
    });

    btnNivel2=new QPushButton(vista);
    btnNivel2->setGeometry(215,250,132,155);
    /*btnNivel2->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });*/
    btnNivel2->show();
    connect(btnNivel2,&QPushButton::clicked,this,[this](){

    });

    btnNivel3=new QPushButton(vista);
    btnNivel3->setGeometry(350,250,132,155);
    /*btnNivel3->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });*/
    btnNivel3->show();
    connect(btnNivel3,&QPushButton::clicked,this,[this](){

    });

    btnNivel4=new QPushButton(vista);
    btnNivel4->setGeometry(490,250,132,155);
    /*btnNivel4->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });*/
    btnNivel4->show();
    connect(btnNivel4,&QPushButton::clicked,this,[this](){

    });

    btnNivel5=new QPushButton(vista);
    btnNivel5->setGeometry(630, 250, 132, 155);
    /*btnNivel5->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });*/
    btnNivel5->show();
    connect(btnNivel5,&QPushButton::clicked,this,[this](){

    });

    btnRegresar=new QPushButton(vista);
    btnRegresar->setGeometry(230, 500, 370, 75);
    btnRegresar->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border: none; }"
    });
    btnRegresar->show();
    connect(btnRegresar,&QPushButton::clicked,this,[this, escena, vista, manager](){
        btnNivel1->hide();
        btnNivel2->hide();
        btnNivel3->hide();
        btnNivel4->hide();
        btnNivel5->hide();
        btnRegresar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menuPrincipal=new MenuPrincipal(escena, vista, manager);
    });

    vista->show();
}
