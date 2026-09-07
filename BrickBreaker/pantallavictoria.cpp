#include "pantallavictoria.h"
#include "menuprincipal.h"

PantallaVictoria::PantallaVictoria(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager, int puntosFinal, int base, int bonusTiempo, int bonusVida, int estrellas) {
    QPixmap fondo(":/imagenes/victoria.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    QFont fuente("Courier New", 20, QFont::Bold);

    for(int i=0;i<estrellas;i++){
        QPixmap estrellaFoto(":/imagenes/estrellas.png");
        estrellaFoto=estrellaFoto.scaled(310,310,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        estrella[i]=escena->addPixmap(estrellaFoto);
        estrella[i]->setPos(85+i*163,20);
    }

    txtBase=escena->addText(QString("%1").arg(base,4,10,QChar('0')));
    txtBase->setFont(fuente);
    txtBase->setDefaultTextColor(Qt::white);
    txtBase->setPos(350,250);

    txtVidas=escena->addText(QString("%1").arg(bonusVida,4,10,QChar('0')));
    txtVidas->setFont(fuente);
    txtVidas->setDefaultTextColor(Qt::white);
    txtVidas->setPos(350,287);

    txtTiempo=escena->addText(QString("%1").arg(bonusTiempo,4,10,QChar('0')));
    txtTiempo->setFont(fuente);
    txtTiempo->setDefaultTextColor(Qt::white);
    txtTiempo->setPos(350,325);

    txtFinal=escena->addText(QString("%1").arg(puntosFinal,4,10,QChar('0')));
    txtFinal->setFont(fuente);
    txtFinal->setDefaultTextColor(Qt::white);
    txtFinal->setPos(350,385);

    btnSiguiente=new QPushButton(vista);
    btnSiguiente->setGeometry(72,477,330,75);
    btnSiguiente->show();
    connect(btnSiguiente,&QPushButton::clicked,this,[](){

    });

    btnVolver=new QPushButton(vista);
    btnVolver->setGeometry(420, 477, 330, 75);
    btnVolver->show();
    connect(btnVolver,&QPushButton::clicked,this,[this, escena, vista, manager](){
        btnSiguiente->hide();
        btnVolver->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menuPrincipal=new MenuPrincipal(escena,vista,manager);
    });

    vista->show();
}

PantallaVictoria::~PantallaVictoria(){
    delete btnSiguiente;
    delete btnVolver;
    delete txtFinal;
    delete txtTiempo;
    delete txtBase;
    delete txtVidas;
    for(int i=0;i<3;i++){
        delete estrella[i];
    }
}
