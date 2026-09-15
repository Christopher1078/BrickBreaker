#include "juego.h"
#include "pantalladerrota.h"
#include "pantallavictoria.h"
#include "usermanager.h"
Juego::Juego(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager)
{
    this->escena=escena;
    this->vista=vista;
    this->manager=manager;
    tiempoPaleta=0;
    tiempoVeloz=0;

    inicio=nullptr;
    fin=nullptr;
    pelotaInicio=nullptr;
    pelotaFin=nullptr;

    vidas=3;
    puntos=0;
    tiempo=0;
    frames=0;
    cantBloques=0;

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
}

void Juego::crearBarraSuperior(){
    txtVidas=escena->addText("VIDAS: ");

    for(int i=0;i<3;i++){
        QPixmap imagen(":/imagenes/corazon.png");
        imagen=imagen.scaled(30,30,Qt::KeepAspectRatio,Qt::SmoothTransformation);

        corazones[i]=escena->addPixmap(imagen);
        corazones[i]->setPos(100+i*40,10);
    }
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
        if(tiempoPaleta>0){
            tiempoPaleta--;
            if(tiempoPaleta==0){
                paleta->hacerNormal();
            }
        }
        if(tiempoVeloz>0){
            tiempoVeloz--;
            if(tiempoVeloz==0){
                pelota->disminuirVelocidad();
            }
        }
        actualizarBarra();
    }
    pelota->mover();
    pelota->comprobarParedes();

    if(pelota->getGrafico()->y()>585){
        perderVida();
        return;
    }

    NodoPowerUp* actual = inicio;

    while(actual != nullptr){
        actual->powerUp->mover();
        NodoPowerUp* siguiente = actual->siguiente;

        if(actual->powerUp->getGrafico()->y() > 590){
            eliminarPowerUp(actual);
        }

        actual = siguiente;
    }

    actual = inicio;

    while(actual != nullptr){
        NodoPowerUp* siguiente = actual->siguiente;
        if(actual->powerUp->getGrafico()->collidesWithItem(paleta->getGrafico())){
            activarPowerUp(actual->powerUp->getTipo());
            eliminarPowerUp(actual);
        }
        actual = siguiente;
    }

    if (pelota->colisionaCon(paleta->getGrafico())){
        pelota->rebotarPaleta(paleta->getGrafico());

        float nuevaY=paleta->getGrafico()->y()-pelota->getGrafico()->boundingRect().height();
        pelota->getGrafico()->setY(nuevaY);
    }

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            if(bloques[i][j].getGrafico()!=nullptr){
                if(!bloques[i][j].estaDestruido()){
                    bloques[i][j].mover();
                    if(pelota->colisionaCon(bloques[i][j].getGrafico())){
                        pelota->rebotarBloque(bloques[i][j].getGrafico());
                        bloques[i][j].destruir();
                        if(bloques[i][j].estaDestruido()){
                            int tipo=bloques[i][j].getPowerUp();
                            if(tipo!=0){
                                PowerUp* powerUp;
                                switch(tipo){
                                case 1:{
                                    powerUp=new PowerUp(PALETA_LARGA);
                                    break;
                                }
                                case 2:{
                                    powerUp=new PowerUp(VELOCIDAD_EXTRA);
                                    break;
                                }
                                case 3:{
                                    powerUp=new PowerUp(VIDA_EXTRA);
                                    break;
                                }
                                default:{
                                    powerUp=new PowerUp(PELOTA_EXTRA);
                                    break;
                                }
                                }
                                powerUp->getGrafico()->setPos(bloques[i][j].getGrafico()->sceneBoundingRect().center());
                                escena->addItem(powerUp->getGrafico());

                                NodoPowerUp* nuevoNodo = new NodoPowerUp;

                                nuevoNodo->powerUp = powerUp;
                                nuevoNodo->anterior = nullptr;
                                nuevoNodo->siguiente = inicio;

                                if(inicio != nullptr){
                                    inicio->anterior = nuevoNodo;
                                }else{
                                    fin=nuevoNodo;
                                }

                                inicio = nuevoNodo;
                            }
                            escena->removeItem(bloques[i][j].getGrafico());
                            cantBloques--;
                        }
                        if(bloques[i][j].getTipoBloque()!=METALICO){
                            puntos+=50;
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

void Juego::actualizarBarra(){
    txtVidas->setPlainText("VIDAS: ");

    for(int i=0;i<3;i++){
        if(i<vidas){
            corazones[i]->setVisible(true);
        }else{
            corazones[i]->setVisible(false);
        }
    }

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
    actualizarBarra();
    if(vidas<=0){
        timer->stop();
        vista->removeEventFilter(this);
        limpiarNivel();
        derrota=new PantallaDerrota(escena, vista, manager, puntos, tiempo, cantBloques, nivel);
        return;
    }
    reiniciarPelota();
}

void Juego::verificarVictoria(){
    if(cantBloques==0){
        int bonusTiempo;
        int bonusVidas;
        int puntoFinal;
        int estrellas;
        timer->stop();
        calcularPuntaje(bonusTiempo, bonusVidas, puntoFinal, estrellas);
        manager->getActual()->setEstrellas(estrellas,nivel);
        manager->getActual()->setMejorPuntaje(puntoFinal, nivel);
        if(!manager->getActual()->isPasado(nivel+1)){
            manager->getActual()->pasarNivel();
        }
        manager->guardarArreglo();
        vista->removeEventFilter(this);
        limpiarNivel();
        victoria=new PantallaVictoria(escena,vista,manager, puntoFinal, puntos, bonusTiempo, bonusVidas, estrellas, nivel);
    }
}

void Juego::limpiarNivel(){
    if(pelota != nullptr && pelota->getGrafico() != nullptr){
        escena->removeItem(pelota->getGrafico());
    }

    if(paleta != nullptr && paleta->getGrafico() != nullptr){
        escena->removeItem(paleta->getGrafico());
    }

    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(bloques[i][j].getGrafico() != nullptr && !bloques[i][j].estaDestruido()){
                escena->removeItem(bloques[i][j].getGrafico());
            }
        }
    }

    escena->removeItem(txtVidas);
    escena->removeItem(txtPuntos);
    escena->removeItem(txtTiempo);

    for(int i=0; i<3; i++){
        escena->removeItem(corazones[i]);
    }
}

void Juego::calcularPuntaje(int &bonusTiempo, int &bonusVidas, int &puntoFinal, int &estrellas){
    bonusTiempo=(tiempoObjetivo-tiempo)*10;

    if(bonusTiempo<0){
        bonusTiempo=0;
    }

    bonusVidas=(vidas-1)*500;

    if(vidas==0){
        bonusVidas=0;
    }

    estrellas=((bonusTiempo+bonusVidas)*3)/bonusObjetivo;
    if(estrellas>3){
        estrellas=3;
    }

    puntoFinal=puntos+bonusTiempo+bonusVidas;
}

void Juego::activarPowerUp(Tipo tipo){
    switch(tipo){
    case PALETA_LARGA:{
        paleta->hacerGrande();
        tiempoPaleta=10;
        break;
    }
    case VELOCIDAD_EXTRA:{
        pelota->aumentarVelocidad();
        tiempoVeloz=10;
        break;
    }
    case VIDA_EXTRA:{
        if(vidas!=3){
            vidas++;
        }
        break;
    }
    case PELOTA_EXTRA:{
        break;
    }
    }
}
void Juego::eliminarPowerUp(NodoPowerUp* nodo) {
    if (nodo == nullptr){
        return;
    }

    if (nodo->anterior != nullptr) {
        nodo->anterior->siguiente = nodo->siguiente;
    } else {
        inicio = nodo->siguiente;
    }

    if (nodo->siguiente != nullptr) {
        nodo->siguiente->anterior = nodo->anterior;
    } else {
        fin = nodo->anterior;
    }

    if (nodo->powerUp != nullptr) {
        if (nodo->powerUp->getGrafico() != nullptr) {
            escena->removeItem(nodo->powerUp->getGrafico());
        }
        delete nodo->powerUp;
    }

    delete nodo;
}

void Juego::crearPelotaExtra(){
    Pelota* nuevaPelota = new Pelota();

    nuevaPelota->getGrafico()->setPos(pelota->getGrafico()->pos());

    escena->addItem(nuevaPelota->getGrafico());

    NodoPelota* nuevoNodo = new NodoPelota;

    nuevoNodo->pelota = nuevaPelota;
    nuevoNodo->anterior = nullptr;
    nuevoNodo->siguiente = pelotaInicio;

    if(pelotaInicio != nullptr){
        pelotaInicio->anterior = nuevoNodo;
    }
    else{
        pelotaFin = nuevoNodo;
    }

    pelotaInicio = nuevoNodo;
}

bool Juego::eventFilter(QObject* objeto, QEvent* evento)
{

    if(vidas==0 || cantBloques==0){
        return QObject::eventFilter(objeto,evento);
    }

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
    for(int i=0;i<FILAS;i++){
        delete[] bloques[i];
    }
    for(int i=0;i<3;i++){
        delete corazones[i];
    }
    delete[] bloques;

}
