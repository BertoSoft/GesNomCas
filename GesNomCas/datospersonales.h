#ifndef DATOSPERSONALES_H
#define DATOSPERSONALES_H

#include <QDialog>

namespace Ui {
class DatosPersonales;
}

class DatosPersonales : public QDialog
{
    Q_OBJECT

public:
    explicit DatosPersonales(QWidget *parent = nullptr);
    ~DatosPersonales();

    void initUi();

private slots:
    void on_btnCancelar_clicked();

    void on_txtNombre_returnPressed();

    void on_txtApellidos_returnPressed();

    void on_txtDireccion_returnPressed();

    void on_txtCodigoPostal_returnPressed();

    void on_txtPoblacion_returnPressed();

    void on_txtPais_returnPressed();

    void on_btnGuardar_clicked();

    void on_txtProvincia_returnPressed();

private:
    Ui::DatosPersonales *ui;
};

#endif // DATOSPERSONALES_H
