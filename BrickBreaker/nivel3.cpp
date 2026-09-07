#include "nivel3.h"

Nivel3::Nivel3(QGraphicsScene* escena, QGraphicsView* vista, UserManager* manager):Juego(escena,vista,manager) {
    tiempoObjetivo=210;
    bonusObjetivo=1500;
    nivel=2;
    FILAS=7;
    COLUMNAS=12;

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
                if(j==0|| j==1 || j==4 || j==5 || j==7| j==9 || j==10 || j==13 || j==14){
                    continue;
                }
                ruta=(":/imagenes/bloque_morado.png");
                break;
            }
            case 1:{
                if(j==0 || j==3 || j==4 || j==5 || j==9 || j==10 || j==11 || j==14){
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
                ruta=(":/imagenes/bloque_naranja.png");
                break;
            }
            case 4:{
                if(j==2 || j==4 || j==10 || j==12){
                    continue;
                }
                ruta=(":/imagenes/bloque_rojo.png");
                break;
            }
            case 5:{
                if(j==0 || j==2 || j==3 || j==4 || j==5 || j==9 || j==10 || j==11 || j==12 || j==14){
                    continue;
                }
                ruta=(":/imagenes/bloque_rojo.png");
                break;
            }
            case 6:{
                if(j==0 || j==1 || j==3 || j==4 || j==5 || j==6 || j==8 || j==9 || j==10 || j==11 || j==13 || j==14){
                    continue;
                }
                ruta=(":/imagenes/bloque_morado.png");
            }
            }
            cantBloques++;
            bloques[i][j].inicializar(x,y,ruta);
            escena->addItem(bloques[i][j].getGrafico());
        }
    }
    iniciarTimer();
}
