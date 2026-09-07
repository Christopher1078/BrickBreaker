#include "menuniveles.h"
#include "menuprincipal.h"
#include "nivel1.h"
#include "nivel2.h"
#include "nivel3.h"

MenuNiveles::MenuNiveles(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager) {
    QPixmap fondo(":/imagenes/menuniveles.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);


    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    int estrellas1=manager->getActual()->getEstrellas(0);
    int estrellas2=manager->getActual()->getEstrellas(1);
    int estrellas3=manager->getActual()->getEstrellas(2);
    int estrellas4=manager->getActual()->getEstrellas(3);
    int estrellas5=manager->getActual()->getEstrellas(4);

    btnNivel1=new QPushButton(vista);
    btnNivel1->setGeometry(70,250,138,155);
    btnNivel1->show();
    connect(btnNivel1,&QPushButton::clicked,this,[this, escena, vista, manager](){
        btnNivel1->hide();
        btnNivel2->hide();
        btnNivel3->hide();
        btnNivel4->hide();
        btnNivel5->hide();
        btnRegresar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        nivel1=new Nivel1(escena,vista, manager);
    });

    btnNivel2=new QPushButton(vista);
    btnNivel2->setGeometry(215,250,132,155);
    btnNivel2->show();
    connect(btnNivel2,&QPushButton::clicked,this,[this, escena, vista, manager](){
        if(manager->getActual()->isPasado(1)){
            btnNivel1->hide();
            btnNivel2->hide();
            btnNivel3->hide();
            btnNivel4->hide();
            btnNivel5->hide();
            btnRegresar->hide();

            escena->clear();

            vista->removeEventFilter(this);

            nivel2 = new Nivel2(escena,vista,manager);
        }
    });

    btnNivel3=new QPushButton(vista);
    btnNivel3->setGeometry(350,250,132,155);
    btnNivel3->show();
    connect(btnNivel3,&QPushButton::clicked,this,[this, escena, vista, manager](){
        if(manager->getActual()->isPasado(2)){
            btnNivel1->hide();
            btnNivel2->hide();
            btnNivel3->hide();
            btnNivel4->hide();
            btnNivel5->hide();
            btnRegresar->hide();

            escena->clear();

            vista->removeEventFilter(this);

            nivel3 = new Nivel3(escena,vista, manager);
        }
    });

    btnNivel4=new QPushButton(vista);
    btnNivel4->setGeometry(490,250,132,155);
    btnNivel4->show();
    connect(btnNivel4,&QPushButton::clicked,this,[this, manager](){
        if(manager->getActual()->isPasado(3)){

        }
    });

    btnNivel5=new QPushButton(vista);
    btnNivel5->setGeometry(630, 250, 132, 155);
    btnNivel5->show();
    connect(btnNivel5,&QPushButton::clicked,this,[this, manager](){
        if(manager->getActual()->isPasado(4)){

        }
    });

    switch(estrellas1){
        case 0:{
            btnNivel1->setIcon(QIcon(":/imagenes/1-0.png"));
            break;
        }
        case 1:{
            btnNivel1->setIcon(QIcon(":/imagenes/1-1.png"));
            break;
        }
        case 2:{
            btnNivel1->setIcon(QIcon(":/imagenes/1-2.png"));
            break;
        }
        case 3:{
            btnNivel1->setIcon(QIcon(":/imagenes/1-3.png"));
            break;
        }
    }
    btnNivel1->setIconSize(QSize(138,155));

    if(!manager->getActual()->isPasado(1)){
        btnNivel2->setIcon(QIcon(":/imagenes/2.png"));
    }else{
        switch(estrellas2){
            case 0:{
                btnNivel2->setIcon(QIcon(":/imagenes/2-0.png"));
                break;
            }
            case 1:{
                btnNivel2->setIcon(QIcon(":/imagenes/2-1.png"));
                break;
            }
            case 2:{
                btnNivel2->setIcon(QIcon(":/imagenes/2-2.png"));
                break;
            }
            case 3:{
                btnNivel2->setIcon(QIcon(":/imagenes/2-3.png"));
                break;
            }
        }
    }
    btnNivel2->setIconSize(QSize(138,155));

    if(!manager->getActual()->isPasado(2)){
        btnNivel3->setIcon(QIcon(":/imagenes/3.png"));
    }else{
        switch(estrellas3){
            case 0:{
                btnNivel3->setIcon(QIcon(":/imagenes/3-0.png"));
                break;
            }
            case 1:{
                btnNivel3->setIcon(QIcon(":/imagenes/3-1.png"));
                break;
            }
            case 2:{
                btnNivel3->setIcon(QIcon(":/imagenes/3-2.png"));
                break;
            }
            case 3:{
                btnNivel3->setIcon(QIcon(":/imagenes/3-3.png"));
                break;
            }
        }
    }
    btnNivel3->setIconSize(QSize(138,155));

    if(!manager->getActual()->isPasado(3)){
        btnNivel4->setIcon(QIcon(":/imagenes/4.png"));
    }else{
        switch(estrellas4){
            case 0:{
                btnNivel4->setIcon(QIcon(":/imagenes/4-0.png"));
                break;
            }
            case 1:{
                btnNivel4->setIcon(QIcon(":/imagenes/4-1.png"));
                break;
            }
            case 2:{
                btnNivel4->setIcon(QIcon(":/imagenes/4-2.png"));
                break;
            }
            case 3:{
                btnNivel4->setIcon(QIcon(":/imagemes/4-3.png"));
                break;
            }
        }
    }
    btnNivel4->setIconSize(QSize(138,155));

    if(!manager->getActual()->isPasado(4)){
        btnNivel5->setIcon(QIcon(":/imagenes/5.png"));
    }else{
        switch(estrellas5){
            case 0:{
                btnNivel5->setIcon(QIcon(":/imagenes/5-0.png"));
                break;
            }
            case 1:{
                btnNivel5->setIcon(QIcon(":/imagenes/5-1.png"));
                break;
            }
            case 2:{
                btnNivel5->setIcon(QIcon(":/imagenes/5-2.png"));
                break;
            }
            case 3:{
                btnNivel5->setIcon(QIcon(":/imagenes/5-3.png"));
                break;
            }
        }
    }
    btnNivel5->setIconSize(QSize(138,155));

    btnRegresar=new QPushButton(vista);
    btnRegresar->setGeometry(230, 500, 370, 75);
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

MenuNiveles::~MenuNiveles(){
    delete btnNivel1;
    delete btnNivel2;
    delete btnNivel3;
    delete btnNivel4;
    delete btnNivel5;
    delete btnRegresar;
}
