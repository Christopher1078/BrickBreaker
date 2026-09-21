#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;
class Usuario
{
public:
    Usuario(string nombre, string password);
    string getNombre();
    string getPassword();
    void pasarNivel();
    int getUltimoNivel();
    bool isPasado(int nivel);
    int getMejorPuntaje(int nivel);
    int getEstrellas(int nivel);
    void setMejorPuntaje(int puntaje, int nivel);
    void setEstrellas(int estrella, int nivel);
private:
    string nombre;
    string password;
    bool niveles[5];
    int estrellas[5];
    int mejorPuntaje[5];
};

#endif // USUARIO_H
