#include "usuario.h"

Usuario::Usuario(string nombre, string password) {
    this->nombre=nombre;
    this->password=password;
}

string Usuario::getNombre(){
    return nombre;
}

string Usuario::getPassword(){
    return password;
}
