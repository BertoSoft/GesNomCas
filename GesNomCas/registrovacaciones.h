#ifndef REGISTROVACACIONES_H
#define REGISTROVACACIONES_H

#include <QDialog>
#include <QTableWidgetItem>

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
    int  getDiasLaborables(QDate, QDate);
    void mostrarResumenAnual();
    void initVacacionesPendientes();
    void mostrarListado();
    void guardar();

private slots:
    void on_btnCancelar_clicked();

    void on_btnGuardar_clicked();

    void on_btnAdd_clicked();

    void on_txtFecha0_returnPressed();

    void on_txtFecha1_returnPressed();

    void on_txtFecha0_textChanged(const QString &arg1);

    void on_txtFecha1_textChanged(const QString &arg1);

    void on_btnEliminar_clicked();

    void on_tableVacaciones_itemClicked(QTableWidgetItem *item);

    void on_tableVacaciones_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::RegistroVacaciones *ui;
};

#endif // REGISTROVACACIONES_H
