#include "Nivel3.h"

Nivel3::Nivel3(QGraphicsScene* escena, QGraphicsView* vista)
{
    this->escena = escena;
    this->vista = vista;

    QPixmap fondo(":/imagenes/fondo.png");

    fondo = fondo.scaled(
        800,
        600,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    QGraphicsPixmapItem* imagenFondo =
        escena->addPixmap(fondo);

    imagenFondo->setZValue(-1);
    imagenFondo->setPos(0, 0);

    escena->setSceneRect(0, 0, 800, 600);

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    pelota = new Pelota();
    paleta = new Paleta();

    crearBloques();

    escena->addItem(pelota->getGrafico());
    escena->addItem(paleta->getGrafico());

    timer = new QTimer(this);

    connect(
        timer,
        &QTimer::timeout,
        this,
        &Nivel3::actualizar
        );

    timer->start(16);
}

void Nivel3::crearBloque(
    int columna,
    int fila,
    const QString& imagen
    )
{
    const int ancho = 45;
    const int alto = 24;

    const int separacionX = 3;
    const int separacionY = 3;

    const int columnas = 15;

    const int anchoTotal =
        columnas * ancho +
        (columnas - 1) * separacionX;

    const int xInicial =
        (800 - anchoTotal) / 2;

    const int yInicial = 25;

    QPixmap textura(imagen);

    textura = textura.scaled(
        ancho,
        alto,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    QGraphicsPixmapItem* grafico =
        new QGraphicsPixmapItem(textura);

    int x =
        xInicial +
        columna * (ancho + separacionX);

    int y =
        yInicial +
        fila * (alto + separacionY);

    grafico->setPos(x, y);

    escena->addItem(grafico);

    bloques.append({
        grafico,
        false
    });
}

void Nivel3::crearBloques()
{
    QString colorBloque =
        ":/imagenes/bloque_rojo.png";

    crearBloque(2, 0, colorBloque);
    crearBloque(3, 0, colorBloque);

    crearBloque(6, 0, colorBloque);

    crearBloque(8, 0, colorBloque);

    crearBloque(11, 0, colorBloque);
    crearBloque(12, 0, colorBloque);

    crearBloque(1, 1, colorBloque);
    crearBloque(2, 1, colorBloque);

    crearBloque(6, 1, colorBloque);
    crearBloque(7, 1, colorBloque);
    crearBloque(8, 1, colorBloque);

    crearBloque(12, 1, colorBloque);
    crearBloque(13, 1, colorBloque);

    for (int columna = 0; columna < 15; columna++)
    {
        crearBloque(
            columna,
            2,
            colorBloque
            );
    }

    for (int columna = 0; columna < 15; columna++)
    {
        crearBloque(
            columna,
            3,
            colorBloque
            );
    }

    crearBloque(0, 4, colorBloque);
    crearBloque(1, 4, colorBloque);

    crearBloque(3, 4, colorBloque);

    crearBloque(5, 4, colorBloque);
    crearBloque(6, 4, colorBloque);
    crearBloque(7, 4, colorBloque);
    crearBloque(8, 4, colorBloque);
    crearBloque(9, 4, colorBloque);

    crearBloque(11, 4, colorBloque);

    crearBloque(13, 4, colorBloque);
    crearBloque(14, 4, colorBloque);

    crearBloque(1, 5, colorBloque);

    crearBloque(6, 5, colorBloque);
    crearBloque(7, 5, colorBloque);
    crearBloque(8, 5, colorBloque);

    crearBloque(13, 5, colorBloque);

    crearBloque(2, 6, colorBloque);

    crearBloque(7, 6, colorBloque);

    crearBloque(12, 6, colorBloque);
}

void Nivel3::actualizar()
{
    pelota->mover();

    pelota->comprobarParedes();

    if (
        pelota->estaBajando() &&
        pelota->colisionaCon(
            paleta->getGrafico()
            )
        )
    {
        pelota->rebotarVertical();
    }

    for (int i = 0; i < bloques.size(); i++)
    {
        if (
            !bloques[i].destruido &&
            pelota->colisionaCon(
                bloques[i].grafico
                )
            )
        {
            bloques[i].destruido = true;

            escena->removeItem(
                bloques[i].grafico
                );

            pelota->rebotarVertical();

            return;
        }
    }
}

bool Nivel3::eventFilter(
    QObject* objeto,
    QEvent* evento
    )
{
    if (evento->type() == QEvent::KeyPress)
    {
        QKeyEvent* tecla =
            static_cast<QKeyEvent*>(evento);

        if (
            tecla->key() == Qt::Key_Left ||
            tecla->key() == Qt::Key_A
            )
        {
            paleta->moverIzquierda();

            return true;
        }

        if (
            tecla->key() == Qt::Key_Right ||
            tecla->key() == Qt::Key_D
            )
        {
            paleta->moverDerecha();

            return true;
        }
    }

    return QObject::eventFilter(
        objeto,
        evento
        );
}

Nivel3::~Nivel3()
{
    if (timer)
    {
        timer->stop();
    }

    vista->removeEventFilter(this);

    delete pelota;
    delete paleta;
}
