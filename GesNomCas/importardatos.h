#ifndef IMPORTARDATOS_H
#define IMPORTARDATOS_H

#include <QDialog>

namespace Ui {
class importarDatos;
}

class importarDatos : public QDialog
{
    Q_OBJECT

public:
    explicit importarDatos(QWidget *parent = nullptr);
    ~importarDatos();

    QString NOMBRE_PROGRAMA;

    void initUi();

private slots:

    void on_btnCancelar_clicked();

    void on_btnImportar_clicked();


    void on_btnAbrirArchivo_clicked();

private:
    Ui::importarDatos *ui;
};

#endif // IMPORTARDATOS_H
