#ifndef USUARIO_H
#define USUARIO_H

#include<string>

using namespace std;

class Usuario
{
public:
    Usuario(string nombre, string password);
    string getNombre();
    string getPassword();
    void pasarNivel(int nivel);
    int getUltimoNivel();
    bool isPasado(int nivel);
private:
    string nombre;
    string password;
    bool niveles[5];
};

#endif // USUARIO_H
