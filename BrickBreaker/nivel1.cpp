#include "nivel1.h"

Nivel1::Nivel1(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena, vista) {
    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            float x=j*60+40;
            float y=i*30+25;
            string ruta;

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
            bloques[i][j].inicializar(x,y,ruta);
            escena->addItem(bloques[i][j].getGrafico());
        }
    }
    iniciarTimer();
}


