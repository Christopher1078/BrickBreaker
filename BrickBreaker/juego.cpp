#include "juego.h"

Juego::Juego(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager)
{
    this->escena=escena;
    this->vista=vista;

    vidas=3;
    puntos=0;
    tiempo=0;
    frames=0;

    QPixmap fondo(":/imagenes/fondo.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    crearBarraSuperior();
    actualizarBarra();

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    pelota = new Pelota();
    paleta = new Paleta();

    escena->addItem(pelota->getGrafico());
    escena->addItem(paleta->getGrafico());

    timer=new QTimer;

    QObject::connect(timer,&QTimer::timeout,this,&Juego::actualizar);

    bloques=new Bloque*[FILAS];
    for(int i=0;i<FILAS;i++){
        bloques[i]=new Bloque[COLUMNAS];
    }
}

void Juego::crearBarraSuperior(){
    txtVidas=escena->addText("VIDAS: ");
    txtPuntos=escena->addText("PUNTOS: 000000");
    txtTiempo=escena->addText("TIEMPO: 00:00");

    QFont fuente("Courier New", 14, QFont::Bold);

    txtVidas->setFont(fuente);
    txtVidas->setDefaultTextColor(Qt::white);
    txtVidas->setPos(30,10);

    txtPuntos->setFont(fuente);
    txtPuntos->setDefaultTextColor(Qt::white);
    txtPuntos->setPos(330,10);

    txtTiempo->setFont(fuente);
    txtPuntos->setDefaultTextColor(Qt::white);
    txtTiempo->setPos(630,10);
}

void Juego::iniciarTimer(){
    timer->start(16);
    vista->show();

}

void Juego::actualizar()
{
    frames++;
    if(frames>=60){
        tiempo++;
        frames=0;
        actualizarBarra();
    }
    pelota->mover();
    pelota->comprobarParedes();

    if(pelota->getGrafico()->y()>590){
        perderVida();
        return;
    }

    if (pelota->colisionaCon(paleta->getGrafico()))
    {
        float mitadPaleta=paleta->getGrafico()->boundingRect().width()/2;
        float centroPaleta=paleta->getGrafico()->x()+mitadPaleta;
        float centroPelota=pelota->getGrafico()->x()+pelota->getGrafico()->boundingRect().width()/2;
        float distancia=centroPelota-centroPaleta;
        float porcentaje=distancia/mitadPaleta;

        pelota->rebotarPaleta(porcentaje);

        float nuevaY=paleta->getGrafico()->y()-pelota->getGrafico()->boundingRect().height();
        pelota->getGrafico()->setY(nuevaY);
    }

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            if(bloques[i][j].getGrafico()!=nullptr){
                if(!bloques[i][j].estaDestruido()){
                    if(pelota->colisionaCon(bloques[i][j].getGrafico())){
                        bloques[i][j].destruir();
                        escena->removeItem(bloques[i][j].getGrafico());
                        pelota->rebotarBloque(bloques[i][j].getGrafico());
                        puntos+=50;
                        actualizarBarra();
                        return;
                    }
                }
            }
        }
    }
}

void Juego::actualizarBarra(){
    txtVidas->setPlainText("VIDAS: "+QString::number(vidas));
    txtPuntos->setPlainText("PUNTOS: "+QString("%1").arg(puntos,6,10,QChar('0')));

    int minutos=tiempo/60;
    int segundos=tiempo%60;

    txtTiempo->setPlainText(QString("TIEMPO: %1:%2").arg(minutos,2,10,QChar('0')).arg(segundos,2,10,QChar('0')));
}

void Juego::reiniciarPelota(){
    pelota->getGrafico()->setPos(390,450);
    pelota->reiniciarMovimiento();
    paleta->reiniciar();
}

void Juego::perderVida(){
    vidas--;
    if(vidas<=0){
        timer->stop();
        return;
    }
    reiniciarPelota();
}

bool Juego::eventFilter(QObject* objeto, QEvent* evento)
{

    if (evento->type() == QEvent::KeyPress)
    {
        QKeyEvent* tecla = static_cast<QKeyEvent*>(evento);

        if (tecla->key() == Qt::Key_Left || tecla->key() == Qt::Key_A)
        {
            paleta->moverIzquierda();
            return true;
        }

        if (tecla->key() == Qt::Key_Right ||tecla->key() == Qt::Key_D)
        {
            paleta->moverDerecha();
            return true;
        }
    }

    return QObject::eventFilter(objeto, evento);
}

Juego::~Juego(){
    delete pelota;
    delete paleta;
    delete timer;

}
