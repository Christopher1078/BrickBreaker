#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario
{
public:
    Usuario(std::string nombre, std::string password);
    std::string getNombre();
    std::string getPassword();
    void pasarNivel();
    int getUltimoNivel();
    bool isPasado(int nivel);
private:
    std::string nombre;
    std::string password;
    bool niveles[5];
};

#endif // USUARIO_H
