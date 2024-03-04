#include "calendario.h"
#include "ui_calendario.h"

#include <QTextCharFormat>

Calendario::Calendario(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Calendario)
{
    ui->setupUi(this);

}

Calendario::~Calendario()
{
    delete ui;
}

void Calendario::on_btnCancelar_clicked(){

    this->close();
}

void Calendario::on_btnGuardar_clicked(){
    QDate   datFecha;
    QLocale qlTraductor;

    datFecha = ui->calCalendario->selectedDate();
    strFecha = qlTraductor.toString(datFecha,"dd/MM/yyyy");

    this->close();

}

void Calendario::on_calCalendario_activated(const QDate &date){

    on_btnGuardar_clicked();
}

