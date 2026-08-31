#ifndef USERMANAGER_H
#define USERMANAGER_H

#include<windows.h>

#include "usuario.h"

class UserManager
{
public:
    UserManager();
    bool iniciarSesion(string nombre, string password);
    bool crearCuenta(string nombre, string password);
    void guardarArreglo(Usuario* usuarios[]);
    Usuario* getActual();
    int buscarUsuario(string nombre);
    void inicializarArreglo();
    string convertirAMinusculas(string textoOriginal);
    void cerrarSesion();
private:
    Usuario* actual;
    Usuario* usuarios[100];
    int cantidad;
    const char DELIMITADOR='|';
    const int limite=100;
};

#endif // USERMANAGER_H
