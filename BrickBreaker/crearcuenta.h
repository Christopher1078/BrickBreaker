#ifndef CREARCUENTA_H
#define CREARCUENTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class CrearCuenta: public QObject
{
public:
    CrearCuenta(QGraphicsScene* escena, QGraphicsView* vista);
private:
    QGraphicsScene* escena;
    QGraphicsView* vista;
    QLineEdit* txtNombre;
    QLineEdit* txtPassword;
    QPushButton* btnCrear;
    QPushButton* btnRegresar;
protected:
    bool eventFilter(QObject* objeto, QEvent* evento) override;
};

#endif // CREARCUENTA_H
