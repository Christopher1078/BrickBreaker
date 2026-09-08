#include "nivel3.h"

Nivel3::Nivel3(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena,vista,manager) {
    tiempoObjetivo=210;
    bonusObjetivo=1500;
    nivel=2;

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
                if(j==3 || j==4){
                    continue;
                }
                ruta=(":/imagenes/bloque_azul.png");
                break;
            }
            case 2:{
                ruta=(":/imagenes/bloque_verde.png");
                break;
            }
            case 3:{
                if(j==0 || j==7){
                    bloques[i][j].setTipo(1);
                }
                ruta=(":/imagenes/bloque_naranja.png");
                break;
            }
            case 4:{
                if(j>=2 && j<=5){
                    continue;
                }
                ruta=(":/imagenes/bloque_rojo.png");
                break;
            }
            }
            cantBloques++;
            bloques[i][j].inicializar(x,y,ruta);
            escena->addItem(bloques[i][j].getGrafico());
        }
    }
    iniciarTimer();
}
