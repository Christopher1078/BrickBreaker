#include "nivel4.h"

Nivel4::Nivel4(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena,vista,manager) {
    tiempoObjetivo=210;
    bonusObjetivo=1500;
    nivel=3;

    bloques=new Bloque*[FILAS];
    for(int i=0;i<FILAS;i++){
        bloques[i]=new Bloque[COLUMNAS];
    }

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            float x=j*90+40;
            float y=i*50+40;
            std::string ruta;

            switch(i){
            case 0:{
                if(j>=2 && j<=5){
                    bloques[i][j].setTipo(1);
                }
                ruta=(":/imagenes/bloque_morado.png");
                break;
            }
            case 1:{
                ruta=(":/imagenes/bloque_azul.png");
                break;
            }
            case 2:{
                if(j==1 || j==6){
                    bloques[i][j].setTipo(1);
                }
                if(j==4){
                    bloques[i][j].setPowerUp(2);
                }
                ruta=(":/imagenes/bloque_verde.png");
                break;
            }
            case 3:{
                if(j==2 || j==5){
                    bloques[i][j].setTipo(1);
                }
                ruta=(":/imagenes/bloque_naranja.png");
                break;
            }
            case 4:{
                if(j==3){
                    bloques[i][j].setPowerUp(3);
                }
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
