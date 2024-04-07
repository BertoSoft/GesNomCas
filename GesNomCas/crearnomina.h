#ifndef CREARNOMINA_H
#define CREARNOMINA_H

#include <QDialog>

#include "funcaux.h"

namespace Ui {
class CrearNomina;
}

class CrearNomina : public QDialog
{
    Q_OBJECT

public:
    explicit CrearNomina(QWidget *parent = nullptr);
    ~CrearNomina();

    //
    // Structuras
    //
    struct DatosCrearNomina{
        QString codigo;
        QString clave;
        QString denominacion;
        QString cantidad;
        QString precio;
        QString importe;
    };


    QString                         strDiasTotales;
    QString                         strTransportes;
    QString                         strAsistencias;
    QString                         strTurnicidad;
    QString                         strHed;
    QString                         strHen;
    QString                         strHef;
    QString                         strToxicos;
    QString                         strCteProrrateo;
    QString                         strIrpf;

    double                          dRemuneracion           = 0.0;
    double                          dRemuneracionPE         = 0.0;
    double                          dBaseCotizacion         = 0.0;
    double                          dProrrateoPagasExtra    = 0.0;
    double                          dDeducciones            = 0.0;
    double                          dIrpf                   = 0.0;

    QString                         strMes;
    QString                         strAno;

    void                            initUi();
    void                            initTable();
    void                            salir();
    void                            guardar();
    QList<DatosCrearNomina>         getListaNomina();
    FuncAux::DatosRetribuciones     getRetribucion(QString);





private slots:
    void on_btnCancelar_clicked();

    void on_btnGuardar_clicked();

private:
    Ui::CrearNomina *ui;
};

#endif // CREARNOMINA_H
