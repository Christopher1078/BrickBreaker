#ifndef NIVEL2_H
#define NIVEL2_H

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

class Nivel2 : public QObject
{
    Q_OBJECT

private:
    struct BloqueNivel2
    {
        QGraphicsPixmapItem* grafico;
        bool destruido;
    };

    QGraphicsScene* escena;
    QGraphicsView* vista;
    QTimer* timer;

    Pelota* pelota;
    Paleta* paleta;

    QVector<BloqueNivel2> bloques;

    void crearBloque(int columna, int fila, const QString& imagen);
    void crearBloques();

public:
    Nivel2(QGraphicsScene* escena, QGraphicsView* vista);
    ~Nivel2();

    void actualizar();

protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};

#endif // NIVEL2_H