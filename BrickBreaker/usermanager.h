#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <windows.h>

#include "usuario.h"

class UserManager
{
public:
    UserManager();
    ~UserManager();
    bool iniciarSesion(std::string nombre, std::string password);
    bool crearCuenta(std::string nombre, std::string password);
    void guardarArreglo();
    Usuario* getActual();
    int buscarUsuario(std::string nombre);
    void inicializarArreglo();
    std::string convertirAMinusculas(std::string textoOriginal);
    void cerrarSesion();
private:
    Usuario* actual;
    Usuario* usuarios[100];
    int cantidad;
    const char DELIMITADOR='|';
    const int limite=100;
};

#endif // USERMANAGER_H
