#include "crearcuenta.h"

#include <QEvent>
#include <QKeyEvent>

CrearCuenta::CrearCuenta(QGraphicsScene* escena, QGraphicsView* vista){
    this->escena=escena;
    this->vista=vista;

    escena->setSceneRect(0,0,800,600);

    QPixmap fondo (":/imagenes/crearcuenta.png");

    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    txtNombre=new QLineEdit(vista);
    txtNombre->setGeometry(250,255,280,50);
    txtNombre->setFocusPolicy(Qt::StrongFocus);
    txtNombre->setStyleSheet({
        "QLineEdit {"
        "background-color: transparent;"
        "border:none;"
        "color: white;"
        "font-family:'Courier New';"
        "font-size: 18px;"
        "font-weight: bold;"
        "padding-left: 50px; }"
    });
    txtNombre->raise();
    txtNombre->show();

    txtPassword=new QLineEdit(vista);
    txtPassword->setGeometry(250, 315, 280, 50);
    txtPassword->setFocusPolicy(Qt::StrongFocus);
    txtPassword->setEchoMode(QLineEdit::Password);
    txtPassword->setStyleSheet({
        "QLineEdit {"
        "background-color: transparent;"
        "border:none;"
        "color: white;"
        "font-family:'Courier New';"
        "font-size: 18px;"
        "font-weight: bold;"
        "padding-left: 50px; }"
    });
    txtPassword->raise();
    txtPassword->show();

    btnCrear=new QPushButton(vista);
    btnCrear->setGeometry(255,382,310,55);
    btnCrear->setStyleSheet({
       "QPushButton {"
       "background-color: transparent;"
       "border:none;"
       "color:transparent; }"
    });
    btnCrear->raise();
    btnCrear->show();

    btnRegresar=new QPushButton(vista);
    btnRegresar->setGeometry(290,452,245,45);
    btnRegresar->setStyleSheet({
       "QPushButton {"
       "background-color: transparent;"
       "border:none }"
    });
    btnRegresar->raise();
    btnRegresar->show();

    vista->show();
}

