#ifndef MODOFICARINCIDENCIAS_H
#define MODOFICARINCIDENCIAS_H

#include "funcaux.h"

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ModoficarIncidencias;
}

class ModoficarIncidencias : public QDialog
{
    Q_OBJECT

public:
    explicit ModoficarIncidencias(QWidget *parent = nullptr);
    ~ModoficarIncidencias();

    void                                initSp();
    void                                initUi();
    void                                limpiarEts();
    void                                refrescarListado();
    QList<FuncAux::DatosIncidencias>    ordenarLista(QList<FuncAux::DatosIncidencias>);

private slots:
    void on_btnModificar_clicked();

    void on_btnVolver_clicked();

    void on_cmbMes_activated(int index);

    void on_cmbAno_activated(int index);

    void on_listIncidencias_itemClicked(QListWidgetItem *item);

    void on_tbAdd_clicked();

    void on_tbEliminar_clicked();

    void on_etHed_returnPressed();

    void on_etHen_returnPressed();

    void on_etHef_returnPressed();

    void on_etToxicos_returnPressed();

    void on_listIncidencias_itemDoubleClicked(QListWidgetItem *item);

    void on_etFecha_returnPressed();

    void on_tbFecha_clicked();

private:
    Ui::ModoficarIncidencias *ui;
};

#endif // MODOFICARINCIDENCIAS_H
