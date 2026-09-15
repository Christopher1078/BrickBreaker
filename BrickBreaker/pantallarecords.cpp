#include "pantallarecords.h"
#include "menuprincipal.h"

PantallaRecords::PantallaRecords(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager) {
    QPixmap fondo(":/imagenes/Records.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    QFont fuente("Courier New", 20, QFont::Bold);

    nivel1=escena->addText(QString("Nivel 1           %1").arg(manager->getActual()->getMejorPuntaje(0),4,10,QChar('0')));
    nivel1->setFont(fuente);
    nivel1->setDefaultTextColor(Qt::white);
    nivel1->setPos(220,256);

    nivel2=escena->addText(QString("Nivel 2           %1").arg(manager->getActual()->getMejorPuntaje(1),4,10,QChar('0')));
    nivel2->setFont(fuente);
    nivel2->setDefaultTextColor(Qt::white);
    nivel2->setPos(220,298);

    nivel3=escena->addText(QString("Nivel 3           %1").arg(manager->getActual()->getMejorPuntaje(2),4,10,QChar('0')));
    nivel3->setFont(fuente);
    nivel3->setDefaultTextColor(Qt::white);
    nivel3->setPos(220,337);

    nivel4=escena->addText(QString("Nivel 4           %1").arg(manager->getActual()->getMejorPuntaje(3),4,10,QChar('0')));
    nivel4->setFont(fuente);
    nivel4->setDefaultTextColor(Qt::white);
    nivel4->setPos(220,375);

    nivel5=escena->addText(QString("Nivel 5           %1").arg(manager->getActual()->getMejorPuntaje(4),4,10,QChar('0')));
    nivel5->setFont(fuente);
    nivel5->setDefaultTextColor(Qt::white);
    nivel5->setPos(220,415);

    btnRegresar=new QPushButton(vista);
    btnRegresar->setGeometry(298,480,223,35);
    btnRegresar->show();
    connect(btnRegresar, &QPushButton::clicked,this,[this, escena, vista, manager]{
        nivel1->hide();
        nivel2->hide();
        nivel3->hide();
        nivel4->hide();
        nivel5->hide();
        btnRegresar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menuPrincipal=new MenuPrincipal(escena, vista, manager);
    });

    vista->show();
}

PantallaRecords::~PantallaRecords(){
    delete nivel1;
    delete nivel2;
    delete nivel3;
    delete nivel4;
    delete nivel5;
    delete btnRegresar;
}
