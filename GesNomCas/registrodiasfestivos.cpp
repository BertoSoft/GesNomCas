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
    initUi();
}

RegistroDiasFestivos::~RegistroDiasFestivos(){
    delete ui;
}

void RegistroDiasFestivos::initUi(){

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
    ui->cmbAno->setCurrentIndex(1);

    //
    // Colocamos los tipos de festivos
    //
    ui->cmbFestivo->addItem("Nacional");
    ui->cmbFestivo->addItem("Autonómico");
    ui->cmbFestivo->addItem("Local");
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

void RegistroDiasFestivos::mostrarListado(){
    QString         strFechaDb;
    QString         strTipoFestivo;
    QString         strAnoDb;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    QColor          color;
    bool            todoOk;
    int             iFila = 0;

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
    // Leo la tabla Retribuciones
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
            // Añadimos una linea a la tabla
            //
            ui->tableFestivos->setRowCount(iFila + 1);

            QTableWidgetItem *item_fecha = new QTableWidgetItem(strFechaDb);
            QTableWidgetItem *item_tipo_festivo = new QTableWidgetItem(strTipoFestivo);

            item_fecha->setTextAlignment(Qt::AlignCenter);
            item_tipo_festivo->setTextAlignment(Qt::AlignCenter);

            //
            // Segun  tipo festivo distinto color
            //
            if(strTipoFestivo == "Nacional"){color = colorNacional;}
            if(strTipoFestivo == "Autonómico"){color = colorAutonomico;}
            if(strTipoFestivo == "Local"){color = colorLocal;}
            if(strTipoFestivo == "Convenio"){color = colorConvenio;}

            item_fecha->setBackground(color);
            item_tipo_festivo->setBackground(color);

            ui->tableFestivos->setItem(iFila, 0, item_fecha);
            ui->tableFestivos->setItem(iFila, 1, item_tipo_festivo);

            iFila++;
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_rellena_festivos");


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
    QString         strRegOldCod = "-1";
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
            strRegOldCod = strFechaDbCod;
            sql.finish();
        }
        sql.next();
    }

    if(strRegOldCod == "-1"){
        strSql = " INSERT INTO Festivos(Fecha,"
                 "                      TipoFestivo) VALUES ('" + strFechaCod + "',"
                 "                                           '" + strTipoFestivoCod + "');";
    }
    else{
        strSql= "UPDATE Festivos SET Fecha ='"        + strFechaCod +"', "
                                    "TipoFestivo ='"  + strTipoFestivoCod + "'  WHERE  Fecha ='" + strRegOldCod + "';";
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

