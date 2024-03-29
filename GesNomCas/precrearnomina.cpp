#include "precrearnomina.h"
#include "ui_precrearnomina.h"

#include "funcaux.h"

#include <QDate>
#include <QMessageBox>

PreCrearNomina::PreCrearNomina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreCrearNomina){

    ui->setupUi(this);

    initSps();
    initUi();
}

PreCrearNomina::~PreCrearNomina(){
    delete ui;
}

void PreCrearNomina::initSps(){
    QDate   qdFecha;
    int     iAno;
    int     iLimite;

    //
    // Colocamos el año actual, uno despues y 10 anteriores, empezando en 2022
    //
    qdFecha = QDate::currentDate();
    iAno    = qdFecha.year();
    iLimite = iAno - 10;
    iAno++;
    while (iAno>iLimite) {
        if(iAno > 2021){
            ui->cmbAno->addItem(QString::number(iAno));
        }
        iAno--;
    }
    ui->cmbAno->setCurrentIndex(1);

    ui->cmbAno->setStyleSheet("color:rgb(0,0,255)");

    //
    // Colocamos los meses del año
    //
    ui->cmbMes->addItem("Enero");
    ui->cmbMes->addItem("Febrero");
    ui->cmbMes->addItem("Marzo");
    ui->cmbMes->addItem("Abril");
    ui->cmbMes->addItem("Mayo");
    ui->cmbMes->addItem("Junio");
    ui->cmbMes->addItem("Julio");
    ui->cmbMes->addItem("Agosto");
    ui->cmbMes->addItem("Septiembre");
    ui->cmbMes->addItem("Octubre");
    ui->cmbMes->addItem("Noviembre");
    ui->cmbMes->addItem("Diciembre");

    ui->cmbMes->setStyleSheet("color:rgb(0,0,255)");

}

void PreCrearNomina::initUi(){
    QDate       qdFecha;

    //
    // Seleccionamos este mes y este año
    //
    qdFecha = QDate::currentDate();
    ui->cmbMes->setCurrentIndex(qdFecha.month() -1);
    ui->cmbAno->setCurrentText(QString::number(qdFecha.year()));
    refrescaUi();

}

void PreCrearNomina::refrescaUi(){
    QDate                           qdFecha;
    QDate                           qdIngreso;
    QDate                           qdZero;
    int                             iAntiguedad;
    int                             iDias;
    FuncAux::DatosEmpleado          datosEmpleado;
    FuncAux::DatosIncidencias       datosIncidencias;

    strMes = ui->cmbMes->currentText();
    strAno = ui->cmbAno->currentText();

    qdFecha.setDate(strAno.toInt(), FuncAux().strMesToInt(strMes), 01);

    //
    // Días Totales
    //
    ui->etDiasTotales->setText(QString::number(qdFecha.daysInMonth()));

    //
    // Antiguedad
    //
    datosEmpleado   = FuncAux().getDatosEmpleado();
    qdIngreso       = FuncAux().fechaCortaToDate(datosEmpleado.ingreso);
    iDias           = qdIngreso.daysTo(qdFecha);
    qdZero          = QDate(1,1,1);
    qdZero          = qdZero.addDays(iDias + 15);

    qdZero          = qdZero.addDays(-1);
    qdZero          = qdZero.addYears(-1);

    iAntiguedad     = qdZero.year();

    ui->etAntiguedad->setText(QString::number(iAntiguedad));

    //
    //Asistencias
    //
    ui->etAsistencias->setText(QString::number(getAsistencias()));

    //
    // Trasnportes
    //
    ui->etTransporte->setText(QString::number(getTransportes()));

    //
    // Turnucidad
    //
    ui->etTurnicidad->setText("1");

    //
    // Irpf
    //
    ui->etIrpf->setText(QString::number(getIrpf()));

    //
    // Incidencias
    //
    datosIncidencias = getIncidencias();

    ui->etHed->setText(datosIncidencias.hed);
    ui->etHen->setText(datosIncidencias.hen);
    ui->etHef->setText(datosIncidencias.hef);
    ui->etToxicos->setText(datosIncidencias.voladuras);

    //
    // Prorrateo
    //
    ui->etProrrateo->setText(QString::number(getProrrateo()));

}

void PreCrearNomina::on_btnCancelar_clicked(){

    strMes = "-1";
    strAno = "-1";
    this->close();
}

void PreCrearNomina::on_btnGuardar_clicked(){

    if(ui->etDiasTotales->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo Días Totales no puede estar vacío");
        ui->etDiasTotales->setFocus();
    }
    else if(ui->etAntiguedad->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo Antiguedad no puede estar vacío");
        ui->etDiasTotales->setFocus();
    }
    else{
        guardar();
        this->close();
    }
}

void PreCrearNomina::guardar(){

    //
    // Guardamos los Valores
    //
    strDiasTotales  = ui->etDiasTotales->text();
    strAsistencias  = ui->etAsistencias->text();
    strTransportes  = ui->etTransporte->text();
    strTurnicidad   = ui->etTurnicidad->text();
    strHed          = ui->etHed->text();
    strHen          = ui->etHen->text();
    strHef          = ui->etHef->text();
    strToxicos      = ui->etToxicos->text();
    strCteProrrateo = ui->etProrrateo->text();

    strMes          = ui->cmbMes->currentText();
    strAno          = ui->cmbAno->currentText();

}

void PreCrearNomina::on_cmbMes_activated(int index){

    refrescaUi();
}

void PreCrearNomina::on_cmbAno_activated(int index){

    refrescaUi();
}

int PreCrearNomina::getAsistencias(){
    int     iAsistencias = 0;
    QDate   qdFecha;
    QDate   qdFin;

    qdFecha.setDate(ui->cmbAno->currentText().toInt(), FuncAux().strMesToInt(ui->cmbMes->currentText()), 1);

    qdFin = qdFecha;
    qdFin.setDate(qdFin.year(), qdFin.month(), 20);

    qdFecha = qdFecha.addMonths(-1);
    qdFecha.setDate(qdFecha.year(), qdFecha.month(), 21);

    while (qdFecha <= qdFin) {
        if(FuncAux().isLaborable(qdFecha) && !FuncAux().isFestivo(qdFecha)){
            iAsistencias++;
        }
        qdFecha = qdFecha.addDays(1);
    }

    return iAsistencias;
}

int PreCrearNomina::getTransportes(){
    int     iTransportes = 0;
    QDate   qdFecha;
    QDate   qdFin;

    qdFecha.setDate(ui->cmbAno->currentText().toInt(), FuncAux().strMesToInt(ui->cmbMes->currentText()), 1);

    qdFin = qdFecha;
    qdFin.setDate(qdFin.year(), qdFin.month(), 20);

    qdFecha = qdFecha.addMonths(-1);
    qdFecha.setDate(qdFecha.year(), qdFecha.month(), 21);

    while (qdFecha <= qdFin) {
        if(FuncAux().isLaborable(qdFecha) && !FuncAux().isFestivo(qdFecha) && !FuncAux().isVacaciones(qdFecha)){
            iTransportes++;
        }
        qdFecha = qdFecha.addDays(1);
    }

    return iTransportes;
}

double PreCrearNomina::getIrpf(){
    QList<FuncAux::DatosRetribuciones>  listaRetribuciones;
    double                              dIrpf   = 0.0;
    int                                 i       = 0;;

    listaRetribuciones = FuncAux().getAllRetribuciones();
    while (i < listaRetribuciones.count()) {
        if(listaRetribuciones[i].clave == "RETENCION" && listaRetribuciones[i].codigo == "911.00"){
            dIrpf = listaRetribuciones[i].cuantia.toDouble();
            i = listaRetribuciones.count();
        }
        i++;
    }

    return dIrpf;
}

FuncAux::DatosIncidencias PreCrearNomina::getIncidencias(){
    FuncAux::DatosIncidencias           datosIncidencias;
    QList<FuncAux::DatosIncidencias>    listaIncidencias;
    QDate                               qdFecha;
    QDate                               qdFecha0;
    QDate                               qdFecha1;
    int                                 i           = 0;
    double                              dHed        = 0.0;
    double                              dHen        = 0.0;
    double                              dHef        = 0.0;
    double                              dToxicos    = 0.0;

    qdFecha1.setDate(ui->cmbAno->currentText().toInt(), FuncAux().strMesToInt(ui->cmbMes->currentText()), 20);
    qdFecha = qdFecha1;
    qdFecha0 = qdFecha.addMonths(-1);
    qdFecha0.setDate(qdFecha0.year(), qdFecha0.month(), 21);

    listaIncidencias = FuncAux().getAllIncidencias();
    while (i < listaIncidencias.count()) {
        qdFecha = FuncAux().fechaCortaToDate(listaIncidencias[i].fecha);
        if(qdFecha0 <= qdFecha && qdFecha <= qdFecha1){
            dHed        += listaIncidencias[i].hed.toDouble();
            dHen        += listaIncidencias[i].hen.toDouble();
            dHef        += listaIncidencias[i].hef.toDouble();
            dToxicos    += listaIncidencias[i].voladuras.toDouble();
        }
        i++;
    }

    datosIncidencias.fecha      = "";
    datosIncidencias.hed        = QString::number(dHed);
    datosIncidencias.hen        = QString::number(dHen);
    datosIncidencias.hef        = QString::number(dHef);
    datosIncidencias.voladuras  = QString::number(dToxicos);

    return datosIncidencias;
}

double PreCrearNomina::getProrrateo(){
    double                              dProrrateo              = 0.0;
    QList<FuncAux::DatosRetribuciones>  listaRetribuciones;
    int                                 i                       = 0;
    double                              dSalarioBasePE          = 0.0;
    double                              dAntiguedadPE           = 0.0;
    double                              dBolsaVacacionesPE      = 0.0;
    double                              dTotal                  = 0.0;

    listaRetribuciones = FuncAux().getAllRetribuciones();
    while (i < listaRetribuciones.count()) {
        if(listaRetribuciones[i].clave == "SALARIO"){
            if(listaRetribuciones[i].codigo == "503.50" ||
                listaRetribuciones[i].codigo == "507.50" ||
                listaRetribuciones[i].codigo == "512.50"){
                if(dSalarioBasePE == 0){
                    dSalarioBasePE = listaRetribuciones[i].cuantia.toDouble();
                }
            }
        }

        if(listaRetribuciones[i].clave == "SALARIO"){
            if(listaRetribuciones[i].codigo == "503.60" ||
                listaRetribuciones[i].codigo == "507.60" ||
                listaRetribuciones[i].codigo == "512.60"){
                if(dAntiguedadPE == 0){
                    dAntiguedadPE = listaRetribuciones[i].cuantia.toDouble();
                }
            }
        }

        if(listaRetribuciones[i].clave == "SALARIO"){
            if(listaRetribuciones[i].codigo == "503.70" ||
                listaRetribuciones[i].codigo == "507.70" ||
                listaRetribuciones[i].codigo == "512.70"){
                if(dBolsaVacacionesPE == 0){
                    dBolsaVacacionesPE = listaRetribuciones[i].cuantia.toDouble();
                }
            }
        }

        i++;
    }

    //
    // Hallamos el total
    //
    dTotal = (dSalarioBasePE * 90.0) + (dAntiguedadPE * 90.0) + (dBolsaVacacionesPE * 90.0);

    //
    // Ahorra dividimos entre el numero de dias del año
    //
    dProrrateo = (dTotal / QDate::currentDate().daysInYear());

    return dProrrateo;
}

void PreCrearNomina::on_etDiasTotales_returnPressed(){
    ui->etAntiguedad->setFocus();
    ui->etAntiguedad->selectAll();
}

void PreCrearNomina::on_etAntiguedad_returnPressed(){
    ui->etAsistencias->setFocus();
    ui->etAsistencias->selectAll();
}

void PreCrearNomina::on_etAsistencias_returnPressed(){
    ui->etTransporte->setFocus();
    ui->etTransporte->selectAll();
}

void PreCrearNomina::on_etTransporte_returnPressed(){
    ui->etTurnicidad->setFocus();
    ui->etTurnicidad->selectAll();
}

void PreCrearNomina::on_etTurnicidad_returnPressed(){
    ui->etIrpf->setFocus();
    ui->etIrpf->selectAll();
}

void PreCrearNomina::on_etIrpf_returnPressed(){
    ui->etHed->setFocus();
    ui->etHed->selectAll();
}

void PreCrearNomina::on_etHed_returnPressed(){
    ui->etHen->setFocus();
    ui->etHen->selectAll();
}

void PreCrearNomina::on_etHen_returnPressed(){
    ui->etHef->setFocus();
    ui->etHef->selectAll();
}

void PreCrearNomina::on_etHef_returnPressed(){
    ui->etToxicos->setFocus();
    ui->etToxicos->selectAll();
}

void PreCrearNomina::on_etToxicos_returnPressed(){
    ui->etProrrateo->setFocus();
    ui->etProrrateo->selectAll();
}

void PreCrearNomina::on_etProrrateo_returnPressed(){
    on_btnGuardar_clicked();
}

