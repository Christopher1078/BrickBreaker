#include "pantalladerrota.h"
#include "menuprincipal.h"

PantallaDerrota::PantallaDerrota(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager, int puntos, int tiempo, int bloques) {
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
    connect(btnReintentar,&QPushButton::clicked,this,[](){

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
