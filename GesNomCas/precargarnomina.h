#ifndef PRECARGARNOMINA_H
#define PRECARGARNOMINA_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class PreCargarNomina;
}

class PreCargarNomina : public QDialog
{
    Q_OBJECT

public:
    explicit PreCargarNomina(QWidget *parent = nullptr);
    ~PreCargarNomina();

    QString strMes;
    QString strAno;

    void initUi();
    void initSp();
    void rellenaListado();
    void guardar();

private slots:
    void on_btnCancelar_clicked();

    void on_btnCargar_clicked();

    void on_cmbAno_activated(int index);

    void on_listNominas_itemClicked(QListWidgetItem *item);

    void on_listNominas_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::PreCargarNomina *ui;
};

#endif // PRECARGARNOMINA_H
