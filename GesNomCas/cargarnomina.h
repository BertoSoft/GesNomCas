#ifndef CARGARNOMINA_H
#define CARGARNOMINA_H

#include <QDialog>

namespace Ui {
class CargarNomina;
}

class CargarNomina : public QDialog
{
    Q_OBJECT

public:
    explicit CargarNomina(QWidget *parent = nullptr);
    ~CargarNomina();

    //
    // Structuras
    //
    struct DatosTableNomina{
        QString codigo;
        QString clave;
        QString denominacion;
        QString cantidad;
        QString precio;
        QString importe;
    };

    QString strMes;
    QString strAno;

    double                          dRemuneracion           = 0.0;
    double                          dRemuneracionPE         = 0.0;
    double                          dBaseCotizacion         = 0.0;
    double                          dProrrateoPagasExtra    = 0.0;
    double                          dDeducciones            = 0.0;
    double                          dIrpf                   = 0.0;

    void initTable();
    void initUi();

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::CargarNomina *ui;
};

#endif // CARGARNOMINA_H
