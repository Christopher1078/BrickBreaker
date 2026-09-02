#include "usermanager.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <qlogging.h>

UserManager::UserManager() {
    actual=nullptr;
    cantidad=0;
    filesystem::create_directory("Usuarios");
    inicializarArreglo();
    for(int i=cantidad;i<limite;i++){
        usuarios[i]=nullptr;
    }
}

bool UserManager::crearCuenta(string nombre, string password){
    if(buscarUsuario(nombre)!=-1){
        MessageBox(NULL,TEXT("YA EXISTE ESE NOMBRE DE USUARIO"),TEXT("ERROR"),MB_OK);
        return false;
    }
    if(cantidad>=limite){
        MessageBox(NULL,TEXT("SE HA LLEGADO AL LIMITE DE USUARIOS"),TEXT("ERROR"),MB_OK);
        return false;
    }
    actual=new Usuario{nombre,password};
    usuarios[cantidad]=actual;
    cantidad++;
    guardarArreglo(usuarios);
    return true;
}

bool UserManager::iniciarSesion(string nombre, string password){
    int indice=buscarUsuario(nombre);
    if(indice==-1){
        MessageBox(NULL,TEXT("NO EXISTE EL USUARIO"), TEXT("ERROR"), MB_OK);
        return false;
    }
    if(usuarios[indice]->getPassword()!=password){
        MessageBox(NULL,TEXT("PASSWORD INCORRECTO"), TEXT("INCORRECTO"), MB_OK);
        return false;
    }

    actual=usuarios[indice];
    return true;
}

void UserManager::guardarArreglo(Usuario* usuarios[]){
    for(int i=0;i<cantidad;i++){
        filesystem::create_directory("Usuarios/"+usuarios[i]->getNombre());
        ofstream archivo("Usuarios/"+usuarios[i]->getNombre()+"/usuario.txt",ios::trunc);
        if(!archivo.is_open()){
            continue;
        }
        archivo << usuarios[i]->getNombre() << DELIMITADOR
                << usuarios[i]->getPassword() << DELIMITADOR
                << usuarios[i]->getUltimoNivel() << "\n";
        archivo.close();
    }
}

void UserManager::inicializarArreglo(){
    for(const auto& entrada: filesystem::directory_iterator("Usuarios")){
        int nivel;
        Usuario* usuario;
        filesystem::path ruta=entrada.path()/"usuario.txt";
        ifstream archivo (ruta);
        if(!archivo.is_open()){
            continue;
        }
        string linea;
        getline(archivo,linea);
        size_t p1=linea.find(DELIMITADOR);
        size_t p2=linea.find(DELIMITADOR,p1+1);
        if(p1==string::npos || p1==string::npos){
            continue;
        }

        string nombre=linea.substr(0,p1);
        string password=linea.substr(p1+1,p2-(p1+1));
        string nivelTxt=linea.substr(p2+1);
        try {
            nivel=stoi(nivelTxt);
        } catch (...) {
            continue;
        }

        usuario=new Usuario{nombre,password};
        for(int i=0;i<nivel;i++){
            usuario->pasarNivel();
        }
        usuarios[cantidad]=usuario;
        cantidad++;
        archivo.close();
    }
}

int UserManager::buscarUsuario(string nombre){
    string nombreMinuscula=convertirAMinusculas(nombre);
    for(int i=0;i<cantidad;i++){
        if(nombreMinuscula==convertirAMinusculas(usuarios[i]->getNombre())){
            return i;
        }
    }
    return -1;
}

string UserManager::convertirAMinusculas(string textoOriginal){
    string resultado=textoOriginal;
    for(size_t i=0;i<resultado.length();i++){
        resultado[i]=static_cast<char>(tolower(static_cast<unsigned char>(resultado[i])));
    }
    return resultado;
}

void UserManager::cerrarSesion(){
    actual=nullptr;
}

