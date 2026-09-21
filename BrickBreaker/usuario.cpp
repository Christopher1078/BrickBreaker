#include "usuario.h"


Usuario::Usuario(std::string nombre, std::string password) {
    this->nombre=nombre;
    this->password=password;

    for(int i=0;i<5;i++){
        niveles[i]=false;
        estrellas[i]=0;
        mejorPuntaje[i]=0;
    }
    niveles[0]=true;
}

std::string Usuario::getNombre(){
    return nombre;
}

std::string Usuario::getPassword(){
    return password;
}

void Usuario::pasarNivel(){
    int siguiente=getUltimoNivel()+1;
    if(siguiente>=5){
        return;
    }
    niveles[siguiente]=true;
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

int Usuario::getEstrellas(int nivel){
    return estrellas[nivel];
}

int Usuario::getMejorPuntaje(int nivel){
    return mejorPuntaje[nivel];
}

void Usuario::setEstrellas(int estrella, int nivel){
    if(estrella>estrellas[nivel]){
        estrellas[nivel]=estrella;
    }
}

void Usuario::setMejorPuntaje(int puntaje, int nivel){
    if(puntaje>mejorPuntaje[nivel]){
        mejorPuntaje[nivel]=puntaje;
    }
}