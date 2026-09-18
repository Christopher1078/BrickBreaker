#include <QApplication>

#include "menuinicio.h"
#include "audiomanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    AudioManager::instancia().reproducirMusica();

    MenuInicio menuInicio;

    return app.exec();
}