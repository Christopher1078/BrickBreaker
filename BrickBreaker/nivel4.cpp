#include "nivel4.h"

Nivel4::Nivel4(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena,vista,manager) {
    tiempoObjetivo=210;
    bonusObjetivo=1500;
    nivel=1;
    FILAS=16;
    COLUMNAS=11;

    bloques=new Bloque*[FILAS];
    for(int i=0;i<FILAS;i++){
        bloques[i]=new Bloque[COLUMNAS];
    }

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            float x=j*60+40;
            float y=i*30+40;
            std::string ruta;

            switch(i){
            case 0:{
                ruta=(":/imagenes/bloque_morado.png");
                break;
            }
            case 1:{
                ruta=(":/imagenes/bloque_azul.png");
                break;
            }
            case 2:{
                ruta=(":/imagenes/bloque_verde.png");
                break;
            }
            case 3:{
                ruta=(":/imagenes/bloque_naranja.png");
                break;
            }
            case 4:{
                ruta=(":/imagenes/bloque_rojo.png");
            }
            }
            cantBloques++;
            bloques[i][j].inicializar(x,y,ruta);
            escena->addItem(bloques[i][j].getGrafico());
        }
    }
    iniciarTimer();
}
