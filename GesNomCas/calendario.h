#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <QDialog>

namespace Ui {
class Calendario;
}

class Calendario : public QDialog
{
    Q_OBJECT

public:
    explicit Calendario(QWidget *parent = nullptr);
    ~Calendario();

    QString strFecha;

private slots:
    void on_btnCancelar_clicked();

    void on_btnGuardar_clicked();

    void on_calCalendario_activated(const QDate &date);

private:
    Ui::Calendario *ui;
};

#endif // CALENDARIO_H
