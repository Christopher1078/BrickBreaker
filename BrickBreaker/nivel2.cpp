#include "nivel2.h"

Nivel2::Nivel2(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena,vista,manager) {
    tiempoObjetivo=150;
    bonusObjetivo=1500;
    nivel=1;

    bloques=new Bloque*[FILAS];
    for(int i=0;i<FILAS;i++){
        bloques[i]=new Bloque[COLUMNAS];
    }

    for(int i=0;i<FILAS;i++){
        for(int j=0;j<COLUMNAS;j++){
            float x=j*90+40;
            float y=i*50+40;
            std::string ruta;

            if((j==0 || j==7) && i!=4){
                bloques[i][j].setMetalico();
                cantBloques--;
            }

            switch(i){
            case 0:{
                if(j==3 || j==4){
                    bloques[i][j].setBlindado();
                }
                ruta=(":/imagenes/bloque_morado.png");
                break;
            }
            case 1:{
                if(j==2 || j==5){
                    bloques[i][j].setBlindado();
                }
                ruta=(":/imagenes/bloque_azul.png");
                break;
            }
            case 2:{
                if(j==4){
                    bloques[i][j].setPowerUp(2);
                }
                ruta=(":/imagenes/bloque_verde.png");
                break;
            }
            case 3:{
                if(j==1 || j==6){
                    bloques[i][j].setBlindado();
                }
                if(j==4){
                    bloques[i][j].setPowerUp(5);
                }
                ruta=(":/imagenes/bloque_naranja.png");
                break;
            }
            case 4:{
                continue;
            }
            }
            cantBloques++;
            bloques[i][j].inicializar(x,y,ruta);
            escena->addItem(bloques[i][j].getGrafico());
        }
    }
    iniciarTimer();
}
