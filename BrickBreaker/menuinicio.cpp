#include "menuinicio.h"

MenuInicio::MenuInicio() {
    escena = new QGraphicsScene();

    escena->setSceneRect(0, 0, 800, 600);
    escena->setBackgroundBrush(QColor(10, 10, 20));

    vista = new QGraphicsView(escena);
    vista->setFixedSize(820, 620);
    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    QGraphicsTextItem* titulo =escena->addText("BRICK BREAKER");
    titulo->setDefaultTextColor(QColor(40, 220, 255));

    QFont fuenteTitulo("Courier New", 32, QFont::Bold);
    titulo->setFont(fuenteTitulo);

    titulo->setPos(235, 120);

    QGraphicsTextItem* inicioSesion = escena->addText("[ INICIAR SESION ]");

    inicioSesion->setDefaultTextColor(Qt::white);

    QFont fuenteBoton("Courier New", 20, QFont::Bold);
    inicioSesion->setFont(fuenteBoton);

    inicioSesion->setPos(260, 280);

    QGraphicsTextItem* crearCuenta=escena->addText("[ CREAR CUENTA ]");

    crearCuenta->setDefaultTextColor(Qt::white);
    crearCuenta->setFont(fuenteBoton);

    crearCuenta->setPos(275, 340);

    QGraphicsTextItem* salir = escena->addText("[ SALIR ]");

    salir->setDefaultTextColor(Qt::white);
    salir->setFont(fuenteBoton);

    salir->setPos(325, 400);


    QGraphicsTextItem* instrucciones = escena->addText("PRESIONA ENTER PARA JUGAR");

    instrucciones->setDefaultTextColor(QColor(180, 180, 180));

    QFont fuenteInstrucciones("Courier New", 12);
    instrucciones->setFont(fuenteInstrucciones);

    instrucciones->setPos(275, 510);

    vista->show();
}

bool MenuInicio::eventFilter(QObject* objeto, QEvent* evento){
    if(evento->type()==QEvent::KeyPress){
        QKeyEvent* tecla=static_cast<QKeyEvent*>(evento);
        if(tecla->key()==Qt::Key_Enter || tecla->key()==Qt::Key_Return){
            escena->clear();
            vista->removeEventFilter(this);
            juego=new Juego(escena,vista);
        }
        return true;
    }
    return QObject::eventFilter(objeto,evento);
}


