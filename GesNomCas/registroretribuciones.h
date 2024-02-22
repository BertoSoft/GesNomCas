#ifndef REGISTRORETRIBUCIONES_H
#define REGISTRORETRIBUCIONES_H

#include <QDialog>

namespace Ui {
class RegistroRetribuciones;
}

class RegistroRetribuciones : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroRetribuciones(QWidget *parent = nullptr);
    ~RegistroRetribuciones();

    void salir();

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::RegistroRetribuciones *ui;
};

#endif // REGISTRORETRIBUCIONES_H
