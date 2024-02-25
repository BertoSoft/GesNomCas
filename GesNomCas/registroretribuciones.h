#ifndef REGISTRORETRIBUCIONES_H
#define REGISTRORETRIBUCIONES_H

#include <QDialog>

namespace Ui {
class RegistroRetribuciones;
}

class RegistroRetribuciones : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroRetribuciones(QWidget *parent = nullptr);
    ~RegistroRetribuciones();

    void initUi();
    void salir();
    void guardar();
    void initChks();
    void controlesClean();
    void controlesOn();
    void controlesOff();

private slots:
    void on_btnCancelar_clicked();

    void on_cmbClave_activated(int index);

    void on_btnEliminar_clicked();

    void on_btnAdd_clicked();

    void on_txtCodigo_returnPressed();

    void on_txtDenominacion_returnPressed();

    void on_txtCuantia_returnPressed();

    void on_btnGuardar_clicked();

    void on_txtCodigo_textChanged(const QString &arg1);

    void on_txtCodigo_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::RegistroRetribuciones *ui;
};

#endif // REGISTRORETRIBUCIONES_H
