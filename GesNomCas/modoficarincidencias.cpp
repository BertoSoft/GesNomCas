#include "modoficarincidencias.h"
#include "ui_modoficarincidencias.h"

#include "funcaux.h"
#include "calendario.h"

#include <QDate>
#include <QListWidgetItem>

ModoficarIncidencias::ModoficarIncidencias(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModoficarIncidencias){

    ui->setupUi(this);

    initSp();
    initUi();
}

ModoficarIncidencias::~ModoficarIncidencias(){
    delete ui;
}

void ModoficarIncidencias::initSp(){
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

    //
    // Color Azul
    //
    ui->cmbMes->setStyleSheet("color:rgb(0,0,255)");

    //
    // Seleccionamos el mes actual
    //
    ui->cmbMes->setCurrentIndex(qdFecha.month() -1);

}

void ModoficarIncidencias::initUi(){

    //
    // Desactivamos los controles
    //
    ui->frameEts->setEnabled(false);
    ui->frameFecha->setEnabled(false);
    ui->btnModificar->setEnabled(false);
    ui->tbEliminar->setEnabled(false);

    //
    // Controles de azul
    //
    ui->etFecha->setStyleSheet("color:rgb(0,0,255)");
    ui->etHed->setStyleSheet("color:rgb(0,0,255)");
    ui->etHen->setStyleSheet("color:rgb(0,0,255)");
    ui->etHef->setStyleSheet("color:rgb(0,0,255)");
    ui->etToxicos->setStyleSheet("color:rgb(0,0,255)");
    ui->listIncidencias->setStyleSheet("color:rgb(0,0,255)");

    //
    //Mostramos el listado
    //
    refrescarListado();

}

void ModoficarIncidencias::limpiarEts(){

    ui->etFecha->setText("");
    ui->etHed->setText("");
    ui->etHen->setText("");
    ui->etHef->setText("");
    ui->etToxicos->setText("");

}

void ModoficarIncidencias::refrescarListado(){
    QList<FuncAux::DatosIncidencias>    listaIncidencias;
    QList<FuncAux::DatosIncidencias>    listaIncidenciasPeriodo;
    QList<FuncAux::DatosIncidencias>    listaPeriodoOrdenada;
    FuncAux::DatosIncidencias           dato;
    QDate                               qdFecha;
    QDate                               qdFecha0;
    QDate                               qdFecha1;
    QString                             strFechaLarga;
    int                                 i;

    //
    // Obtenemos todas las incidencias
    //
    listaIncidencias = FuncAux().getAllIncidencias();

    //
    // Obtenemos la lista del periodo
    //
    qdFecha0.setDate(ui->cmbAno->currentText().toInt(), FuncAux().strMesToInt(ui->cmbMes->currentText()), 1);
    qdFecha1.setDate(qdFecha0.year(), qdFecha0.month(), qdFecha0.daysInMonth());
    i = 0;
    while (i < listaIncidencias.count()) {
        qdFecha = FuncAux().fechaCortaToDate(listaIncidencias[i].fecha);
        if(qdFecha0 <= qdFecha && qdFecha <= qdFecha1){

            dato.fecha      = listaIncidencias[i].fecha;
            dato.hed        = listaIncidencias[i].hed;
            dato.hen        = listaIncidencias[i].hen;
            dato.hef        = listaIncidencias[i].hef;
            dato.voladuras  = listaIncidencias[i].voladuras;

            listaIncidenciasPeriodo.append(dato);

        }
        i++;
    }

    //
    // Ordenamos la lista
    //
    listaPeriodoOrdenada = ordenarLista(listaIncidenciasPeriodo);

    //
    // Borramos la list y dibujamos la nueva
    //
    while (ui->listIncidencias->count() > 0) {
        ui->listIncidencias->takeItem(0);
    }

    i = 0;
    while (i < listaPeriodoOrdenada.count()) {
        qdFecha         = FuncAux().fechaCortaToDate(listaPeriodoOrdenada[i].fecha);
        strFechaLarga   = FuncAux().dateToFechaLarga(qdFecha);
        strFechaLarga.append(" ");
        ui->listIncidencias->addItem(strFechaLarga);
        ui->listIncidencias->item(ui->listIncidencias->count() - 1)->setTextAlignment(Qt::AlignRight);
        i++;
    }

}

QList<FuncAux::DatosIncidencias> ModoficarIncidencias::ordenarLista(QList<FuncAux::DatosIncidencias> lista){
    QList<FuncAux::DatosIncidencias>    listaOrdenada;
    QList <QDate>                       listaQDates;
    FuncAux::DatosIncidencias           dato;
    int                                 i = 0;

    // Obtenemos la lista de Fechas
    //
    while (i < lista.count()) {
        listaQDates.append(FuncAux().fechaCortaToDate(lista[i].fecha));
        i++;
    }

    //
    // Ordenamos las fechas
    //
    std::sort(listaQDates.begin(), listaQDates.end());

    //
    // Ordenamos la lista
    //
    while (listaQDates.count() > 0) {
        i = 0;
        while (i < lista.count()) {
            if(FuncAux().fechaCortaToDate(lista[i].fecha) == listaQDates[0]){

                dato.fecha      = lista[i].fecha;
                dato.hed        = lista[i].hed;
                dato.hen        = lista[i].hen;
                dato.hef        = lista[i].hef;
                dato.voladuras  = lista[i].voladuras;

                listaOrdenada.append(dato);
            }
            i++;
        }
        listaQDates.remove(0, 1);
    }

    return listaOrdenada;

}

void ModoficarIncidencias::on_btnModificar_clicked(){
    FuncAux::DatosIncidencias   dato;

    //
    // Guardamos los valores
    //

    dato.fecha      = ui->etFecha->text();
    dato.hed        = ui->etHed->text();
    dato.hen        = ui->etHen->text();
    dato.hef        = ui->etHef->text();
    dato.voladuras  = ui->etToxicos->text();

    FuncAux().setIncidencia(dato);

    //
    // Limpiamos los controles
    //
    limpiarEts();

    //
    // Desactivamos el boton modificar, y los frames
    //
    ui->btnModificar->setEnabled(false);
    ui->frameEts->setEnabled(false);
    ui->frameFecha->setEnabled(false);

    //
    // Refrescamos el listado
    //
    refrescarListado();

}

void ModoficarIncidencias::on_btnVolver_clicked(){

    this->close();
}

void ModoficarIncidencias::on_cmbMes_activated(int index){

    refrescarListado();
}

void ModoficarIncidencias::on_cmbAno_activated(int index){

    refrescarListado();
}

void ModoficarIncidencias::on_listIncidencias_itemClicked(QListWidgetItem *item){
    QList<FuncAux::DatosIncidencias>    listaIncidencias;
    QDate                               qdFecha;
    QString                             strFechaLarga;
    int                                 i   = 0;

    //
    // Activamos el tbEliminar
    //
    ui->tbEliminar->setEnabled(true);

    //
    // Obtenemos la fecha seleccionada
    //
    strFechaLarga = item->text();
    strFechaLarga = strFechaLarga.remove(strFechaLarga.length() -1, 1);
    qdFecha = FuncAux().fechaLargaToDate(strFechaLarga);

    //
    // Obtenemos la lista de incidencias
    //
    listaIncidencias = FuncAux().getAllIncidencias();

    //
    // Buscamos la fecha en la lista, y rellenamos los ets
    //
    i = 0;
    while (i < listaIncidencias.count()) {
        if(listaIncidencias[i].fecha == FuncAux().dateToFechaCorta(qdFecha)){

            ui->etFecha->setText(listaIncidencias[i].fecha);
            ui->etHed->setText(listaIncidencias[i].hed);
            ui->etHen->setText(listaIncidencias[i].hen);
            ui->etHef->setText(listaIncidencias[i].hef);
            ui->etToxicos->setText(listaIncidencias[i].voladuras);

            i = listaIncidencias.count();
        }
        i++;
    }

}

void ModoficarIncidencias::on_listIncidencias_itemDoubleClicked(QListWidgetItem *item){

    //
    // Activo los controles
    //
    ui->frameEts->setEnabled(true);
    ui->frameFecha->setEnabled(true);

    //
    // Activo el btnModificar
    //
    ui->btnModificar->setEnabled(true);

    //
    // Desactivo el tbEliminar
    //
    ui->tbEliminar->setEnabled(false);

    //
    // Pongo el foco en hed
    //
    ui->etHed->setFocus();
    ui->etHed->selectAll();

}

void ModoficarIncidencias::on_tbAdd_clicked(){

    //
    // Activamos los ets, y el btnModificar
    //
    ui->frameEts->setEnabled(true);
    ui->frameFecha->setEnabled(true);
    ui->btnModificar->setEnabled(true);

    //
    // Desactivamos el tbEliminar
    //
    ui->tbEliminar->setEnabled(false);

    //
    // Borramos cualquuier seleccion, y limpiamos los controles
    //
    ui->listIncidencias->clearSelection();
    limpiarEts();

    //
    // Colocamos la fecha actual
    //
    ui->etFecha->setText(FuncAux().dateToFechaCorta(QDate::currentDate()));

    //
    // Ponemos el foco en etHed
    //
    ui->etHed->setFocus();
    ui->etHed->selectAll();
}

void ModoficarIncidencias::on_tbEliminar_clicked(){

    //
    // Eliminamos la incidencia
    //
    FuncAux().delIncidencia(FuncAux().fechaCortaToDate(ui->etFecha->text()));

    //
    // Borramos oo ets
    //
    limpiarEts();

    //
    // Refrescamnos la lista
    //
    refrescarListado();

    //
    // Desactivamos el tb Eliminar
    //
    ui->tbEliminar->setEnabled(false);

}

void ModoficarIncidencias::on_etHed_returnPressed(){

    ui->etHen->setFocus();
    ui->etHen->selectAll();
}

void ModoficarIncidencias::on_etHen_returnPressed(){

    ui->etHef->setFocus();
    ui->etHef->selectAll();
}

void ModoficarIncidencias::on_etHef_returnPressed(){

    ui->etToxicos->setFocus();
    ui->etToxicos->selectAll();
}

void ModoficarIncidencias::on_etToxicos_returnPressed(){

    ui->etFecha->setFocus();
    ui->etFecha->selectAll();
}

void ModoficarIncidencias::on_etFecha_returnPressed(){

    on_btnModificar_clicked();
}

void ModoficarIncidencias::on_tbFecha_clicked(){

    Calendario *pCalendario = new Calendario();

    pCalendario->setWindowModality(Qt::ApplicationModal);
    pCalendario->setWindowFlag(Qt::FramelessWindowHint);
    pCalendario->exec();

    if(pCalendario->strFecha != ""){
        ui->etFecha->setText(pCalendario->strFecha);
    }

    delete pCalendario;

    ui->etFecha->setFocus();
    ui->etFecha->selectAll();
}

