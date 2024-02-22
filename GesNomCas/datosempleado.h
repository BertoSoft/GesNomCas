#ifndef DATOSEMPLEADO_H
#define DATOSEMPLEADO_H

#include <QDialog>

namespace Ui {
class DatosEmpleado;
}

class DatosEmpleado : public QDialog
{
    Q_OBJECT

public:
    explicit DatosEmpleado(QWidget *parent = nullptr);
    ~DatosEmpleado();

    void initUi();
    void guardar();
    void salir();
    void rellenaCampos();

private slots:
    void on_txtEmpleado_returnPressed();

    void on_txtCategoria_returnPressed();

    void on_txtIngreso_returnPressed();

    void on_txtNif_returnPressed();

    void on_txtPuesto_returnPressed();

    void on_txtNumeroAfiliacion_returnPressed();

    void on_txtGrupoCotizacion_returnPressed();

    void on_txtCodigoOcupacion_returnPressed();

    void on_txtContrato_returnPressed();

    void on_txtFinContrato_returnPressed();

    void on_btnCancelar_clicked();

    void on_btnGuardar_clicked();

private:
    Ui::DatosEmpleado *ui;
};

#endif // DATOSEMPLEADO_H
