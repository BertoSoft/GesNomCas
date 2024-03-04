#ifndef REGISTRODIASFESTIVOS_H
#define REGISTRODIASFESTIVOS_H

#include <QDialog>

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
    QColor colorNacional    = QColor(255, 0, 0);
    QColor colorAutonomico  = QColor(0, 255, 0);
    QColor colorLocal       = QColor(0, 0, 255);
    QColor colorConvenio    = QColor(125, 125, 125);

    void initUi();
    void initSp();
    void mostrarExcesosJornada();
    void mostrarListado();
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

private:
    Ui::RegistroDiasFestivos *ui;
};

#endif // REGISTRODIASFESTIVOS_H
