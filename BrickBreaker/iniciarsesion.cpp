#include "iniciarsesion.h"
#include "menuinicio.h"
#include "menuprincipal.h"

IniciarSesion::IniciarSesion(QGraphicsScene *escena, QGraphicsView *vista) {
    manager=new UserManager;

    QPixmap fondo(":/imagenes/iniciarsesion.png");
    fondo=fondo.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    txtNombre=new QLineEdit(vista);
    txtNombre->setGeometry(250, 273, 280, 50);
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
    txtNombre->show();

    txtPassword=new QLineEdit(vista);
    txtPassword->setGeometry(250, 335, 280, 50);
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
    txtPassword->show();

    btnIniciar=new QPushButton(vista);
    btnIniciar->setGeometry(255,400,315,55);
    btnIniciar->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border:none;"
        "color:transparent; }"
    });
    btnIniciar->show();
    connect(btnIniciar, &QPushButton::clicked,this,[this, escena, vista](){
        string nombre=txtNombre->text().toStdString();
        string password=txtPassword->text().toStdString();

        if(nombre.empty() || password.empty()){
            MessageBox(NULL,TEXT("NO PUEDE HABER PARAMETROS VACIOS"),TEXT("ERROR"),MB_OK);
        }else if(manager->iniciarSesion(nombre,password)){
            txtNombre->hide();
            txtPassword->hide();
            btnIniciar->hide();
            btnRegresar->hide();
            btnMostrar->hide();
            escena->clear();
            vista->removeEventFilter(this);
            menuPrincipal=new MenuPrincipal(escena,vista,manager);
        }
    });

    btnRegresar=new QPushButton(vista);
    btnRegresar->setGeometry(290,467,245,45);
    btnRegresar->setStyleSheet({
        "QPushButton {"
        "background-color: transparent;"
        "border:none;"
        "color:transparent; }"
    });
    btnRegresar->show();
    connect(btnRegresar,&QPushButton::clicked,this,[this, escena, vista](){
        txtNombre->hide();
        txtPassword->hide();
        btnIniciar->hide();
        btnRegresar->hide();
        btnMostrar->hide();
        escena->clear();
        vista->removeEventFilter(this);
        menu=new MenuInicio(escena, vista);
    });

    btnMostrar=new QPushButton(vista);
    btnMostrar->setGeometry(530,345,35,30);
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

IniciarSesion::~IniciarSesion(){
    delete txtNombre;
    delete txtPassword;
    delete btnIniciar;
    delete btnMostrar;
    delete btnRegresar;
}
