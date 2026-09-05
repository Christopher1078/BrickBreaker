#ifndef NIVEL3_H
#define NIVEL3_H
#include<QObject>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QEvent>
#include <QVector>
#include <QPixmap>
#include <QString>

#include "pelota.h"
#include "paleta.h"

class Nivel3 : public QObject
{
    Q_OBJECT

private:
    struct BloqueNivel3
    {
        QGraphicsPixmapItem* grafico;
        bool destruido;
    };

    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;

    Pelota* pelota;
    Paleta* paleta;

    QVector<BloqueNivel3> bloques;

    void crearBloque(int columna, int fila, const QString& imagen);
    void crearBloques();

public:
    Nivel3(QGraphicsScene* escena, QGraphicsView* vista);
    ~Nivel3();

    void actualizar();

protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};
#endif // NIVEL3_H
