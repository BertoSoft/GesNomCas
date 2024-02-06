#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QString nombre_programa;

    void initUi();
    void centrar();
    void salir();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private slots:


    void on_btnSalir_clicked();

    void on_btnLogin_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
