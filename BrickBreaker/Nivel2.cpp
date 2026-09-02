#include "nivel2.h"

Nivel2::Nivel2(QGraphicsScene* escena, QGraphicsView* vista)
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

    // Timer
    timer = new QTimer(this);

    connect(
        timer,
        &QTimer::timeout,
        this,
        &Nivel2::actualizar
        );

    timer->start(16);
}



void Nivel2::crearBloque(
    int columna,
    int fila,
    const QString& imagen
    )
{
    const int ancho = 55;
    const int alto = 25;

    const int separacionX = 4;
    const int separacionY = 4;

    // Vamos a trabajar con 10 columnas
    const int columnas = 10;

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



void Nivel2::crearBloques()
{


    for (int columna = 0; columna < 10; columna++)
    {
        crearBloque(
            columna,
            0,
            ":/imagenes/bloque_rojo.png"
            );
    }




    for (int columna = 0; columna < 10; columna++)
    {
        crearBloque(
            columna,
            1,
            ":/imagenes/bloque_rojo.png"
            );
    }




    for (int columna = 0; columna < 4; columna++)
    {
        crearBloque(
            columna,
            2,
            ":/imagenes/bloque_naranja.png"
            );
    }

    for (int columna = 6; columna < 10; columna++)
    {
        crearBloque(
            columna,
            2,
            ":/imagenes/bloque_naranja.png"
            );
    }




    for (int columna = 0; columna < 3; columna++)
    {
        crearBloque(
            columna,
            3,
            ":/imagenes/bloque_verde.png"
            );
    }

    for (int columna = 7; columna < 10; columna++)
    {
        crearBloque(
            columna,
            3,
            ":/imagenes/bloque_verde.png"
            );
    }



    for (int columna = 0; columna < 2; columna++)
    {
        crearBloque(
            columna,
            4,
            ":/imagenes/bloque_azul.png"
            );
    }

    for (int columna = 8; columna < 10; columna++)
    {
        crearBloque(
            columna,
            4,
            ":/imagenes/bloque_azul.png"
            );
    }



    crearBloque(
        0,
        5,
        ":/imagenes/bloque_morado.png"
        );

    crearBloque(
        9,
        5,
        ":/imagenes/bloque_morado.png"
        );
}




void Nivel2::actualizar()
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




bool Nivel2::eventFilter(
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


Nivel2::~Nivel2()
{
    if (timer)
    {
        timer->stop();
    }

    vista->removeEventFilter(this);

    delete pelota;
    delete paleta;
}