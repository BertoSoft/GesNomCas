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

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::RegistroDiasFestivos *ui;
};

#endif // REGISTRODIASFESTIVOS_H
