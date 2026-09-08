#include "pantalladerrota.h"
#include "menuprincipal.h"
#include "nivel1.h"
#include "nivel2.h"
#include "nivel3.h"
#include "nivel4.h"
#include "nivel5.h"

PantallaDerrota::PantallaDerrota(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager, int puntos, int tiempo, int bloques, int nivel) {
    QPixmap fondo(":/imagenes/derrota.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    QFont fuente("Courier New", 20, QFont::Bold);

    txtPuntos=escena->addText(QString("%1").arg(puntos,4,10,QChar('0')));
    txtPuntos->setFont(fuente);
    txtPuntos->setDefaultTextColor(Qt::white);
    txtPuntos->setPos(380,200);

    int minutos=tiempo/60;
    int segundos=tiempo%60;

    txtTiempo=escena->addText(QString("%1:%2").arg(minutos,2,10,QChar('0')).arg(segundos,2,10,QChar('0')));
    txtTiempo->setFont(fuente);
    txtTiempo->setDefaultTextColor(Qt::white);
    txtTiempo->setPos(380, 257);

    txtBloques=escena->addText(QString("%1").arg(bloques,2,10,QChar('0')));
    txtBloques->setFont(fuente);
    txtBloques->setDefaultTextColor(Qt::white);
    txtBloques->setPos(380,310);

    btnReintentar=new QPushButton(vista);
    btnReintentar->setGeometry(55,440,349,85);
    btnReintentar->show();
    connect(btnReintentar,&QPushButton::clicked,this,[this, escena, vista, nivel, manager](){
        btnReintentar->hide();
        btnVolver->hide();
        escena->clear();
        vista->removeEventFilter(this);
        switch(nivel){
        case 0:{
            nivel1=new Nivel1(escena, vista, manager);
            break;
        }
        case 1:{
            nivel2=new Nivel2(escena,vista,manager);
            break;
        }
        case 2:{
            nivel3=new Nivel3(escena,vista,manager);
            break;
        }
        case 3:{
            nivel4=new Nivel4(escena,vista,manager);
            break;
        }
        case 4:{
            nivel5=new Nivel5(escena,vista,manager);
            break;
        }
        }
    });

    btnVolver=new QPushButton(vista);
    btnVolver->setGeometry(420, 440, 350, 85);
    btnVolver->show();
    connect(btnVolver,&QPushButton::clicked,this,[this, escena, vista, manager](){
        btnReintentar->hide();
        btnVolver->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menuPrincipal=new MenuPrincipal(escena,vista,manager);
    });

    vista->show();
}

PantallaDerrota::~PantallaDerrota(){
    delete btnVolver;
    delete btnReintentar;
    delete txtTiempo;
    delete txtBloques;
    delete txtPuntos;
}
