#include "music.h"

#include "audiomanager.h"
#include "menuprincipal.h"
#include "usermanager.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>

Music::Music(
    QGraphicsScene* escena,
    QGraphicsView* vista,
    UserManager* manager
    )
{
    this->escena = escena;
    this->vista = vista;
    this->manager = manager;

    menuPrincipal = nullptr;

    QPixmap fondo(":/imagenes/musica.png");

    fondo = fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen =escena->addPixmap(fondo);

    imagen->setPos(0, 0);
    imagen->setZValue(-1);

    QString transparente =
        "QPushButton {"
        "background: transparent;"
        "border: none;"
        "}"
        "QPushButton:pressed {"
        "background: rgba(255,255,255,25);"
        "}";

    btnMusicaMenos = new QPushButton(vista->viewport());

    btnMusicaMenos->setGeometry(265,190,38,38);

    btnMusicaMenos->setStyleSheet(transparente);

    btnMusicaMenos->setCursor(Qt::PointingHandCursor );

    btnMusicaMenos->setFocusPolicy(
        Qt::NoFocus
        );

    btnMusicaMenos->show();
    btnMusicaMenos->raise();

    btnMusicaMas =
        new QPushButton(vista->viewport());

    btnMusicaMas->setGeometry(510,190,38,38);

    btnMusicaMas->setStyleSheet(transparente);

    btnMusicaMas->setCursor(
        Qt::PointingHandCursor
        );

    btnMusicaMas->setFocusPolicy(
        Qt::NoFocus
        );

    btnMusicaMas->show();
    btnMusicaMas->raise();

    btnEfectosMenos =
        new QPushButton(vista->viewport());

    btnEfectosMenos->setGeometry(265,310,38,38);

    btnEfectosMenos->setStyleSheet(
        transparente
        );

    btnEfectosMenos->setCursor(
        Qt::PointingHandCursor
        );

    btnEfectosMenos->setFocusPolicy(
        Qt::NoFocus
        );

    btnEfectosMenos->show();
    btnEfectosMenos->raise();

    btnEfectosMas =
        new QPushButton(vista->viewport());

    btnEfectosMas->setGeometry(510,310,38,38);

    btnEfectosMas->setStyleSheet(
        transparente
        );

    btnEfectosMas->setCursor(
        Qt::PointingHandCursor
        );

    btnEfectosMas->setFocusPolicy(
        Qt::NoFocus
        );

    btnEfectosMas->show();
    btnEfectosMas->raise();

    lblMusica =
        new QLabel(vista->viewport());

    lblMusica->setGeometry(560,200,64,30
        );

    lblMusica->setAlignment(
        Qt::AlignCenter
        );

    lblMusica->setStyleSheet(
        "QLabel {"
        "background: rgb(0, 11, 56);"
        "color: #35DEFF;"
        "font: bold 18px 'Courier New';"
        "border: none;"
        "border-radius: 3px;"
        "}"
        );

    lblMusica->setAttribute(
        Qt::WA_TransparentForMouseEvents
        );

    lblMusica->show();
    lblMusica->raise();

    lblEfectos = new QLabel(vista->viewport());

    lblEfectos->setGeometry( 560,320, 64, 30 );

    lblEfectos->setAlignment(
        Qt::AlignCenter
        );

    lblEfectos->setStyleSheet(
        "QLabel {"
        "background: rgb(14, 1, 57);"
        "color: #FF54FA;"
        "font: bold 18px 'Courier New';"
        "border: none;"
        "border-radius: 3px;"
        "}"
        );

    lblEfectos->setAttribute(
        Qt::WA_TransparentForMouseEvents
        );

    lblEfectos->show();
    lblEfectos->raise();

    btnMute =
        new QPushButton(vista->viewport());

    btnMute->setGeometry(260,382,280,60
                         );

    btnMute->setCursor(
        Qt::PointingHandCursor
        );

    btnMute->setFocusPolicy(
        Qt::NoFocus
        );

    btnMute->show();
    btnMute->raise();

    btnVolver =
        new QPushButton(vista->viewport());

    btnVolver->setGeometry(260,452,280,60);

    btnVolver->setStyleSheet(transparente);

    btnVolver->setCursor( Qt::PointingHandCursor );

    btnVolver->setFocusPolicy(Qt::NoFocus );

    btnVolver->show();
    btnVolver->raise();

    connect(
        btnMusicaMenos,
        &QPushButton::clicked,
        this,
        [this]()
        {
            AudioManager::instancia()
            .bajarMusica();

            actualizarValores();
        }
        );

    connect(
        btnMusicaMas,
        &QPushButton::clicked,
        this,
        [this]()
        {
            AudioManager::instancia()
            .subirMusica();

            actualizarValores();
        }
        );

    connect(
        btnEfectosMenos,
        &QPushButton::clicked,
        this,
        [this]()
        {
            AudioManager::instancia()
            .bajarEfectos();

            actualizarValores();
        }
        );

    connect(
        btnEfectosMas,
        &QPushButton::clicked,
        this,
        [this]()
        {
            AudioManager::instancia()
            .subirEfectos();

            actualizarValores();
        }
        );

    connect(
        btnMute,
        &QPushButton::clicked,
        this,
        [this]()
        {
            AudioManager::instancia()
            .alternarMute();

            actualizarBotonMute();
        }
        );

    connect(
        btnVolver,
        &QPushButton::clicked,
        this,
        [this]()
        {
            btnMusicaMenos->hide();
            btnMusicaMas->hide();

            btnEfectosMenos->hide();
            btnEfectosMas->hide();

            btnMute->hide();
            btnVolver->hide();

            lblMusica->hide();
            lblEfectos->hide();

            this->escena->clear();

            menuPrincipal =
                new MenuPrincipal(
                    this->escena,
                    this->vista,
                    this->manager
                    );
        }
        );

    actualizarValores();
    actualizarBotonMute();

    vista->show();
}

Music::~Music()
{
    delete btnMusicaMenos;
    delete btnMusicaMas;

    delete btnEfectosMenos;
    delete btnEfectosMas;

    delete btnMute;
    delete btnVolver;

    delete lblMusica;
    delete lblEfectos;
}

void Music::actualizarValores()
{
    lblMusica->setText(
        QString::number(
            AudioManager::instancia()
                .getVolumenMusica()
            )
        + "%"
        );

    lblEfectos->setText(
        QString::number(
            AudioManager::instancia()
                .getVolumenEfectos()
            )
        + "%"
        );
}

void Music::actualizarBotonMute()
{
    if(
        AudioManager::instancia()
            .estaMuteado()
        )
    {
        btnMute->setStyleSheet(
            "QPushButton {"
            "background: transparent;"
            "border: none;"
            "padding: 0px;"
            "margin: 0px;"
            "border-image: url(:/imagenes/mute_naranja.png) "
            "0 0 0 0 stretch stretch;"
            "}"
            );
    }
    else
    {
        btnMute->setStyleSheet(
            "QPushButton {"
            "background: transparent;"
            "border: none;"
            "padding: 0px;"
            "margin: 0px;"
            "}"
            "QPushButton:pressed {"
            "background: rgba(255,255,255,25);"
            "}"
            );
    }
}