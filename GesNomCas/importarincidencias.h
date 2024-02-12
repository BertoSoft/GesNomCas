#ifndef IMPORTARINCIDENCIAS_H
#define IMPORTARINCIDENCIAS_H

#include <QDialog>

namespace Ui {
class importarincidencias;
}

class importarincidencias : public QDialog
{
    Q_OBJECT

public:
    explicit importarincidencias(QWidget *parent = nullptr);
    ~importarincidencias();

    QString nombrePrograma;

    void initUi();

private slots:
    void on_btnImportar_clicked();

    void on_btnCancelar_clicked();

    void on_btnAbrirArchivo_clicked();

private:
    Ui::importarincidencias *ui;
};

#endif // IMPORTARINCIDENCIAS_H
