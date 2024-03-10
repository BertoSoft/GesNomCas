#include "registrovacaciones.h"
#include "ui_registrovacaciones.h"

#include "funcaux.h"

#include <QDate>
#include <QLocale>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QColor>

RegistroVacaciones::RegistroVacaciones(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroVacaciones){

    ui->setupUi(this);

    initSps();
    initTable();
    initVacacionesPendientes();
    initUi();
}

RegistroVacaciones::~RegistroVacaciones(){
    delete ui;
}

void RegistroVacaciones::initUi(){

    //
    // Pongo las fechas en Blanco y desactivo controles
    //
    ui->txtFecha0->setText("");
    ui->txtFecha1->setText("");
    ui->frameControles->setEnabled(false);
    ui->btnGuardar->setEnabled(false);
    ui->btnEliminar->setEnabled(false);

    //
    // Mostramos los excesos de jornada y el listado
    //
    mostrarResumenAnual();
    mostrarListado();
}

void RegistroVacaciones::initSps(){
    int     iAno;
    int     iLimite;

    //
    // Colocamos el año actual, uno despues y 10 anteriores, con un tope de 2022
    //
    iAno    = QDate::currentDate().year();
    iLimite = iAno - 10;
    iAno++;
    while (iAno>iLimite) {
        if(iAno > 2021){
            ui->cmbAno->addItem(QString::number(iAno));
        }
        iAno--;
    }
    ui->cmbAno->setCurrentIndex(1);
}

void RegistroVacaciones::initTable(){

    //
    // Colocamos las columnas del tablelist
    //
    ui->tableVacaciones->setColumnCount(3);

    QStringList headers;
    headers += tr("Inicio");
    headers += tr("Final");
    headers += tr("Total Dias");

    ui->tableVacaciones->setHorizontalHeaderLabels(headers);

    ui->tableVacaciones->setColumnWidth(0, (int) ( ( this->width() * 0.53 ) / 3 ) );
    ui->tableVacaciones->setColumnWidth(1, (int) ( ( this->width() * 0.53 ) / 3 ) );
    ui->tableVacaciones->setColumnWidth(2, (int) ( ( this->width() * 0.53 ) / 3 ) );

}

void RegistroVacaciones::initVacacionesPendientes(){
    FuncAux::VacacionesPendientes           dato;
    QList<FuncAux::VacacionesPendientes>    listaVacacionesPendientes;
    int                                     iAno;
    int                                     iAnoSp;
    int                                     iDias;

    //
    // Comprobamos si existen registros de vacaciones pendientes, si no es a si comenzamos la serie en 2021 con 9 dias
    //
    listaVacacionesPendientes = FuncAux().getVacacionesPendientes();

    //
    // Si la lista esta vacia iniciamos con el 2021, y añadimos hasta el año actual
    //
    if(listaVacacionesPendientes.count() == 0){
        iAno    = 2021;
        iAnoSp  = ui->cmbAno->currentText().toInt();
        iDias   = 9;

        while (iAno < iAnoSp) {
            dato.strAno = QString::number(iAno);
            dato.strDias = QString::number(iDias);
            FuncAux().setVacacionesPendientes(dato);
            iAno++;
            iDias+=22;
        }
    }

}

void RegistroVacaciones::mostrarResumenAnual(){

}

void RegistroVacaciones::mostrarListado(){

}

void RegistroVacaciones::on_btnCancelar_clicked(){

    this->close();
}

