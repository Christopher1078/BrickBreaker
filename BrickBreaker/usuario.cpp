#include "usuario.h"

Usuario::Usuario(string nombre, string password) {
    this->nombre=nombre;
    this->password=password;
    niveles[0]=true;
    for(int i=1;i<5;i++){
        niveles[i]=false;
    }
}

string Usuario::getNombre(){
    return nombre;
}

string Usuario::getPassword(){
    return password;
}

void Usuario::pasarNivel(){
    int siguiente=getUltimoNivel()+1;
    if(siguiente>=5){
        return;
    }
    niveles[getUltimoNivel()+1]=true;
}

int Usuario::getUltimoNivel(){
    for(int i=1;i<5;i++){
        if(!niveles[i]){
            return i-1;
        }
    }
    return 4;
}

bool Usuario::isPasado(int nivel){
    return niveles[nivel];
}
