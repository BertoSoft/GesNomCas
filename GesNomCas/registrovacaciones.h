#ifndef REGISTROVACACIONES_H
#define REGISTROVACACIONES_H

#include <QDialog>

namespace Ui {
class RegistroVacaciones;
}

class RegistroVacaciones : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroVacaciones(QWidget *parent = nullptr);
    ~RegistroVacaciones();

    void initSps();
    void initTable();
    void initUi();
    void mostrarResumenAnual();
    void initVacacionesPendientes();
    void mostrarListado();

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::RegistroVacaciones *ui;
};

#endif // REGISTROVACACIONES_H
