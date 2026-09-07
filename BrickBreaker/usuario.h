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
    int getMejorPuntaje(int nivel);
    int getEstrellas(int nivel);
    void setMejorPuntaje(int puntaje, int nivel);
    void setEstrellas(int estrella, int nivel);
private:
    std::string nombre;
    std::string password;
    bool niveles[5];
    int estrellas[5];
    int mejorPuntaje[5];
};

#endif // USUARIO_H
