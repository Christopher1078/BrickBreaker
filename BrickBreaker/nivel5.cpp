#include "nivel5.h"

Nivel5::Nivel5(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena,vista,manager) {
    tiempoObjetivo=180;
    bonusObjetivo=1500;
    nivel=4;

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
                if(j==1 || j==6){
                    bloques[i][j].setBlindado();
                }
                if(j==2 || j==5){
                    continue;
                }
                if(j==3){
                    bloques[i][j].setMovil(220,390);
                }
                if(j==4){
                    bloques[i][j].setMovil(400,570);
                }
                ruta=(":/imagenes/bloque_morado.png");
                break;
            }
            case 1:{
                if(j==2 || j==5){
                    bloques[i][j].setBlindado();
                }
                if(j==4){
                    bloques[i][j].setPowerUp(6);
                }
                if(j==6){
                    bloques[i][j].setPowerUp(7);
                }
                ruta=(":/imagenes/bloque_azul.png");
                break;
            }
            case 2:{
                if(j==3 || j==4){
                    bloques[i][j].setBlindado();
                }
                if(j==2 || j==5){
                    continue;
                }
                if(j==1){
                    bloques[i][j].setMovil(130,300);
                }
                if(j==6){
                    bloques[i][j].setMovil(500,670);
                }
                if(j==7){
                    bloques[i][j].setPowerUp(5);
                }
                ruta=(":/imagenes/bloque_verde.png");
                break;
            }
            case 3:{
                if(j==1 || j==6){
                    bloques[i][j].setBlindado();
                }
                if(j==3){
                    bloques[i][j].setPowerUp(1);
                }
                if(j==4){
                    bloques[i][j].setPowerUp(4);
                }
                ruta=(":/imagenes/bloque_naranja.png");
                break;
            }
            case 4:{
                if(j==3){
                    bloques[i][j].setPowerUp(3);
                }
                if(j==2 || j==5 || j==0 || j==7){
                    bloques[i][j].setMetalico();
                    cantBloques--;
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
