#ifndef PRECREARNOMINA_H
#define PRECREARNOMINA_H

#include "funcaux.h"

#include <QDialog>


namespace Ui {
class PreCrearNomina;
}

class PreCrearNomina : public QDialog
{
    Q_OBJECT

public:
    explicit PreCrearNomina(QWidget *parent = nullptr);
    ~PreCrearNomina();

    QString strMes;
    QString strAno;
    QString strDiasTotales;
    QString strAsistencias;
    QString strTransportes;
    QString strTurnicidad;
    QString strHed;
    QString strHen;
    QString strHef;
    QString strToxicos;
    QString strCteProrrateo;
    QString strIrpf;


    void                        initSps();
    void                        initUi();
    void                        refrescaUi();
    void                        guardar();
    int                         getAsistencias();
    int                         getTransportes();
    double                      getIrpf();
    FuncAux::DatosIncidencias   getIncidencias();
    double                      getProrrateo();

protected:

    bool eventFilter(QObject *obj, QEvent *ev);


private slots:
    void on_btnCancelar_clicked();

    void on_btnGuardar_clicked();

    void on_cmbMes_activated(int index);

    void on_cmbAno_activated(int index);

    void on_etDiasTotales_returnPressed();

    void on_etAntiguedad_returnPressed();

    void on_etAsistencias_returnPressed();

    void on_etTransporte_returnPressed();

    void on_etTurnicidad_returnPressed();

    void on_etIrpf_returnPressed();

    void on_etHed_returnPressed();

    void on_etHen_returnPressed();

    void on_etHef_returnPressed();

    void on_etToxicos_returnPressed();

    void on_etProrrateo_returnPressed();

private:
    Ui::PreCrearNomina *ui;
};

#endif // PRECREARNOMINA_H
