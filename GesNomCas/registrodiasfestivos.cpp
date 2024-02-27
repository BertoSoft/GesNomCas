#include "registrodiasfestivos.h"
#include "ui_registrodiasfestivos.h"

#include "funcaux.h"

#include <QDate>
#include <QLocale>

RegistroDiasFestivos::RegistroDiasFestivos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroDiasFestivos)
{
    ui->setupUi(this);

    initSp();
    initUi();
}

RegistroDiasFestivos::~RegistroDiasFestivos(){
    delete ui;
}

void RegistroDiasFestivos::initUi(){

    ui->frameFestivos->setEnabled(false);
    ui->btnGuardar->setEnabled(false);
    mostrarExcesosJornada();
}

void RegistroDiasFestivos::initSp(){
    QDate   qdFecha;
    int     iAno;
    int     iLimite;

    //
    // Colocamos el año actual, uno despues y 10 anteriores
    //
    qdFecha = QDate::currentDate();
    iAno    = qdFecha.year();
    iLimite = iAno - 10;
    iAno++;
    while (iAno>iLimite) {
        ui->cmbAno->addItem(QString::number(iAno));
        iAno--;
    }

    //
    // Colocamos los tipos de festivos
    //
    ui->cmbFestivo->addItem("Nacional");
    ui->cmbFestivo->addItem("Autonómico");
    ui->cmbFestivo->addItem("Locale");
    ui->cmbFestivo->addItem("Convenio");

}

void RegistroDiasFestivos::mostrarExcesosJornada(){
    QDate   qdFecha;
    QString str;
    int     iDiasAno;
    int     iSabados;
    int     iDomingos;
    int     iNacionales;
    int     iAutonomicos;
    int     iLocales;
    int     iLaborables;
    int     iHorasLaborables;
    int     iHorasVacaciones = 176;
    int     iHorasExceso;
    int     iDiasExceso;

    qdFecha.setDate(ui->cmbAno->currentText().toInt(), 1, 1);

    iDiasAno            = qdFecha.daysInYear();
    iSabados            = FuncAux().getSabados(ui->cmbAno->currentText()).toInt();
    iDomingos           = FuncAux().getDomingos(ui->cmbAno->currentText()).toInt();
    iNacionales         = FuncAux().getFestivosNacionales(ui->cmbAno->currentText()).toInt();
    iAutonomicos        = FuncAux().getFestivosAutonomicos(ui->cmbAno->currentText()).toInt();
    iLocales            = FuncAux().getFestivosLocales(ui->cmbAno->currentText()).toInt();
    iLaborables         = iDiasAno - iSabados - iDomingos - iNacionales - iAutonomicos - iLocales - 1;
    iHorasLaborables    = iLaborables * 8;
    iHorasExceso        = iHorasLaborables - iHorasVacaciones - 1752;
    iDiasExceso         = iHorasExceso / 8;

    ui->lblSabados->setText(QString::number(iSabados));
    ui->lblDomingos->setText(QString::number(iDomingos));
    ui->lblNacionales->setText(QString::number(iNacionales));
    ui->lblAutonomicos->setText(QString::number(iAutonomicos));
    ui->lblLocales->setText(QString::number(iLocales));
    ui->lblConvenio->setText("1");

    //(366 -52 -52 -8 -2 -2 -1) x 8 Horas = 1992 Horas
    str = "(";
    str.append(QString::number(iDiasAno));
    str.append("-");
    str.append(QString::number(iSabados));
    str.append("-");
    str.append(QString::number(iDomingos));
    str.append("-");
    str.append(QString::number(iNacionales));
    str.append("-");
    str.append(QString::number(iAutonomicos));
    str.append("-");
    str.append(QString::number(iLocales));
    str.append("-");
    str.append(QString::number(1));
    str.append(") x 8 Horas = ");
    str.append(QString::number(iHorasLaborables));
    ui->lblHorasAnuales->setText(str);

    //Vacaciones ( 22 Días x 8 Horas ) = 176 Horas
    str = "Vacaciones (22 Días x 8 Horas) = 176 Horas";
    ui->lblHorasVacaciones->setText(str);

    //1992 Horas  - 176 Horas  = 1816 Horas
    str = QString::number(iHorasLaborables);
    str.append(" Horas - 176 Horas = ");
    str.append(QString::number((iHorasLaborables - iHorasVacaciones)));
    str.append(" Horas");
    ui->lblHorasReales->setText(str);

    //1816 Horas - 1752 Horas  = 64 Horas
    str = QString::number((iHorasLaborables - iHorasVacaciones));
    str.append(" Horas - 1752 Horas = ");
    str.append(QString::number(iHorasExceso));
    str.append(" Horas");
    ui->lblHorasDiferencia->setText(str);

    //(64 Horas / 8 Horas) = 8 Días Exceso Jornada
    str = "( ";
    str.append(QString::number(iHorasExceso));
    str.append(" Horas / 8 Horas) = ");
    str.append(QString::number(iDiasExceso));
    str.append(" Días Exceso Jornada");
    ui->lblDiasExceso->setText(str);

}

void RegistroDiasFestivos::on_btnCancelar_clicked(){

    salir();
}

void RegistroDiasFestivos::salir(){

    this->close();
}

void RegistroDiasFestivos::on_cmbAno_activated(int index){

    mostrarExcesosJornada();
}

