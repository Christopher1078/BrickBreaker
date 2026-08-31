#include "crearcuenta.h"
#include "menuinicio.h"
#include "menuprincipal.h"

#include <QEvent>
#include <QKeyEvent>

CrearCuenta::CrearCuenta(QGraphicsScene* escena, QGraphicsView* vista){
    manager=new UserManager;

    QPixmap fondo (":/imagenes/crearcuenta.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    txtNombre=new QLineEdit(vista);
    txtNombre->setGeometry(250,255,280,50);
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
    txtPassword->setGeometry(250, 320, 280, 50);
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
    connect(btnCrear,&QPushButton::clicked,this,[this, vista, escena]{
        string nombre=txtNombre->text().toStdString();
        string password=txtPassword->text().toStdString();

        if(nombre.empty() || password.empty()){
            MessageBox(NULL,TEXT("NO PUEDE HABER PARAMETROS VACIOS"),TEXT("ERROR"),MB_OK);
        }else if(manager->crearCuenta(nombre, password)){
            txtNombre->hide();
            txtPassword->hide();
            btnCrear->hide();
            btnRegresar->hide();
            btnMostrar->hide();
            escena->clear();
            vista->removeEventFilter(this);
            menuPrincipal=new MenuPrincipal(escena, vista, manager);
        }
    });

    btnRegresar=new QPushButton(vista);
    btnRegresar->setGeometry(290,452,245,45);
    btnRegresar->setStyleSheet({
       "QPushButton {"
       "background-color: transparent;"
       "border:none }"
    });
    btnRegresar->raise();
    btnRegresar->show();
    connect(btnRegresar,&QPushButton::clicked,this,[this, vista, escena]{
        btnRegresar->hide();
        btnCrear->hide();
        btnMostrar->hide();
        txtPassword->hide();
        txtNombre->hide();
        vista->removeEventFilter(this);
        menu=new MenuInicio(escena,vista);
    });

    btnMostrar=new QPushButton(vista);
    btnMostrar->setGeometry(530,332,35,30);
    btnMostrar->setStyleSheet({
       "QPushButton {"
       "background-color: transparent;"
       "border: none; }"
    });
    btnMostrar->setIcon(QIcon(":/imagenes/ojo2.png"));
    btnMostrar->setIconSize(QSize(35,30));
    btnMostrar->raise();
    btnMostrar->show();
    connect(btnMostrar,&QPushButton::clicked,this,[this, escena](){
        if(txtPassword->echoMode()==QLineEdit::Password){
            txtPassword->setEchoMode(QLineEdit::Normal);
            btnMostrar->setIcon(QIcon(":imagenes/ojo1.png"));
        }else{
            txtPassword->setEchoMode(QLineEdit::Password);
            btnMostrar->setIcon(QIcon(":imagenes/ojo2.png"));
        }
    });

    vista->show();
}

