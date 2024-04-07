#include "registrodiasfestivos.h"
#include "ui_registrodiasfestivos.h"

#include "funcaux.h"
#include "calendario.h"

#include <QDate>
#include <QLocale>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QColor>


RegistroDiasFestivos::RegistroDiasFestivos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroDiasFestivos){

    ui->setupUi(this);

    initSp();
    initTable();
    initUi();
}

RegistroDiasFestivos::~RegistroDiasFestivos(){
    delete ui;
}

void RegistroDiasFestivos::initUi(){

    //
    // Pongo la fecha en Blanco y desactivo controles
    //
    ui->txtFecha->setText("");
    ui->frameFestivos->setEnabled(false);
    ui->btnGuardar->setEnabled(false);
    ui->btnEliminar->setEnabled(false);

    //
    // Mostramos los excesos de jornada y el listado
    //
    mostrarExcesosJornada();
    mostrarListado();
}

void RegistroDiasFestivos::initTable(){

    //
    // Colocamos las columnas del tablelist
    //
    ui->tableFestivos->setColumnCount(2);

    QStringList headers;
    headers += tr("Fecha");
    headers += tr("Tipo Festivo");

    ui->tableFestivos->setHorizontalHeaderLabels(headers);

    ui->tableFestivos->setColumnWidth(0, (int) ( ( this->width() * 0.4 ) / 2 ) );
    ui->tableFestivos->setColumnWidth(1, (int) ( ( this->width() * 0.4 ) / 2 ) );
}

void RegistroDiasFestivos::initSp(){
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

    //
    // Colocamos los tipos de festivos
    //
    ui->cmbFestivo->addItem("Nacional");
    ui->cmbFestivo->addItem("Autonómico");
    ui->cmbFestivo->addItem("Local");
    ui->cmbFestivo->addItem("Convenio");
    ui->cmbFestivo->addItem("Exceso Jornada");

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
    int     iConvenio;
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
    iConvenio           = FuncAux().getFestivosConvenio(ui->cmbAno->currentText()).toInt();
    iLaborables         = iDiasAno - iSabados - iDomingos - iNacionales - iAutonomicos - iLocales - 1;
    iHorasLaborables    = iLaborables * 8;
    iHorasExceso        = iHorasLaborables - iHorasVacaciones - 1752;
    iDiasExceso         = iHorasExceso / 8;

    ui->lblSabados->setText(QString::number(iSabados));
    ui->lblDomingos->setText(QString::number(iDomingos));
    ui->lblNacionales->setText(QString::number(iNacionales));
    ui->lblAutonomicos->setText(QString::number(iAutonomicos));
    ui->lblLocales->setText(QString::number(iLocales));
    ui->lblConvenio->setText(QString::number(iConvenio));

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

void RegistroDiasFestivos::mostrarListado(){
    QString                 strFechaDb;
    QString                 strTipoFestivo;
    QString                 strAnoDb;
    QString                 strSql;
    QSqlDatabase            dbSql;
    QSqlQuery               sql;
    QColor                  color;
    bool                    todoOk;
    int                     iFila = 0;
    QList<FuncAux::DatosFestivos>    lista;
    QList<FuncAux::DatosFestivos>    listaOrdenada;
    FuncAux::DatosFestivos           dato;

    //
    // Si no esta vacio lo vaciamos
    //
    while(ui->tableFestivos->rowCount()>0){
        ui->tableFestivos->removeRow(0);
    }

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_rellena_festivos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(FuncAux().getRutaDb());

    //
    // Si se abre y no da error, creamos la SqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Leo la tabla Festivos
    //
    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDb  = FuncAux().desCifrar(sql.record().value("Fecha").toString());
        strAnoDb    = strFechaDb;
        strAnoDb    = strAnoDb.remove(0, strAnoDb.length() - 4);
        if(strAnoDb == ui->cmbAno->currentText()){
            strTipoFestivo = FuncAux().desCifrar(sql.record().value("TipoFestivo").toString());

            //
            // Añadimos un elemento a la lista
            //
            dato.qdFecha           = FuncAux().fechaCortaToDate(strFechaDb);
            dato.strTipoFestivo    = strTipoFestivo;
            lista.append(dato);
        }
        sql.next();
    }

    //
    // Ordenamos la lista
    //
    listaOrdenada = ordenarLista(lista);

    //
    // Rellenamos la tabla
    //
    while (listaOrdenada.count() > 0) {

        //
        // Añadimos una linea a la tabla
        //
        ui->tableFestivos->setRowCount(iFila + 1);

        QTableWidgetItem *item_fecha = new QTableWidgetItem(FuncAux().dateToFechaCorta(listaOrdenada[0].qdFecha));
        QTableWidgetItem *item_tipo_festivo = new QTableWidgetItem(listaOrdenada[0].strTipoFestivo);

        item_fecha->setTextAlignment(Qt::AlignCenter);
        item_tipo_festivo->setTextAlignment(Qt::AlignCenter);

        //
        // Segun  tipo festivo distinto color
        //
        if(listaOrdenada[0].strTipoFestivo == "Nacional"){color = colorNacional;}
        if(listaOrdenada[0].strTipoFestivo == "Autonómico"){color = colorAutonomico;}
        if(listaOrdenada[0].strTipoFestivo == "Local"){color = colorLocal;}
        if(listaOrdenada[0].strTipoFestivo == "Convenio"){color = colorConvenio;}
        if(listaOrdenada[0].strTipoFestivo == "Exceso Jornada"){color = colorExcesoJornada;}

        item_fecha->setBackground(color);
        item_tipo_festivo->setBackground(color);

        ui->tableFestivos->setItem(iFila, 0, item_fecha);
        ui->tableFestivos->setItem(iFila, 1, item_tipo_festivo);

        iFila++;
        listaOrdenada.remove(0, 1);
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_rellena_festivos");

}

QList<FuncAux::DatosFestivos> RegistroDiasFestivos::ordenarLista(QList<FuncAux::DatosFestivos> lista){
    QList<FuncAux::DatosFestivos>    listaOrdenada;
    QList <QDate>                    listaQDates;
    int                              i = 0;
    FuncAux::DatosFestivos           dato;
    //

    // Obtenemos la lista de Fechas
    //
    while (i < lista.count()) {
        listaQDates.append(lista[i].qdFecha);
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
            if(lista[i].qdFecha == listaQDates[0]){
                dato.qdFecha        = lista[i].qdFecha;
                dato.strTipoFestivo = lista[i].strTipoFestivo;
                listaOrdenada.append(dato);
            }
            i++;
        }
        listaQDates.remove(0, 1);
    }

    return listaOrdenada;
}

void RegistroDiasFestivos::on_btnCancelar_clicked(){

    salir();
}

void RegistroDiasFestivos::on_cmbAno_activated(int index){

    mostrarExcesosJornada();
    mostrarListado();
}

void RegistroDiasFestivos::on_btnAdd_clicked(){
    QDate qdFecha = QDate::currentDate();

    ui->tableFestivos->clearSelection();
    ui->frameFestivos->setEnabled(true);
    ui->btnGuardar->setEnabled(true);
    ui->txtFecha->setText(FuncAux().dateToFechaCorta(qdFecha));
    ui->txtFecha->setFocus();
    ui->txtFecha->selectAll();
}

void RegistroDiasFestivos::on_btnGuardar_clicked(){
    QString str;

    if(ui->txtFecha->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la fecha no puede estar vacío");
        ui->txtFecha->setFocus();
    }
    else if(!FuncAux().isFormatoFecha(ui->txtFecha->text())){
        str = "Formato de Fecha no reconocido.\n Formato Correcto\n ";
        str.append(FuncAux().dateToFechaCorta(QDate::currentDate()));
        QMessageBox::information(this, FuncAux().getAppName(), str);
        ui->txtFecha->setFocus();
        ui->txtFecha->selectAll();
    }
    else {
        guardar();
        initUi();
    }

}

void RegistroDiasFestivos::on_txtFecha_returnPressed(){

    on_btnGuardar_clicked();
}

void RegistroDiasFestivos::salir(){

    this->close();
}

void RegistroDiasFestivos::guardar(){
    QString         strFechaCod;
    QString         strTipoFestivoCod;
    QString         strFechaDbCod;
    QString         strFechaOldCod = "-1";
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Codifico los valores
    //
    strFechaCod         = FuncAux().cifrar(ui->txtFecha->text());
    strTipoFestivoCod   = FuncAux().cifrar(ui->cmbFestivo->currentText());

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_dias_festivos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(FuncAux().getRutaDb());

    //
    // Si se abre y no da error, creamos la SqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Comprobamos si existe ese Fecha, si es asi asignamos el strFechaDbCod
    //
    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDbCod = sql.record().value("Fecha").toString();
        if(ui->txtFecha->text() == FuncAux().desCifrar(strFechaDbCod)){
            strFechaOldCod = sql.record().value("Fecha").toString();
            sql.finish();
        }
        sql.next();
    }

    if(strFechaOldCod == "-1"){
        strSql = " INSERT INTO Festivos(Fecha,"
                 "                      TipoFestivo) VALUES ('" + strFechaCod + "',"
                 "                                           '" + strTipoFestivoCod + "');";
    }
    else{
        strSql= "UPDATE Festivos SET Fecha ='"        + strFechaCod +"', "
                                    "TipoFestivo ='"  + strTipoFestivoCod + "'  WHERE  Fecha ='" + strFechaOldCod + "';";
    }


    //
    // Ahora ejecutamos la instruccion
    //
    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_dias_festivos");

}

void RegistroDiasFestivos::on_txtFecha_textChanged(const QString &arg1){
    QString str = arg1;

    //
    // Si len == 2 , aumento /
    //
    if(str.length() == 2 ){
        str.append("/");
        ui->txtFecha->setText(str);
    }

    //
    // Si len == 5 , aumento /
    //
    if(str.length() == 5 ){
        str.append("/");
        ui->txtFecha->setText(str);
    }

    //
    // Si len == 2 , aumento /
    //
    if(str.length() > 10 ){
        str.remove(str.length() -1, 1);
        ui->txtFecha->setText(str);
    }

}

void RegistroDiasFestivos::on_cmbFestivo_activated(int index){

    ui->txtFecha->setFocus();
    ui->txtFecha->selectAll();
}

void RegistroDiasFestivos::on_toolButton_clicked(){

    Calendario *pCalendario = new Calendario();

    pCalendario->setWindowModality(Qt::ApplicationModal);
    pCalendario->setWindowFlag(Qt::FramelessWindowHint);
    pCalendario->exec();

    if(pCalendario->strFecha != ""){
        ui->txtFecha->setText(pCalendario->strFecha);
    }

    delete pCalendario;

    ui->txtFecha->setFocus();
    ui->txtFecha->selectAll();
}

void RegistroDiasFestivos::on_btnEliminar_clicked(){
    QString         strFechaDbCod;
    QString         strFechaDb;
    QString         strFechaEliminar = "";
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_eliminar_festivos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(FuncAux().getRutaDb());

    //
    // Si se abre y no da error, creamos la SqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Busco en la tabla Festivos el registro a eliminar
    //
    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDbCod   = sql.record().value("Fecha").toString();
        strFechaDb      = FuncAux().desCifrar(strFechaDbCod);
        if(strFechaDb == ui->txtFecha->text()){
            strFechaEliminar = strFechaDbCod;
            sql.last();
        }
        sql.next();
    }

    if(strFechaEliminar != ""){
        strSql = "DELETE FROM Festivos WHERE Fecha='" + strFechaEliminar + "';";
        sql.exec(strSql);
    }


    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_eliminar_festivos");

    //
    // Reiniciamos
    //
    ui->cmbFestivo->setCurrentIndex(0);
    initUi();
}

void RegistroDiasFestivos::on_tableFestivos_itemClicked(QTableWidgetItem *item){
    QString         strFechaDb;
    QString         strFechaSeleccionada;
    QString         strTipoFestivo;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Desactivo los controles
    //
    ui->frameFestivos->setEnabled(false);
    ui->btnGuardar->setEnabled(false);

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_item_click_festivos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(FuncAux().getRutaDb());

    //
    // Si se abre y no da error, creamos la SqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    strSql ="SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDb              = FuncAux().desCifrar(sql.record().value("Fecha").toString());
        strFechaSeleccionada    = ui->tableFestivos->item(item->row(), 0)->text();
        if(strFechaDb == strFechaSeleccionada){
            strTipoFestivo = FuncAux().desCifrar(sql.record().value("TipoFestivo").toString());
            ui->txtFecha->setText(strFechaSeleccionada);
            ui->cmbFestivo->setCurrentText(strTipoFestivo);
        }
        sql.next();
    }


    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_item_click_festivos");

    //
    // Activamos el boton de suprimir
    //
    ui->btnEliminar->setEnabled(true);
}

void RegistroDiasFestivos::on_tableFestivos_itemDoubleClicked(QTableWidgetItem *item){

    // Activo los controles
    //
    ui->frameFestivos->setEnabled(true);

    //
    // Activo el boton Guardar y desactivo el boton  -
    //
    ui->btnGuardar->setEnabled(true);
    ui->btnEliminar->setEnabled(false);

    //
    // situo el foco en txtCodigo
    //
    ui->txtFecha->setFocus();
    ui->txtFecha->selectAll();
}

