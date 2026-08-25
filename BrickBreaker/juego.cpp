#include "juego.h"

Juego::Juego()
{
    escena = new QGraphicsScene();

    escena->setSceneRect(0, 0, 800, 600);

    vista = new QGraphicsView(escena);
    vista->setFixedSize(820, 620);
    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    pelota = new Pelota();
    paleta = new Paleta();

    escena->addItem(pelota->getGrafico());
    escena->addItem(paleta->getGrafico());

    timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, this, &Juego::actualizar);

    timer->start(16);

    vista->show();
}

void Juego::actualizar()
{
    pelota->mover();

    pelota->comprobarParedes();

    if (pelota->colisionaCon(paleta->getGrafico()) && pelota->estaBajando())
    {
        pelota->rebotarVertical();
    }
}

bool Juego::eventFilter(QObject* objeto, QEvent* evento)
{
    if (evento->type() == QEvent::KeyPress)
    {
        QKeyEvent* tecla = static_cast<QKeyEvent*>(evento);

        if (tecla->key() == Qt::Key_Left ||
            tecla->key() == Qt::Key_A)
        {
            paleta->moverIzquierda();
        }

        if (tecla->key() == Qt::Key_Right ||
            tecla->key() == Qt::Key_D)
        {
            paleta->moverDerecha();
        }

        return true;
    }

    return QObject::eventFilter(objeto, evento);
}
