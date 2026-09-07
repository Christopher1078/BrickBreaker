#include "usermanager.h"

#include <filesystem>
#include <fstream>
#include <iostream>

UserManager::UserManager() {
    actual=nullptr;
    cantidad=0;
    std::filesystem::create_directory("Usuarios");
    inicializarArreglo();
    for(int i=cantidad;i<limite;i++){
        usuarios[i]=nullptr;
    }
}

bool UserManager::crearCuenta(std::string nombre, std::string password){
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
    guardarArreglo();
    return true;
}

bool UserManager::iniciarSesion(std::string nombre, std::string password){
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

void UserManager::guardarArreglo(){
    for(int i=0;i<cantidad;i++){
        std::filesystem::create_directory("Usuarios/"+usuarios[i]->getNombre());
        std::ofstream archivo("Usuarios/"+usuarios[i]->getNombre()+"/usuario.txt",std::ios::trunc);
        std::ofstream archivoBin("Usuarios/"+usuarios[i]->getNombre()+"/datos.dat",std::ios::trunc | std::ios::binary);
        if(!archivo.is_open() || !archivoBin.is_open()){
            continue;
        }
        archivo << usuarios[i]->getNombre() << DELIMITADOR
                << usuarios[i]->getPassword() << DELIMITADOR
                << usuarios[i]->getUltimoNivel() << "\n";

        for(int j=0;j<5;j++){
            int estrella=usuarios[i]->getEstrellas(j);
            archivoBin.write(reinterpret_cast<char*>(&estrella), sizeof(estrella));
        }

        for(int j=0;j<5;j++){
            int mejor=usuarios[i]->getMejorPuntaje(j);
            archivoBin.write(reinterpret_cast<char*>(&mejor), sizeof(mejor));
        }

        archivoBin.close();
        archivo.close();
    }
}

void UserManager::inicializarArreglo(){
    for(const auto& entrada: std::filesystem::directory_iterator("Usuarios")){
        int nivel;
        Usuario* usuario;
        std::filesystem::path ruta=entrada.path()/"usuario.txt";
        std::filesystem::path rutaBin=entrada.path()/"datos.dat";
        std::ifstream archivo (ruta);
        std::ifstream archivoBin(rutaBin, std::ios::binary);
        if(!archivo.is_open() || !archivoBin.is_open()){
            continue;
        }
        std::string linea;
        getline(archivo,linea);
        size_t p1=linea.find(DELIMITADOR);
        size_t p2=linea.find(DELIMITADOR,p1+1);
        if(p1==std::string::npos || p1==std::string::npos){
            continue;
        }

        std::string nombre=linea.substr(0,p1);
        std::string password=linea.substr(p1+1,p2-(p1+1));
        std::string nivelTxt=linea.substr(p2+1);
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

        for(int i=0;i<5;i++){
            int estrella;
            archivoBin.read(reinterpret_cast<char*>(&estrella), sizeof(estrella));
            usuarios[cantidad]->setEstrellas(estrella,i);
        }

        for(int i=0;i<5;i++){
            int puntaje;
            archivoBin.read(reinterpret_cast<char*>(&puntaje), sizeof(puntaje));
            usuarios[cantidad]->setMejorPuntaje(puntaje,i);
        }

        cantidad++;
        archivo.close();
        archivoBin.close();
    }
}

int UserManager::buscarUsuario(std::string nombre){
    std::string nombreMinuscula=convertirAMinusculas(nombre);
    for(int i=0;i<cantidad;i++){
        if(nombreMinuscula==convertirAMinusculas(usuarios[i]->getNombre())){
            return i;
        }
    }
    return -1;
}

std::string UserManager::convertirAMinusculas(std::string textoOriginal){
    std::string resultado=textoOriginal;
    for(size_t i=0;i<resultado.length();i++){
        resultado[i]=static_cast<char>(tolower(static_cast<unsigned char>(resultado[i])));
    }
    return resultado;
}

void UserManager::cerrarSesion(){
    actual=nullptr;
}

Usuario* UserManager::getActual(){
    return actual;
}

UserManager::~UserManager(){
    for (int i = 0; i < cantidad; i++) {
        delete usuarios[i];
    }
}

