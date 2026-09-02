#include "juego.h"

Juego::Juego(QGraphicsScene* escena, QGraphicsView* vista)
{
    this->escena=escena;
    this->vista=vista;

    QPixmap fondo(":/imagenes/fondo.png");
    fondo=fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QGraphicsPixmapItem* imagen=escena->addPixmap(fondo);
    imagen->setZValue(-1);
    imagen->setPos(0,0);

    escena->setSceneRect(0, 0, 800, 600);
    escena->setBackgroundBrush(QColor(10, 10, 20));

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    pelota = new Pelota();
    paleta = new Paleta();

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            float x=j*90+40;
            float y=i*35+40;

            QColor color;

            if (i == 0){
                color = QColor(255, 50, 50);
            }
            else if (i == 1){
                color = QColor(255, 180, 40);
            }
            else{
                color = QColor(50, 150, 255);
            }

            bloques[i][j]=new Bloque(x,y, color);

            escena->addItem(bloques[i][j]->getGrafico());
        }
    }

    escena->addItem(pelota->getGrafico());
    escena->addItem(paleta->getGrafico());

    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, this, &Juego::actualizar);

    timer->start(16);

    //vista->show();
}

void Juego::actualizar()
{
    pelota->mover();
    pelota->comprobarParedes();

    if (pelota->colisionaCon(paleta->getGrafico()))
    {
        pelota->rebotarVertical();
    }

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            if(!bloques[i][j]->estaDestruido()){
                if(pelota->colisionaCon(bloques[i][j]->getGrafico())){
                    bloques[i][j]->destruir();
                    escena->removeItem(bloques[i][j]->getGrafico());
                    pelota->rebotarVertical();
                    return;
                }
            }
        }
    }
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
}
