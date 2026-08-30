#include <QApplication>

#include "menuinicio.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MenuInicio menuInicio;

    return app.exec();
}