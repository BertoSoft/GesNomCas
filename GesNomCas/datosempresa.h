#ifndef DATOSEMPRESA_H
#define DATOSEMPRESA_H

#include <QDialog>

namespace Ui {
class DatosEmpresa;
}

class DatosEmpresa : public QDialog
{
    Q_OBJECT

public:
    explicit DatosEmpresa(QWidget *parent = nullptr);
    ~DatosEmpresa();

    void initUi();
    void guardar();
    void salir();
    void rellenaCampos();

private slots:
    void on_txtEmpresa_returnPressed();

    void on_txtDomicilio_returnPressed();

    void on_txtNumeroPatronal_returnPressed();

    void on_txtCentroTrabajo_returnPressed();

    void on_txtCif_returnPressed();

    void on_txtActividad_returnPressed();

    void on_txtConvenio_returnPressed();

    void on_btnCancelar_clicked();

    void on_btnGuardar_clicked();

private:
    Ui::DatosEmpresa *ui;
};

#endif // DATOSEMPRESA_H
