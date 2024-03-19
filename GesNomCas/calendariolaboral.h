#ifndef CALENDARIOLABORAL_H
#define CALENDARIOLABORAL_H

#include <QDialog>
#include <QDate>

namespace Ui {
class CalendarioLaboral;
}

class CalendarioLaboral : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarioLaboral(QWidget *parent = nullptr);
    ~CalendarioLaboral();

    //
    // Colores
    //
    QColor colorNacional        = QColor(255, 255, 0);
    QColor colorAutonomico      = QColor(0, 255, 0);
    QColor colorLocal           = QColor(0, 0, 255);
    QColor colorConvenio        = QColor(125, 125, 125);
    QColor colorExcesoJornada   = QColor(125, 255, 255);

    void        initUi();
    void        initSp();
    void        initCalendario();
    void        dibujaCalendario();
    void        coloreaCalendario();
    QList<int>  dateToPos(QDate);

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::CalendarioLaboral *ui;
};

#endif // CALENDARIOLABORAL_H
