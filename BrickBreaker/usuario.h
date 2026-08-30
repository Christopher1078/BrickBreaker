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
private:
    string nombre;
    string password;
};

#endif // USUARIO_H
