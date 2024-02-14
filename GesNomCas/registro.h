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

    QString NOMBRE_PROGRAMA;

    void initUi();
    void centrar();
    void entrar();
    void salir();

protected:
    bool eventFilter(QObject *, QEvent *);

private slots:

    void on_etUsuario_returnPressed();

    void on_btnSalir_clicked();

    void on_btnLogin_clicked();

    void on_etPasswd_returnPressed();

    void on_etPasswd1_returnPressed();

private:
    Ui::Registro *ui;
};

#endif // REGISTRO_H
