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

    void initUi();
    void initSp();
    void mostrarExcesosJornada();
    void salir();

private slots:
    void on_btnCancelar_clicked();

    void on_cmbAno_activated(int index);

private:
    Ui::RegistroDiasFestivos *ui;
};

#endif // REGISTRODIASFESTIVOS_H
