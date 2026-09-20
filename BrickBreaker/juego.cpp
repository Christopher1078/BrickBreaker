#include "juego.h"

#include "pantalladerrota.h"
#include "pantallavictoria.h"
#include "usermanager.h"
#include "audiomanager.h"
#include "menuniveles.h"

#include <QLabel>

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
    lblEspera = nullptr;
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
    menuPausa->setGeometry(235, 145, 350, 310);
    menuPausa->setStyleSheet(
        "QWidget {"
        "background-color: rgba(10, 10, 10, 235);"
        "border: 3px solid white;"
        "border-radius: 18px;"
        "}"
        );

    QLabel* titulo = new QLabel("PAUSA", menuPausa);
    titulo->setGeometry(25, 30, 300, 55);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet(
        "QLabel {"
        "color: white;"
        "background: transparent;"
        "border: none;"
        "font: bold 30px 'Courier New';"
        "}"
        );

    btnResumir = new QPushButton("RESUMIR", menuPausa);
    btnResumir->setGeometry(55, 115, 240, 58);
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

    btnRendirse = new QPushButton("RENDIRSE", menuPausa);
    btnRendirse->setGeometry(55, 195, 240, 58);
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

    connect(btnPausa, &QPushButton::clicked, this, &Juego::pausarJuego);
    connect(btnResumir, &QPushButton::clicked, this, &Juego::resumirJuego);
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

    // Borra el fondo y cualquier elemento visual que no pertenezca al objeto Juego.
    escena->clear();

    new MenuNiveles(escena, vista, manager);

    // El nivel ya no se usa. Se destruye al volver al bucle de eventos para
    // liberar pelota, paleta, bloques, timer y los controles del nivel sin
    // destruir el objeto mientras todavía se procesa el clic del botón.
    deleteLater();
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
    mostrarEspera("PRESIONA W PARA COMENZAR");
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

            // Mientras espera la W no se permite mover la paleta con otras teclas.
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

    // btnResumir y btnRendirse son hijos de menuPausa y Qt los elimina junto con el panel.
    delete menuPausa;
    menuPausa = nullptr;
    btnResumir = nullptr;
    btnRendirse = nullptr;

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
