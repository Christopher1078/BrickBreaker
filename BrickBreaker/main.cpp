#include <QApplication>

#include "menuinicio.h"
#include "juego.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MenuInicio juego;

    return app.exec();
}