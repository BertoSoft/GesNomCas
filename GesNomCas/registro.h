#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class Registro;
}

class Registro : public QDialog
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr);
    ~Registro();

    void initUi();
    void centrar();
    void salir();
    void enter();

protected:
    bool eventFilter(QObject *, QEvent *);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_etUsuario_returnPressed();

private:
    Ui::Registro *ui;
};

#endif // REGISTRO_H
