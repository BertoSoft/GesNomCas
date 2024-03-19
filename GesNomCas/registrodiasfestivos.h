#ifndef REGISTRODIASFESTIVOS_H
#define REGISTRODIASFESTIVOS_H

#include "funcaux.h"

#include <QDialog>
#include <QTableWidgetItem>
#include <QDate>

namespace Ui {
class RegistroDiasFestivos;
}

class RegistroDiasFestivos : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroDiasFestivos(QWidget *parent = nullptr);
    ~RegistroDiasFestivos();

    //
    // Colores
    //
    QColor colorNacional        = QColor(255, 255, 0);
    QColor colorAutonomico      = QColor(0, 255, 0);
    QColor colorLocal           = QColor(0, 0, 255);
    QColor colorConvenio        = QColor(125, 125, 125);
    QColor colorExcesoJornada   = QColor(125, 255, 255);


    void initUi();
    void initTable();
    void initSp();
    void mostrarExcesosJornada();
    void mostrarListado();
    QList<FuncAux::DatosFestivos> ordenarLista(QList<FuncAux::DatosFestivos>);
    void salir();
    void guardar();

private slots:
    void on_btnCancelar_clicked();

    void on_cmbAno_activated(int index);

    void on_btnAdd_clicked();

    void on_btnGuardar_clicked();

    void on_txtFecha_returnPressed();

    void on_txtFecha_textChanged(const QString &arg1);

    void on_cmbFestivo_activated(int index);

    void on_toolButton_clicked();

    void on_btnEliminar_clicked();

    void on_tableFestivos_itemClicked(QTableWidgetItem *item);

    void on_tableFestivos_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::RegistroDiasFestivos *ui;
};

#endif // REGISTRODIASFESTIVOS_H
