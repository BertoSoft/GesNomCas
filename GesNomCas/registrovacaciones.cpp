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
    mostrarListado();
    mostrarResumenAnual();

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
    FuncAux::DatosVacacionesPendientes           dato;
    QList<FuncAux::DatosVacacionesPendientes>    listaVacacionesPendientes;
    int                                     iAno;
    int                                     iAnoSp;
    int                                     iDias;
    int                                     iAnoDb;

    //
    // Comprobamos si existen registros de vacaciones pendientes, si no es a si comenzamos la serie en 2021 con 9 dias
    //
    listaVacacionesPendientes = FuncAux().getAllVacacionesPendientes();

    //
    // Si la lista esta vacia iniciamos con el 2021, y añadimos hasta el año actual
    //
    if(listaVacacionesPendientes.count() == 0){
        iAno    = 2021;
        iAnoSp  = ui->cmbAno->currentText().toInt();
        iDias   = 9;

        while (iAno < iAnoSp + 1) {
            dato.strAno = QString::number(iAno);
            dato.strDias = QString::number(iDias);
            FuncAux().setVacacionesPendientes(dato);
            iAno++;
            iDias+=22;
        }
    }
    //
    // Si no esta vacia comprobamnos que todos los años esten cubiertos
    //
    else{
        iAnoDb  = listaVacacionesPendientes[listaVacacionesPendientes.count() -1].strAno.toInt();
        iDias   = listaVacacionesPendientes[listaVacacionesPendientes.count() -1].strDias.toInt();
        iAnoSp  = ui->cmbAno->currentText().toInt() + 1;
        if (iAnoSp > iAnoDb){
            while (iAnoDb < iAnoSp) {
                dato.strAno     = QString::number(iAnoDb + 1);
                dato.strDias    = QString::number(iDias + 22);
                FuncAux().setVacacionesPendientes(dato);
                iAnoDb++;
                iDias+=22;
            }
        }
    }
}

void RegistroVacaciones::refrescaVacacionesPendientes(int iDias){
    QList<FuncAux::DatosVacacionesPendientes>   listaVacacionesPendientes;
    FuncAux::DatosVacacionesPendientes          dato;
    int                                         iVacacionesOld = -1;
    int                                         iVacacionesNew;
    int                                         iAnoSp;
    int                                         i;

    listaVacacionesPendientes = FuncAux().getAllVacacionesPendientes();

    iAnoSp = ui->cmbAno->currentText().toInt();
    i = 0;
    while (i < listaVacacionesPendientes.count()) {
        //
        // Si el año es mayor o igual que iAnoSp, restamos las vacaciones disfrutadas iLaborables
        //
        if(listaVacacionesPendientes[i].strAno.toInt() >= iAnoSp){

            iVacacionesOld  = listaVacacionesPendientes[i].strDias.toInt();
            iVacacionesNew  = iVacacionesOld - iDias;

            dato.strAno     = listaVacacionesPendientes[i].strAno;
            dato.strDias    = QString::number(iVacacionesNew);

            FuncAux().setVacacionesPendientes(dato);
        }
        i++;
    }

}

int RegistroVacaciones::getDiasLaborables(QDate qdFecha0, QDate qdFecha1){
    int         iLaborables = 0;
    QDate       qdFecha;
    QString     strFechaLarga;
    QString     str;

    qdFecha = qdFecha0;
    while (qdFecha <= qdFecha1) {
        strFechaLarga = FuncAux().dateToFechaLarga(qdFecha);
        str = strFechaLarga.remove(4, strFechaLarga.length() -4);
        if(str != "sába"  && str != "domi"){
            if(!FuncAux().isFestivo(qdFecha)){
                iLaborables++;
            }
        }

        qdFecha = qdFecha.addDays(1);
    }

    return iLaborables;
}

void RegistroVacaciones::mostrarResumenAnual(){
    QList<FuncAux::DatosVacacionesPendientes>    listaVacacionesPendientes;
    int                                     iAno;
    int                                     iVacacionesAtrasadas    = 0;
    int                                     iVacacionesDisfrutadas  = 0;
    int                                     iVacacionesPendientes   = 0;
    int                                     i;
    QString                                 str;
    QString                                 strAno;
    QDate                                   qdFecha0;
    QDate                                   qdFecha1;

    //
    // Vacaciones Atrasadas
    //
    strAno = ui->cmbAno->currentText();
    iAno = strAno.toInt();
    iAno--;
    strAno = QString::number(iAno);
    listaVacacionesPendientes = FuncAux().getAllVacacionesPendientes();
    i = 0;
    while (i < listaVacacionesPendientes.count()) {
        if(listaVacacionesPendientes[i].strAno == strAno){
            iVacacionesAtrasadas = listaVacacionesPendientes[i].strDias.toInt();
            i = listaVacacionesPendientes.count();
        }
        i++;
    }
    str = "Vacaciones Años Anteriores ";
    str.append(QString::number(iVacacionesAtrasadas));
    str.append(" Días.");
    ui->lblVacacionesAnteriores->setText(str);

    //
    // Vacaciones Disfrutadas
    //
    i = 0;
    while (i < ui->tableVacaciones->rowCount()) {
        iVacacionesDisfrutadas += ui->tableVacaciones->item(i, 2)->text().toInt();
        i++;
    }
    str = "Vacaciones Disfrutadas ";
    str.append(QString::number(iVacacionesDisfrutadas));
    str.append(" Días.");
    ui->lblVacacionesDisfrutadas->setText(str);

    //
    // Vacaciones Pendientes
    //
    iVacacionesPendientes = (iVacacionesAtrasadas + 22) - iVacacionesDisfrutadas;
    str = " Vacaciones Pendientes ";
    str.append(QString::number(iVacacionesPendientes));
    str.append(" Días.");
    ui->lblVacacionesPendientes->setText(str);

}

void RegistroVacaciones::mostrarListado(){
    QList<FuncAux::DatosVacaciones>     listaVacacionesSinOrdenar;
    QList<FuncAux::DatosVacaciones>     listaVacaciones;
    int                                 iLaborables = 0;
    int                                 i;
    int                                 iFila = 0;

    //
    // Borramos la tabla
    //
    while (ui->tableVacaciones->rowCount() > 0) {
        ui->tableVacaciones->removeRow(0);
    }

    listaVacacionesSinOrdenar   = FuncAux().getAllVacaciones();
    listaVacaciones             = ordenarListaVacaciones(listaVacacionesSinOrdenar);

    i = 0;
    while (i<listaVacaciones.count()) {

        //
        // solo los periodos de este año
        //
        if(listaVacaciones[i].strAno == ui->cmbAno->currentText()){

            //
            // Añadimos una linea a la tabla
            //
            ui->tableVacaciones->setRowCount(iFila + 1);

            //
            // Obtenemos los laborables del periodo
            //
            iLaborables = getDiasLaborables(listaVacaciones[i].qdFecha0, listaVacaciones[i].qdFecha1);

            QTableWidgetItem *item_fecha0       = new QTableWidgetItem(FuncAux().dateToFechaCorta(listaVacaciones[i].qdFecha0));
            QTableWidgetItem *item_fecha1       = new QTableWidgetItem(FuncAux().dateToFechaCorta(listaVacaciones[i].qdFecha1));
            QTableWidgetItem *item_Laborables   = new QTableWidgetItem(QString::number(iLaborables));

            item_fecha0->setTextAlignment(Qt::AlignCenter);
            item_fecha1->setTextAlignment(Qt::AlignCenter);
            item_Laborables->setTextAlignment(Qt::AlignCenter);

            ui->tableVacaciones->setItem(iFila, 0, item_fecha0);
            ui->tableVacaciones->setItem(iFila, 1, item_fecha1);
            ui->tableVacaciones->setItem(iFila, 2, item_Laborables);

            iFila++;
            iLaborables = 0;
        }

        i++;
    }

}

QList<FuncAux::DatosVacaciones> RegistroVacaciones::ordenarListaVacaciones(QList<FuncAux::DatosVacaciones> lista){
    QList<FuncAux::DatosVacaciones>     listaOrdenada;
    QList <QDate>                       listaQDates;
    FuncAux::DatosVacaciones            dato;
    int                                 i = 0;

    //
    // Obtenemos la lista de Fechas
    //
    while (i < lista.count()) {
        listaQDates.append(lista[i].qdFecha0);
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
            if(lista[i].qdFecha0 == listaQDates[0]){
                dato.qdFecha0   = lista[i].qdFecha0;
                dato.qdFecha1   = lista[i].qdFecha1;
                dato.strAno     = lista[i].strAno;

                listaOrdenada.append(dato);

                i = lista.count();
            }
            i++;
        }
        listaQDates.remove(0, 1);
    }

    return listaOrdenada;
}

void RegistroVacaciones::on_btnCancelar_clicked(){

    this->close();
}

void RegistroVacaciones::on_btnGuardar_clicked(){
    QString str;

    if(ui->txtFecha0->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la fecha de inicio no puede estar vacío");
        ui->txtFecha0->setFocus();
    }
    else if(ui->txtFecha1->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la fecha final no puede estar vacío");
        ui->txtFecha1->setFocus();
    }
    else if(!FuncAux().isFormatoFecha(ui->txtFecha0->text())){
        str = "Formato de Fecha no reconocido.\n Formato Correcto\n ";
        str.append(FuncAux().dateToFechaCorta(QDate::currentDate()));
        QMessageBox::information(this, FuncAux().getAppName(), str);
        ui->txtFecha0->setFocus();
        ui->txtFecha0->selectAll();
    }
    else if(!FuncAux().isFormatoFecha(ui->txtFecha1->text())){
        str = "Formato de Fecha no reconocido.\n Formato Correcto\n ";
        str.append(FuncAux().dateToFechaCorta(QDate::currentDate()));
        QMessageBox::information(this, FuncAux().getAppName(), str);
        ui->txtFecha1->setFocus();
        ui->txtFecha1->selectAll();
    }
    else if(FuncAux().fechaCortaToDate(ui->txtFecha0->text()) > FuncAux().fechaCortaToDate(ui->txtFecha1->text())){
        QMessageBox::information(this, FuncAux().getAppName(), "La fecha final, no puede ser anterior a la inicial...");
        ui->txtFecha0->setFocus();
        ui->txtFecha0->selectAll();
    }
    else if(FuncAux().fechaCortaToDate(ui->txtFecha0->text()).year() < ui->cmbAno->currentText().toInt()){
        QMessageBox::information(this, FuncAux().getAppName(), "La fecha inicial, no puede ser del año anterior...");
        ui->txtFecha0->setFocus();
        ui->txtFecha0->selectAll();
    }
    else if(FuncAux().fechaCortaToDate(ui->txtFecha1->text()).year() > ui->cmbAno->currentText().toInt()){
        QMessageBox::information(this, FuncAux().getAppName(), "La fecha final, no puede ser del año posterior...");
        ui->txtFecha1->setFocus();
        ui->txtFecha1->selectAll();
    }
    else{
        guardar();
        initUi();
    }
}

void RegistroVacaciones::on_btnAdd_clicked(){
    QDate qdFecha = QDate::currentDate();

    ui->tableVacaciones->clearSelection();
    ui->frameControles->setEnabled(true);
    ui->btnGuardar->setEnabled(true);
    ui->txtFecha0->setText(FuncAux().dateToFechaCorta(qdFecha));
    ui->txtFecha1->setText(FuncAux().dateToFechaCorta(qdFecha));
    ui->txtFecha0->setFocus();
    ui->txtFecha0->selectAll();
}

void RegistroVacaciones::on_btnEliminar_clicked(){
    QString         strFecha0Db;
    QString         strFecha1Db;
    QString         strFecha0DbCod;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;
    QDate           qdFecha0;
    QDate           qdFecha1;
    int             iDias;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_del_vacaciones");

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
    strSql = "SELECT *FROM Vacaciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFecha0Db = FuncAux().desCifrar(sql.record().value("FechaInicio").toString());
        strFecha1Db = FuncAux().desCifrar(sql.record().value("FechaFin").toString());
        if(strFecha0Db == ui->txtFecha0->text() && strFecha1Db == ui->txtFecha1->text()){
            strFecha0DbCod = sql.record().value("FechaInicio").toString();
            strSql = "DELETE FROM Vacaciones WHERE FechaInicio='" + strFecha0DbCod + "';";
            sql.exec(strSql);
            sql.last();
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_del_vacaciones");

    //
    // Aumentamos los dias de vacaciones pendientes
    //
    qdFecha0    = FuncAux().fechaCortaToDate(ui->txtFecha0->text());
    qdFecha1    = FuncAux().fechaCortaToDate(ui->txtFecha1->text());
    iDias       = getDiasLaborables(qdFecha0, qdFecha1);

    refrescaVacacionesPendientes(-1 * iDias);

    //
    // Reiniciamos
    //
    initUi();
}

void RegistroVacaciones::on_txtFecha0_returnPressed(){
    ui->txtFecha1->setFocus();
    ui->txtFecha1->selectAll();
}

void RegistroVacaciones::on_txtFecha1_returnPressed(){
    on_btnGuardar_clicked();
}

void RegistroVacaciones::on_txtFecha0_textChanged(const QString &arg1){
    QString str = arg1;

    //
    // Si len == 2 , aumento /
    //
    if(str.length() == 2 ){
        str.append("/");
        ui->txtFecha0->setText(str);
    }

    //
    // Si len == 5 , aumento /
    //
    if(str.length() == 5 ){
        str.append("/");
        ui->txtFecha0->setText(str);
    }

    //
    // Si len == 2 , aumento /
    //
    if(str.length() > 10 ){
        str.remove(str.length() -1, 1);
        ui->txtFecha0->setText(str);
    }
}

void RegistroVacaciones::on_txtFecha1_textChanged(const QString &arg1){
    QString str = arg1;

    //
    // Si len == 2 , aumento /
    //
    if(str.length() == 2 ){
        str.append("/");
        ui->txtFecha1->setText(str);
    }

    //
    // Si len == 5 , aumento /
    //
    if(str.length() == 5 ){
        str.append("/");
        ui->txtFecha1->setText(str);
    }

    //
    // Si len == 2 , aumento /
    //
    if(str.length() > 10 ){
        str.remove(str.length() -1, 1);
        ui->txtFecha1->setText(str);
    }
}

void RegistroVacaciones::guardar(){
    QString         strFecha0OldCod = "-1";
    QString         strFecha1OldCod = "-1";
    QString         strAnoOldCod    = "-1";
    QString         strFecha0Cod;
    QString         strFecha1Cod;
    QString         strAnoCod;
    QString         strFecha0Db;
    QString         strFecha1Db;
    QString         strAnoDb;
    QDate           qdFecha0;
    QDate           qdFecha1;
    QDate           qdFecha0Db;
    QDate           qdFecha1Db;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Codifico los valores
    //
    strFecha0Cod        = FuncAux().cifrar(ui->txtFecha0->text());
    strFecha0Cod        = FuncAux().cifrar(ui->txtFecha1->text());
    strAnoCod           = FuncAux().cifrar(ui->cmbAno->currentText());

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_vacaciones");

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
    // Establecemos qdFecha0 y qdFecha1
    //
    qdFecha0 = FuncAux().fechaCortaToDate(ui->txtFecha0->text());
    qdFecha1 = FuncAux().fechaCortaToDate(ui->txtFecha1->text());

    strSql = "SELECT *FROM Vacaciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {

        //
        // Obtenemos el año
        //
        strAnoDb = FuncAux().desCifrar(sql.record().value("Ano").toString());

        if(strAnoDb == ui->cmbAno->currentText()){
            strFecha0Db = FuncAux().desCifrar(sql.record().value("FechaInicio").toString());
            strFecha1Db = FuncAux().desCifrar(sql.record().value("FechaFin").toString());

            qdFecha0Db = FuncAux().fechaCortaToDate(strFecha0Db);
            qdFecha1Db = FuncAux().fechaCortaToDate(strFecha1Db);

            //
            // Primer caso, fecha0 < fecha0Db y fecha1 > fecha1Db -> editamos registro
            //
            if( qdFecha0 < qdFecha0Db && qdFecha1 > qdFecha1Db){
                strFecha0OldCod = sql.record().value("FechaInicio").toString();
                strFecha1OldCod = sql.record().value("FechaFin").toString();
                strAnoOldCod    = sql.record().value("Ano").toString();
            }

            //
            // fecha0 < fecha0Db pero fecha1 > fecha0Db y ademas fecha1 < fecha1Db -> fecha1 = fecha1Db y editamos
            //
            if(qdFecha0 < qdFecha0Db && qdFecha1 > qdFecha0Db && qdFecha1 <= qdFecha1Db){
                qdFecha1 = qdFecha1Db;
                strFecha0OldCod = sql.record().value("FechaInicio").toString();
                strFecha1OldCod = sql.record().value("FechaFin").toString();
                strAnoOldCod    = sql.record().value("Ano").toString();
            }

            //
            // fecha0 > fecha0Db && fecha1 < fecha1Db -> No hacemos nada
            //
            if(qdFecha0 > qdFecha0Db && qdFecha1 < qdFecha1Db){
                qdFecha0 = qdFecha0Db;
                qdFecha1 = qdFecha1Db;
                strFecha0OldCod = sql.record().value("FechaInicio").toString();
                strFecha1OldCod = sql.record().value("FechaFin").toString();
                strAnoOldCod    = sql.record().value("Ano").toString();
            }

            //
            // fecha0 > fecha0Db && fecha0 < fecha1Db && fecha1 > fecha1Db -> fecha0 = fecha0Db
            //
            if(qdFecha0 > qdFecha0Db && qdFecha0 < qdFecha1Db && qdFecha1 >= qdFecha1Db){
                qdFecha0 = qdFecha0Db;
                strFecha0OldCod = sql.record().value("FechaInicio").toString();
                strFecha1OldCod = sql.record().value("FechaFin").toString();
                strAnoOldCod    = sql.record().value("Ano").toString();
            }

        }
        sql.next();
    }

    //
    // Codificamos los valores
    //
    strFecha0Cod    = FuncAux().cifrar(FuncAux().dateToFechaCorta(qdFecha0));
    strFecha1Cod    = FuncAux().cifrar(FuncAux().dateToFechaCorta(qdFecha1));
    strAnoCod       = FuncAux().cifrar(ui->cmbAno->currentText());

    //
    // Guardamos
    //
    if(strFecha0OldCod == "-1"){
        strSql = " INSERT INTO Vacaciones(FechaInicio,"
                 "                        FechaFin,"
                 "                        Ano) VALUES ('" + strFecha0Cod + "',"
                                  "                                     '" + strFecha1Cod + "',"
                                  "                                     '" + strAnoCod + "');";
    }
    else{
        strSql= "UPDATE Vacaciones SET FechaInicio ='"+ strFecha0Cod +"', "
                                      "FechaFin ='"   + strFecha1Cod +"', "
                                      "Ano ='"        + strAnoCod + "'  WHERE  FechaInicio ='" + strFecha0OldCod + "';";
    }


    //
    // Ahora ejecutamos la instruccion
    //
    sql.exec(strSql);

    //
    // Actualizamos Vacaciones Pendientes
    //
    refrescaVacacionesPendientes(getDiasLaborables(qdFecha0, qdFecha1));

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_vacaciones");

}

void RegistroVacaciones::on_tableVacaciones_itemClicked(QTableWidgetItem *item){

    //
    // Desactivo los controles
    //
    ui->frameControles->setEnabled(false);
    ui->btnGuardar->setEnabled(false);

    //
    // Coloco los valores en los txt
    //
    ui->txtFecha0->setText(ui->tableVacaciones->item(item->row(), 0)->text());
    ui->txtFecha1->setText(ui->tableVacaciones->item(item->row(), 1)->text());

    //
    // Activamos el boton de suprimir
    //
    ui->btnEliminar->setEnabled(true);
}

void RegistroVacaciones::on_tableVacaciones_itemDoubleClicked(QTableWidgetItem *item){

    //
    // Activo los controles
    //
    ui->frameControles->setEnabled(true);

    //
    // Activo el boton Guardar y desactivo el boton  -
    //
    ui->btnGuardar->setEnabled(true);
    ui->btnEliminar->setEnabled(false);

    //
    // situo el foco en txtCodigo
    //
    ui->txtFecha0->setFocus();
    ui->txtFecha0->selectAll();
}

void RegistroVacaciones::on_cmbAno_activated(int index){

    initUi();
}

