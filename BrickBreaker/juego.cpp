#include "juego.h"

#include "pantalladerrota.h"
#include "pantallavictoria.h"
#include "usermanager.h"
#include "audiomanager.h"
#include "menuniveles.h"

#include <QLabel>

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <system_error>

Juego::Juego(QGraphicsScene* escena,QGraphicsView* vista,UserManager* manager){
    this->escena = escena;
    this->vista = vista;
    this->manager = manager;

    tiempoPaleta = 0;
    tiempoVeloz = 0;
    tiempoLento = 0;
    tiempoRalentizado = 0;
    tiempoMini=0;

    inicio = nullptr;
    fin = nullptr;

    pelotaInicio = nullptr;
    pelotaFin = nullptr;

    bloques = nullptr;

    btnPausa = nullptr;
    menuPausa = nullptr;
    btnRendirse = nullptr;
    btnResumir = nullptr;
    btnGuardar = nullptr;
    lblEspera = nullptr;
    lblGuardado = nullptr;
    pausado = false;
    saliendoDelNivel = false;
    esperandoInicio = false;

    vidas = 3;
    puntos = 0;
    tiempo = 0;
    frames = 0;
    cantBloques = 0;

    QPixmap fondo(":/imagenes/fondo.png");

    fondo = fondo.scaled(800,600,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QGraphicsPixmapItem* imagen =escena->addPixmap(fondo);

    imagen->setZValue(-1);
    imagen->setPos(0, 0);

    crearBarraSuperior();
    actualizarBarra();
    crearMenuPausa();

    vista->installEventFilter(this);
    vista->setFocusPolicy(Qt::StrongFocus);
    vista->setFocus();

    pelota = new Pelota();
    paleta = new Paleta();

    escena->addItem(pelota->getGrafico());

    escena->addItem(paleta->getGrafico());

    timer = new QTimer;

    QObject::connect(timer,&QTimer::timeout,this,&Juego::actualizar);
}

void Juego::crearBarraSuperior(){
    txtVidas =escena->addText("VIDAS: ");

    for(int i = 0; i < 3; i++){
        QPixmap imagen(":/imagenes/corazon.png");

        imagen = imagen.scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation);

        corazones[i] =escena->addPixmap(imagen);

        corazones[i]->setPos(100 + i * 40,10);
    }

    txtPuntos =escena->addText("PUNTOS: 000000");

    txtTiempo =escena->addText("TIEMPO: 00:00");

    QFont fuente("Courier New",14,QFont::Bold);

    txtVidas->setFont(fuente);
    txtVidas->setDefaultTextColor(Qt::white);
    txtVidas->setPos(30, 10);

    txtPuntos->setFont(fuente);
    txtPuntos->setDefaultTextColor(Qt::white);
    txtPuntos->setPos(330, 10);

    txtTiempo->setFont(fuente);
    txtTiempo->setDefaultTextColor(Qt::white);
    txtTiempo->setPos(630, 10);
}

void Juego::crearMenuPausa(){
    btnPausa = new QPushButton("PAUSA", vista);
    btnPausa->setGeometry(680, 535, 110, 48);
    btnPausa->setCursor(Qt::PointingHandCursor);
    btnPausa->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(20, 20, 20, 210);"
        "color: white;"
        "border: 2px solid white;"
        "border-radius: 10px;"
        "font: bold 16px 'Courier New';"
        "}"
        "QPushButton:hover { background-color: rgba(55, 55, 55, 230); }"
        "QPushButton:pressed { background-color: rgba(90, 90, 90, 230); }"
        );
    btnPausa->show();

    menuPausa = new QWidget(vista);
    menuPausa->setGeometry(225, 100, 370, 405);
    menuPausa->setStyleSheet(
        "QWidget {"
        "background-color: rgba(10, 10, 10, 235);"
        "border: 3px solid white;"
        "border-radius: 18px;"
        "}"
        );

    QLabel* titulo = new QLabel("PAUSA", menuPausa);
    titulo->setGeometry(35, 20, 300, 55);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet(
        "QLabel {"
        "color: white;"
        "background: transparent;"
        "border: none;"
        "font: bold 30px 'Courier New';"
        "}"
        );

    btnResumir = new QPushButton("CONTINUAR", menuPausa);
    btnResumir->setGeometry(65, 90, 240, 58);
    btnResumir->setCursor(Qt::PointingHandCursor);
    btnResumir->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(35, 120, 70, 230);"
        "color: white;"
        "border: 2px solid white;"
        "border-radius: 10px;"
        "font: bold 18px 'Courier New';"
        "}"
        "QPushButton:hover { background-color: rgba(45, 150, 85, 240); }"
        );

    btnGuardar = new QPushButton("GUARDAR EL JUEGO", menuPausa);
    btnGuardar->setGeometry(65, 165, 240, 58);
    btnGuardar->setCursor(Qt::PointingHandCursor);
    btnGuardar->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(55, 90, 150, 230);"
        "color: white;"
        "border: 2px solid white;"
        "border-radius: 10px;"
        "font: bold 16px 'Courier New';"
        "}"
        "QPushButton:hover { background-color: rgba(70, 115, 185, 240); }"
        );

    btnRendirse = new QPushButton("RENDIRSE", menuPausa);
    btnRendirse->setGeometry(65, 240, 240, 58);
    btnRendirse->setCursor(Qt::PointingHandCursor);
    btnRendirse->setStyleSheet(
        "QPushButton {"
        "background-color: rgba(145, 45, 45, 230);"
        "color: white;"
        "border: 2px solid white;"
        "border-radius: 10px;"
        "font: bold 18px 'Courier New';"
        "}"
        "QPushButton:hover { background-color: rgba(180, 55, 55, 240); }"
        );

    lblGuardado = new QLabel("", menuPausa);
    lblGuardado->setGeometry(35, 315, 300, 52);
    lblGuardado->setAlignment(Qt::AlignCenter);
    lblGuardado->setWordWrap(true);
    lblGuardado->setStyleSheet(
        "QLabel {"
        "color: rgb(130, 255, 170);"
        "background: transparent;"
        "border: none;"
        "font: bold 14px 'Courier New';"
        "}"
        );

    connect(btnPausa, &QPushButton::clicked, this, &Juego::pausarJuego);
    connect(btnResumir, &QPushButton::clicked, this, &Juego::resumirJuego);
    connect(btnGuardar, &QPushButton::clicked, this, &Juego::guardarJuego);
    connect(btnRendirse, &QPushButton::clicked, this, &Juego::rendirse);

    menuPausa->hide();

    lblEspera = new QLabel(vista);
    lblEspera->setGeometry(145, 245, 510, 125);
    lblEspera->setAlignment(Qt::AlignCenter);
    lblEspera->setWordWrap(true);
    lblEspera->setStyleSheet(
        "QLabel {"
        "background-color: rgba(10, 10, 10, 225);"
        "color: white;"
        "border: 3px solid white;"
        "border-radius: 16px;"
        "font: bold 22px 'Courier New';"
        "padding: 12px;"
        "}"
        );
    lblEspera->hide();
}

void Juego::pausarJuego(){
    if(pausado || saliendoDelNivel || esperandoInicio || vidas <= 0 || cantBloques == 0){
        return;
    }

    pausado = true;
    timer->stop();
    btnPausa->hide();
    if(lblGuardado != nullptr){
        lblGuardado->clear();
    }
    menuPausa->show();
    menuPausa->raise();
    btnResumir->setFocus();
}

void Juego::resumirJuego(){
    if(!pausado || saliendoDelNivel){
        return;
    }

    pausado = false;
    menuPausa->hide();
    btnPausa->show();
    vista->setFocus();
    timer->start(16);
}

void Juego::rendirse(){
    if(saliendoDelNivel){
        return;
    }

    saliendoDelNivel = true;
    pausado = false;
    timer->stop();
    vista->removeEventFilter(this);

    ocultarControlesPausa();
    limpiarNivel();


    escena->clear();

    new MenuNiveles(escena, vista, manager);


    deleteLater();
}

std::string Juego::rutaJuegoGuardado() const{
    if(manager == nullptr || manager->getActual() == nullptr){
        return "";
    }

    std::filesystem::path carpeta = std::filesystem::path("Usuarios") / manager->getActual()->getNombre();
    return (carpeta / ("partida_nivel_" + std::to_string(nivel + 1) + ".dat")).string();
}

void Juego::guardarJuego(){
    if(!pausado || saliendoDelNivel || manager == nullptr || manager->getActual() == nullptr){
        return;
    }

    std::string ruta = rutaJuegoGuardado();
    if(ruta.empty()){
        return;
    }

    std::filesystem::create_directories(std::filesystem::path(ruta).parent_path());
    std::ofstream archivo(ruta, std::ios::trunc);

    if(!archivo.is_open()){
        if(lblGuardado != nullptr){
            lblGuardado->setStyleSheet(
                "QLabel { color: rgb(255, 130, 130); background: transparent; border: none; font: bold 14px 'Courier New'; }"
                );
            lblGuardado->setText("NO SE PUDO GUARDAR");
        }
        return;
    }

    archivo << std::setprecision(9);
    archivo << "BRICKBREAKER_SAVE 1\n";
    archivo << nivel << ' ' << vidas << ' ' << puntos << ' ' << tiempo << ' '
            << frames << ' ' << cantBloques << '\n';
    archivo << tiempoPaleta << ' ' << tiempoVeloz << ' ' << tiempoLento << ' '
            << tiempoMini << ' ' << tiempoRalentizado << '\n';

    archivo << paleta->getGrafico()->x() << ' ' << paleta->getGrafico()->y() << ' '
            << paleta->estaGrande() << ' ' << paleta->estaMini() << ' '
            << paleta->estaRalentizada() << '\n';

    archivo << pelota->getGrafico()->x() << ' ' << pelota->getGrafico()->y() << ' '
            << pelota->getVelocidadX() << ' ' << pelota->getVelocidadY() << ' '
            << pelota->estaAumentada() << ' ' << pelota->estaRalentizada() << '\n';

    archivo << FILAS * COLUMNAS << '\n';
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            QGraphicsPixmapItem* grafico = bloques[i][j].getGrafico();
            bool existe = grafico != nullptr;
            archivo << existe;

            if(existe){
                archivo << ' ' << bloques[i][j].estaDestruido()
                << ' ' << bloques[i][j].getGolpes()
                << ' ' << grafico->x()
                << ' ' << grafico->y()
                << ' ' << bloques[i][j].getVelocidad();
            }
            archivo << '\n';
        }
    }

    int cantidadPelotasExtra = 0;
    for(NodoPelota* actual = pelotaInicio; actual != nullptr; actual = actual->siguiente){
        cantidadPelotasExtra++;
    }
    archivo << cantidadPelotasExtra << '\n';
    for(NodoPelota* actual = pelotaInicio; actual != nullptr; actual = actual->siguiente){
        Pelota* p = actual->pelota;
        archivo << p->getGrafico()->x() << ' ' << p->getGrafico()->y() << ' '
                << p->getVelocidadX() << ' ' << p->getVelocidadY() << ' '
                << p->estaAumentada() << ' ' << p->estaRalentizada() << '\n';
    }

    int cantidadPowerUps = 0;
    for(NodoPowerUp* actual = inicio; actual != nullptr; actual = actual->siguiente){
        cantidadPowerUps++;
    }
    archivo << cantidadPowerUps << '\n';
    for(NodoPowerUp* actual = inicio; actual != nullptr; actual = actual->siguiente){
        archivo << static_cast<int>(actual->powerUp->getTipo()) << ' '
                << actual->powerUp->getGrafico()->x() << ' '
                << actual->powerUp->getGrafico()->y() << '\n';
    }

    archivo.close();

    if(lblGuardado != nullptr){
        lblGuardado->setStyleSheet(
            "QLabel { color: rgb(130, 255, 170); background: transparent; border: none; font: bold 14px 'Courier New'; }"
            );
        lblGuardado->setText("PARTIDA GUARDADA");
    }
}

bool Juego::cargarJuegoGuardado(){
    std::string ruta = rutaJuegoGuardado();
    if(ruta.empty() || !std::filesystem::exists(ruta)){
        return false;
    }

    std::ifstream archivo(ruta);
    if(!archivo.is_open()){
        return false;
    }

    std::string firma;
    int version = 0;
    archivo >> firma >> version;
    if(firma != "BRICKBREAKER_SAVE" || version != 1){
        return false;
    }

    int nivelGuardado = -1;
    int vidasGuardadas = 0;
    int puntosGuardados = 0;
    int tiempoGuardado = 0;
    int framesGuardados = 0;
    int bloquesGuardados = 0;
    archivo >> nivelGuardado >> vidasGuardadas >> puntosGuardados >> tiempoGuardado
        >> framesGuardados >> bloquesGuardados;

    if(!archivo.good() || nivelGuardado != nivel){
        return false;
    }

    int tPaleta = 0;
    int tVeloz = 0;
    int tLento = 0;
    int tMini = 0;
    int tRalentizado = 0;
    archivo >> tPaleta >> tVeloz >> tLento >> tMini >> tRalentizado;

    float paletaX = 0;
    float paletaY = 0;
    bool paletaGrande = false;
    bool paletaMini = false;
    bool paletaLenta = false;
    archivo >> paletaX >> paletaY >> paletaGrande >> paletaMini >> paletaLenta;

    float pelotaX = 0;
    float pelotaY = 0;
    float pelotaVX = 0;
    float pelotaVY = 0;
    bool pelotaAumentada = false;
    bool pelotaRalentizada = false;
    archivo >> pelotaX >> pelotaY >> pelotaVX >> pelotaVY >> pelotaAumentada >> pelotaRalentizada;

    int cantidadBloquesArchivo = 0;
    archivo >> cantidadBloquesArchivo;
    if(!archivo.good() || cantidadBloquesArchivo != FILAS * COLUMNAS){
        return false;
    }

    struct EstadoBloque{
        bool existe = false;
        bool destruido = false;
        int golpes = 0;
        float x = 0;
        float y = 0;
        float velocidad = 0;
    };

    EstadoBloque estados[FILAS][COLUMNAS];
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            archivo >> estados[i][j].existe;
            if(estados[i][j].existe){
                archivo >> estados[i][j].destruido
                    >> estados[i][j].golpes
                    >> estados[i][j].x
                    >> estados[i][j].y
                    >> estados[i][j].velocidad;
            }
        }
    }

    int cantidadPelotasExtra = 0;
    archivo >> cantidadPelotasExtra;
    if(cantidadPelotasExtra < 0 || cantidadPelotasExtra > 20){
        return false;
    }

    struct EstadoPelota{
        float x;
        float y;
        float vx;
        float vy;
        bool aumentada;
        bool ralentizada;
    };

    EstadoPelota extras[20];
    for(int i = 0; i < cantidadPelotasExtra; i++){
        archivo >> extras[i].x >> extras[i].y >> extras[i].vx >> extras[i].vy
            >> extras[i].aumentada >> extras[i].ralentizada;
    }

    int cantidadPowerUps = 0;
    archivo >> cantidadPowerUps;
    if(cantidadPowerUps < 0 || cantidadPowerUps > 40){
        return false;
    }

    struct EstadoPowerUp{
        int tipo;
        float x;
        float y;
    };

    EstadoPowerUp powers[40];
    for(int i = 0; i < cantidadPowerUps; i++){
        archivo >> powers[i].tipo >> powers[i].x >> powers[i].y;
        if(powers[i].tipo < static_cast<int>(PALETA_LARGA) || powers[i].tipo > static_cast<int>(PELOTA_LENTA)){
            return false;
        }
    }

    if(archivo.fail()){
        return false;
    }

    vidas = vidasGuardadas;
    puntos = puntosGuardados;
    tiempo = tiempoGuardado;
    frames = framesGuardados;
    cantBloques = bloquesGuardados;
    tiempoPaleta = tPaleta;
    tiempoVeloz = tVeloz;
    tiempoLento = tLento;
    tiempoMini = tMini;
    tiempoRalentizado = tRalentizado;

    paleta->restaurarEstado(paletaX, paletaY, paletaGrande, paletaMini, paletaLenta);
    pelota->restaurarEstado(pelotaX, pelotaY, pelotaVX, pelotaVY, pelotaAumentada, pelotaRalentizada);

    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            QGraphicsPixmapItem* grafico = bloques[i][j].getGrafico();
            if(!estados[i][j].existe || grafico == nullptr){
                continue;
            }

            bloques[i][j].restaurarEstado(
                estados[i][j].destruido,
                estados[i][j].golpes,
                estados[i][j].x,
                estados[i][j].y,
                estados[i][j].velocidad
                );

            if(estados[i][j].destruido && grafico->scene() != nullptr){
                escena->removeItem(grafico);
            }
        }
    }

    for(int i = 0; i < cantidadPelotasExtra; i++){
        Pelota* nuevaPelota = new Pelota();
        nuevaPelota->restaurarEstado(
            extras[i].x, extras[i].y, extras[i].vx, extras[i].vy,
            extras[i].aumentada, extras[i].ralentizada
            );
        escena->addItem(nuevaPelota->getGrafico());

        NodoPelota* nuevo = new NodoPelota;
        nuevo->pelota = nuevaPelota;
        nuevo->anterior = nullptr;
        nuevo->siguiente = pelotaInicio;
        if(pelotaInicio != nullptr){
            pelotaInicio->anterior = nuevo;
        }else{
            pelotaFin = nuevo;
        }
        pelotaInicio = nuevo;
    }

    for(int i = 0; i < cantidadPowerUps; i++){
        PowerUp* power = new PowerUp(static_cast<Tipo>(powers[i].tipo));
        power->getGrafico()->setPos(powers[i].x, powers[i].y);
        escena->addItem(power->getGrafico());

        NodoPowerUp* nuevo = new NodoPowerUp;
        nuevo->powerUp = power;
        nuevo->anterior = nullptr;
        nuevo->siguiente = inicio;
        if(inicio != nullptr){
            inicio->anterior = nuevo;
        }else{
            fin = nuevo;
        }
        inicio = nuevo;
    }

    actualizarBarra();
    return true;
}

void Juego::eliminarJuegoGuardado(){
    std::string ruta = rutaJuegoGuardado();
    if(!ruta.empty()){
        std::error_code error;
        std::filesystem::remove(ruta, error);
    }
}

void Juego::ocultarControlesPausa(){
    pausado = false;
    esperandoInicio = false;

    if(btnPausa != nullptr){
        btnPausa->hide();
    }

    if(menuPausa != nullptr){
        menuPausa->hide();
    }

    if(lblEspera != nullptr){
        lblEspera->hide();
    }
}

void Juego::mostrarEspera(const QString& mensaje){
    esperandoInicio = true;
    timer->stop();

    if(btnPausa != nullptr){
        btnPausa->setEnabled(false);
    }

    if(menuPausa != nullptr){
        menuPausa->hide();
    }

    if(lblEspera != nullptr){
        lblEspera->setText(mensaje);
        lblEspera->show();
        lblEspera->raise();
    }

    vista->setFocus();
}

void Juego::comenzarTrasEspera(){
    if(!esperandoInicio || saliendoDelNivel || vidas <= 0 || cantBloques == 0){
        return;
    }

    esperandoInicio = false;

    if(lblEspera != nullptr){
        lblEspera->hide();
    }

    if(btnPausa != nullptr){
        btnPausa->setEnabled(true);
        btnPausa->show();
    }

    vista->setFocus();
    timer->start(16);
}

void Juego::iniciarTimer(){
    vista->show();

    if(cargarJuegoGuardado()){
        mostrarEspera("PARTIDA CARGADA\nPRESIONA W PARA CONTINUAR");
    }else{
        mostrarEspera("PRESIONA W PARA COMENZAR");
    }
}

void Juego::actualizar(){
    frames++;

    if(frames >= 60){
        tiempo++;
        frames = 0;

        if(tiempoPaleta > 0){
            tiempoPaleta--;

            if(tiempoPaleta == 0){
                paleta->hacerNormal();
            }
        }

        if(tiempoVeloz > 0){
            tiempoVeloz--;

            if(tiempoVeloz == 0){
                pelota->disminuirVelocidad();
                NodoPelota* actual=pelotaInicio;
                while(actual!=nullptr){
                    actual->pelota->disminuirVelocidad();
                    actual=actual->siguiente;
                }
            }
        }

        if(tiempoMini > 0){
            tiempoMini--;

            if(tiempoMini == 0){
                paleta->hacerNormal();
            }
        }

        if(tiempoLento > 0){
            tiempoLento--;

            if(tiempoLento == 0){
                paleta->derralentizar();
            }
        }

        if(tiempoRalentizado > 0){
            tiempoRalentizado--;
            if(tiempoRalentizado == 0){
                pelota->disminuirVelocidad();
                NodoPelota* actual=pelotaInicio;
                while(actual!=nullptr){
                    actual->pelota->disminuirVelocidad();
                    actual=actual->siguiente;
                }
            }
        }
        actualizarBarra();
    }

    pelota->mover();
    pelota->comprobarParedes();

    NodoPelota* pelotaActual =pelotaInicio;

    while(pelotaActual != nullptr){
        pelotaActual->pelota->mover();

        pelotaActual =pelotaActual->siguiente;
    }

    pelotaActual = pelotaInicio;

    while(pelotaActual != nullptr){
        pelotaActual->pelota->comprobarParedes();

        pelotaActual =pelotaActual->siguiente;
    }

    pelotaActual = pelotaInicio;

    while(pelotaActual != nullptr){
        NodoPelota* siguiente =pelotaActual->siguiente;

        if(pelotaActual->pelota->getGrafico()->y() > 585){
            eliminarPelota(pelotaActual);
        }

        pelotaActual = siguiente;
    }

    if(pelota->getGrafico()->y() > 585 && pelotaInicio == nullptr){
        perderVida();
        return;
    }

    pelotaActual = pelotaInicio;

    while(pelotaActual != nullptr){
        if(pelotaActual->pelota->colisionaCon(paleta->getGrafico())){
            pelotaActual->pelota->rebotarPaleta(paleta->getGrafico());

            AudioManager::instancia().reproducirRebote();

            float nuevaY = paleta->getGrafico()->y()-pelotaActual->pelota->getGrafico()->boundingRect().height();

            pelotaActual->pelota->getGrafico()->setY(nuevaY);
        }

        pelotaActual =pelotaActual->siguiente;
    }

    NodoPowerUp* actual = inicio;

    while(actual != nullptr)
    {
        actual->powerUp->mover();

        NodoPowerUp* siguiente =actual->siguiente;

        if(actual->powerUp->getGrafico()->y() > 590){
            eliminarPowerUp(actual);
        }

        actual = siguiente;
    }

    actual = inicio;

    while(actual != nullptr){
        NodoPowerUp* siguiente =actual->siguiente;

        if(actual->powerUp->getGrafico()->collidesWithItem(paleta->getGrafico())){
            activarPowerUp(actual->powerUp->getTipo());

            eliminarPowerUp(actual);
        }

        actual = siguiente;
    }

    if(pelota->colisionaCon(paleta->getGrafico())){
        pelota->rebotarPaleta(paleta->getGrafico());

        AudioManager::instancia().reproducirRebote();

        float nuevaY =
            paleta->getGrafico()->y()-pelota->getGrafico()->boundingRect().height();

        pelota->getGrafico()->setY(nuevaY);
    }

    revisarColisionBloques(pelota);

    pelotaActual = pelotaInicio;

    while(pelotaActual != nullptr)
    {
        NodoPelota* siguiente =pelotaActual->siguiente;

        revisarColisionBloques(pelotaActual->pelota);

        pelotaActual = siguiente;
    }
}

void Juego::actualizarBarra()
{
    txtVidas->setPlainText("VIDAS: ");

    for(int i = 0; i < 3; i++){
        if(i < vidas){
            corazones[i]->setVisible(true);
        }
        else{
            corazones[i]->setVisible(false);
        }
    }

    txtPuntos->setPlainText("PUNTOS: "+QString("%1").arg(puntos,6,10,QChar('0')));

    int minutos = tiempo / 60;
    int segundos = tiempo % 60;

    txtTiempo->setPlainText(QString("TIEMPO: %1:%2").arg(minutos,2,10,QChar('0')).arg(segundos,2,10,QChar('0')));
}

void Juego::reiniciarPelota(){
    pelota->getGrafico()->setPos(390,500);

    pelota->reiniciarMovimiento();

    paleta->reiniciar();
}

void Juego::perderVida(){
    AudioManager::instancia().reproducirPerderVida();

    timer->stop();
    vidas--;

    actualizarBarra();

    if(vidas <= 0){
        esperandoInicio = false;

        if(lblEspera != nullptr){
            lblEspera->hide();
        }

        vista->removeEventFilter(this);

        limpiarNivel();

        derrota =new PantallaDerrota(escena,vista,manager,puntos,tiempo,cantBloques,nivel);

        return;
    }

    reiniciarPelota();
    mostrarEspera("PERDISTE UNA VIDA\nPRESIONA W PARA CONTINUAR");
}

void Juego::verificarVictoria()
{
    if(cantBloques == 0){
        int bonusTiempo;
        int bonusVidas;
        int puntoFinal;
        int estrellas;

        timer->stop();

        calcularPuntaje(bonusTiempo,bonusVidas,puntoFinal,estrellas);

        manager->getActual()->setEstrellas(estrellas,nivel);

        manager ->getActual() ->setMejorPuntaje(puntoFinal,nivel);

        if(nivel < 4 && !manager->getActual()->isPasado(nivel + 1)){
            manager->getActual()->pasarNivel();
        }

        manager->guardarArreglo();
        eliminarJuegoGuardado();

        vista->removeEventFilter(this);

        limpiarNivel();

        victoria =new PantallaVictoria(escena,vista,manager,puntoFinal,puntos,bonusTiempo,bonusVidas,estrellas,nivel);
    }
}

void Juego::limpiarNivel(){
    ocultarControlesPausa();

    if(pelota != nullptr && pelota->getGrafico() != nullptr){
        escena->removeItem(pelota->getGrafico());
    }

    if(paleta != nullptr && paleta->getGrafico() != nullptr){
        escena->removeItem(paleta->getGrafico());
    }

    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(bloques[i][j].getGrafico()!= nullptr && !bloques[i][j].estaDestruido()){
                escena->removeItem(bloques[i][j].getGrafico());
            }
        }
    }

    NodoPelota* pelotaActual = pelotaInicio;

    NodoPowerUp* powerActual =inicio;

    while(pelotaActual != nullptr){
        NodoPelota* siguiente =pelotaActual->siguiente;

        eliminarPelota(pelotaActual);

        pelotaActual = siguiente;
    }

    while(powerActual != nullptr){
        NodoPowerUp* siguiente =powerActual->siguiente;

        eliminarPowerUp(powerActual);

        powerActual = siguiente;
    }

    escena->removeItem(txtVidas);
    escena->removeItem(txtPuntos);
    escena->removeItem(txtTiempo);

    for(int i = 0; i < 3; i++){
        escena->removeItem(corazones[i]);
    }
}

void Juego::calcularPuntaje(int& bonusTiempo,int& bonusVidas,int& puntoFinal,int& estrellas)
{
    bonusTiempo =(tiempoObjetivo - tiempo)* 10;

    if(bonusTiempo < 0){
        bonusTiempo = 0;
    }

    bonusVidas =(vidas - 1)* 500;

    if(vidas == 0){
        bonusVidas = 0;
    }

    estrellas =((bonusTiempo+bonusVidas)* 3)/bonusObjetivo;

    if(estrellas > 3){
        estrellas = 3;
    }

    puntoFinal =puntos + bonusTiempo + bonusVidas;
}

void Juego::activarPowerUp(Tipo tipo){
    AudioManager::instancia().reproducirPowerUp();

    switch(tipo){
    case PALETA_LARGA:{
        paleta->hacerGrande();
        tiempoPaleta = 10;
        break;
    }

    case VELOCIDAD_EXTRA:{
        pelota->aumentarVelocidad();
        NodoPelota* actual=pelotaInicio;
        while(actual!=nullptr){
            actual->pelota->aumentarVelocidad();
            actual=actual->siguiente;
        }
        tiempoVeloz = 10;
        break;
    }

    case VIDA_EXTRA:{
        if(vidas != 3){
            vidas++;
            actualizarBarra();
        }
        break;
    }

    case PELOTA_EXTRA:{
        crearPelotaExtra();
        break;
    }

    case PELOTA_LENTA:{
        pelota->ralentalizar();
        NodoPelota* actual=pelotaInicio;
        while(actual!=nullptr){
            actual->pelota->ralentalizar();
            actual=actual->siguiente;
        }
        tiempoRalentizado = 10;
        break;
    }

    case PALETA_LENTA:{
        paleta->ralentizar();
        tiempoLento=10;
        break;
    }

    case PALETA_MINI:{
        paleta->hacerMini();
        tiempoMini=10;
        break;
    }
    }
}

void Juego::eliminarPowerUp(NodoPowerUp* nodo)
{
    if(nodo == nullptr){
        return;
    }

    if(nodo->anterior != nullptr){
        nodo->anterior->siguiente =nodo->siguiente;
    }
    else{
        inicio =nodo->siguiente;
    }

    if(nodo->siguiente != nullptr){
        nodo->siguiente->anterior =nodo->anterior;
    }
    else{
        fin =nodo->anterior;
    }

    if(nodo->powerUp != nullptr){
        if(nodo->powerUp->getGrafico()!= nullptr){
            escena->removeItem(nodo->powerUp->getGrafico());
        }

        delete nodo->powerUp;
    }

    delete nodo;
}

void Juego::crearPelotaExtra(){
    Pelota* nuevaPelota =new Pelota();

    nuevaPelota->getGrafico()->setPos(paleta->getGrafico()->pos());

    escena->addItem(nuevaPelota->getGrafico());

    NodoPelota* nuevoNodo =new NodoPelota;

    nuevoNodo->pelota =nuevaPelota;

    nuevoNodo->anterior =nullptr;

    nuevoNodo->siguiente =pelotaInicio;

    if(pelotaInicio != nullptr){
        pelotaInicio->anterior =nuevoNodo;
    }
    else{
        pelotaFin =nuevoNodo;
    }

    pelotaInicio =nuevoNodo;
}

void Juego::eliminarPelota(NodoPelota* nodo){
    if(nodo->anterior == nullptr){
        pelotaInicio =nodo->siguiente;
    }
    else{
        nodo->anterior->siguiente =nodo->siguiente;
    }

    if(nodo->siguiente == nullptr){
        pelotaFin =nodo->anterior;
    }
    else{
        nodo->siguiente->anterior =nodo->anterior;
    }

    escena->removeItem(nodo->pelota->getGrafico());

    delete nodo->pelota;
    delete nodo;
}

void Juego::revisarColisionBloques(Pelota* p){
    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(bloques[i][j].getGrafico()!= nullptr){
                if(!bloques[i][j].estaDestruido()){
                    bloques[i][j].mover();
                    if(p->colisionaCon(bloques[i][j].getGrafico())){
                        p->rebotarBloque(bloques[i][j].getGrafico());
                        bloques[i][j].destruir();

                        if(bloques[i][j].estaDestruido()){
                            AudioManager::instancia().reproducirRomperBloque();

                            int tipo =bloques[i][j].getPowerUp();

                            if(tipo != 0){
                                PowerUp* powerUp;

                                switch(tipo){
                                case 1:
                                    powerUp =new PowerUp(PALETA_LARGA);
                                    break;
                                case 2:
                                    powerUp =new PowerUp(VELOCIDAD_EXTRA);
                                    break;
                                case 3:
                                    powerUp =new PowerUp(VIDA_EXTRA);
                                    break;
                                case 4:
                                    powerUp =new PowerUp(PELOTA_EXTRA);
                                    break;
                                case 5:
                                    powerUp =new PowerUp(PELOTA_LENTA);
                                    break;
                                case 6:
                                    powerUp =new PowerUp(PALETA_LENTA);
                                    break;
                                default:
                                    powerUp =new PowerUp(PALETA_MINI);
                                    break;
                                }

                                powerUp->getGrafico()->setPos(bloques[i][j].getGrafico()->sceneBoundingRect().center());

                                escena->addItem(powerUp->getGrafico());

                                NodoPowerUp* nuevoNodo =new NodoPowerUp;

                                nuevoNodo->powerUp =powerUp;

                                nuevoNodo->anterior =nullptr;

                                nuevoNodo->siguiente =inicio;

                                if(inicio != nullptr){
                                    inicio->anterior =nuevoNodo;
                                }
                                else{
                                    fin =nuevoNodo;
                                }

                                inicio =nuevoNodo;
                            }

                            escena->removeItem(bloques[i][j].getGrafico());

                            cantBloques--;
                        }

                        if(bloques[i][j].getTipoBloque()!= METALICO){
                            puntos += 50;
                        }

                        actualizarBarra();

                        verificarVictoria();

                        return;
                    }
                }
            }
        }
    }
}

bool Juego::eventFilter(QObject* objeto,QEvent* evento){
    if(pausado || saliendoDelNivel){
        return QObject::eventFilter(objeto,evento);
    }

    if(vidas == 0 || cantBloques == 0){
        return QObject::eventFilter(objeto,evento);
    }

    if(esperandoInicio){
        if(evento->type() == QEvent::KeyPress){
            QKeyEvent* tecla =static_cast<QKeyEvent*>(evento);

            if(tecla->key() == Qt::Key_W && !tecla->isAutoRepeat()){
                comenzarTrasEspera();
            }


            return true;
        }

        return QObject::eventFilter(objeto,evento);
    }

    if(evento->type() == QEvent::KeyPress){
        QKeyEvent* tecla =static_cast<QKeyEvent*>(evento);

        if(tecla->key() == Qt::Key_Left || tecla->key() == Qt::Key_A){
            paleta->moverIzquierda();
            return true;
        }

        if(tecla->key() == Qt::Key_Right || tecla->key() == Qt::Key_D){
            paleta->moverDerecha();
            return true;
        }
    }

    return QObject::eventFilter(objeto,evento);
}

Juego::~Juego(){
    if(vista != nullptr){
        vista->removeEventFilter(this);
    }

    delete btnPausa;
    btnPausa = nullptr;


    delete menuPausa;
    menuPausa = nullptr;
    btnResumir = nullptr;
    btnRendirse = nullptr;
    btnGuardar = nullptr;
    lblGuardado = nullptr;

    delete lblEspera;
    lblEspera = nullptr;

    delete pelota;
    pelota = nullptr;

    delete paleta;
    paleta = nullptr;

    delete timer;
    timer = nullptr;

    if(bloques != nullptr){
        for(int i = 0; i < FILAS; i++){
            delete[] bloques[i];
        }
        delete[] bloques;
        bloques = nullptr;
    }

    delete txtVidas;
    txtVidas = nullptr;
    delete txtPuntos;
    txtPuntos = nullptr;
    delete txtTiempo;
    txtTiempo = nullptr;

    for(int i = 0; i < 3; i++){
        delete corazones[i];
        corazones[i] = nullptr;
    }
}
