#include "instrucciones.h"
#include "menuprincipal.h"
#include "usermanager.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>

Instrucciones::Instrucciones(
    QGraphicsScene* escena,
    QGraphicsView* vista,
    UserManager* manager
    )
{
    this->escena = escena;
    this->vista = vista;
    this->manager = manager;

    menuPrincipal = nullptr;

    QPixmap fondo(":/imagenes/instrucciones.png");

    fondo = fondo.scaled(
        800,
        600,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    QGraphicsPixmapItem* imagen =
        escena->addPixmap(fondo);

    imagen->setZValue(-1);
    imagen->setPos(0, 0);

    QString transparente =
        "QPushButton {"
        "background: transparent;"
        "border: none;"
        "}"
        "QPushButton:pressed {"
        "background: rgba(255,255,255,25);"
        "}";

    btnRegresar =
        new QPushButton(vista->viewport());

    btnRegresar->setGeometry(
        285,   // X
        523,   // Y
        235,   // ancho
        52     // alto
        );

    btnRegresar->setStyleSheet(
        transparente
        );

    btnRegresar->setCursor(
        Qt::PointingHandCursor
        );

    btnRegresar->setFocusPolicy(
        Qt::NoFocus
        );

    btnRegresar->show();
    btnRegresar->raise();

    connect(
        btnRegresar,
        &QPushButton::clicked,
        this,
        [this]()
        {
            btnRegresar->hide();

            this->escena->clear();

            menuPrincipal =
                new MenuPrincipal(
                    this->escena,
                    this->vista,
                    this->manager
                    );
        }
        );

    vista->show();
}

Instrucciones::~Instrucciones()
{
    delete btnRegresar;
}