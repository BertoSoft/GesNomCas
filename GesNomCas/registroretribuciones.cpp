#include "registroretribuciones.h"
#include "ui_registroretribuciones.h"

#include "funcaux.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

RegistroRetribuciones::RegistroRetribuciones(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroRetribuciones)
{
    ui->setupUi(this);

    initUi();
}

RegistroRetribuciones::~RegistroRetribuciones(){
    delete ui;
}

void RegistroRetribuciones::initUi(){

    initChks();
    rellenaListado();
    ui->btnEliminar->setEnabled(false);
    ui->btnGuardar->setEnabled(false);
    controlesClean();
    controlesOff();
    ui->listRetribuciones->setFocus();
}

void RegistroRetribuciones::initChks(){

    ui->cmbClave->addItem("SALARIO");
    ui->cmbClave->addItem("COTIZACION");
    ui->cmbClave->addItem("RETENCION");
}

void RegistroRetribuciones::controlesClean(){

    ui->txtCodigo->setText("");
    ui->txtDenominacion->setText("");
    ui->txtCuantia->setText("");
    ui->cmbClave->setCurrentIndex(0);
}

void RegistroRetribuciones::controlesOn(){

    ui->txtCodigo->setEnabled(true);
    ui->cmbClave->setEnabled(true);
    ui->txtDenominacion->setEnabled(true);
    ui->txtCuantia->setEnabled(true);
}

void RegistroRetribuciones::controlesOff(){

    ui->txtCodigo->setEnabled(false);
    ui->cmbClave->setEnabled(false);
    ui->txtDenominacion->setEnabled(false);
    ui->txtCuantia->setEnabled(false);
}

void RegistroRetribuciones::rellenaListado(){
    QString         strRegCod;
    QString         strReg;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Si no esta vacio lo vaciamos
    //
    while(ui->listRetribuciones->count()>0){
        ui->listRetribuciones->takeItem(0);
    }

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_rellena_listado");

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
    strSql = "SELECT *FROM Retribuciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strRegCod   = sql.record().value("Denominacion").toString();
        strReg      = FuncAux().desCifrar(strRegCod);
        ui->listRetribuciones->addItem(strReg);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_rellena_listado");

}

void RegistroRetribuciones::salir(){

    this->close();
}

void RegistroRetribuciones::guardar(){
    QString         strCodigoCod ;
    QString         strClaveCod;
    QString         strDenominacionCod;
    QString         strCuantiaCod;
    QString         strCodigoViejoCod       = "-1";
    QString         strRegCod               = "";
    QString         strReg                  = "";
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Codifico los valores
    //
    strCodigoCod            = FuncAux().cifrar(ui->txtCodigo->text());
    strClaveCod             = FuncAux().cifrar(ui->cmbClave->currentText());
    strDenominacionCod      = FuncAux().cifrar(ui->txtDenominacion->text());
    strCuantiaCod           = FuncAux().cifrar(ui->txtCuantia->text());

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_retribuciones");

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
    // Comprobamos si existe ese registro, si es asi asignamos el codigoViejoCod
    //
    strSql = "SELECT *FROM Retribuciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strRegCod   = sql.record().value("Codigo").toString();
        if(strRegCod != ""){strReg = FuncAux().desCifrar(strRegCod);}
        if(strReg == ui->txtCodigo->text()){
            strCodigoViejoCod = strRegCod;
            sql.last();
        }
        sql.next();
    }

    if(strCodigoViejoCod == "-1"){
        strSql = " INSERT INTO Retribuciones(Codigo,"
                 "                           Clave,"
                 "                           Denominacion,"
                 "                           Cuantia) VALUES ('" + strCodigoCod + "',"
                 "                                            '" + strClaveCod + "',"
                 "                                            '" + strDenominacionCod + "',"
                 "                                            '" + strCuantiaCod + "');";
    }
    else{
        strSql= "UPDATE Retribuciones SET Codigo ='"        + strCodigoCod +"', "
                                         "Clave ='"         + strClaveCod +"', "
                                         "Denominacion ='"  + strDenominacionCod +"', "
                                         "Cuantia ='"       + strCuantiaCod + "'  WHERE  Codigo ='" + strCodigoViejoCod + "';";
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
    dbSql.removeDatabase("con_set_retribuciones");
}

void RegistroRetribuciones::on_cmbClave_activated(int index){

}

void RegistroRetribuciones::on_txtCodigo_returnPressed(){

    ui->txtDenominacion->setFocus();
    ui->txtDenominacion->selectAll();
}

void RegistroRetribuciones::on_txtDenominacion_returnPressed(){

    ui->txtCuantia->setFocus();
    ui->txtCuantia->selectAll();
}

void RegistroRetribuciones::on_txtCuantia_returnPressed(){

    on_btnGuardar_clicked();
}

void RegistroRetribuciones::on_btnGuardar_clicked(){

    if(ui->txtCodigo->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Código no puede estar vacío");
        ui->txtCodigo->setFocus();
    }
    else if(ui->txtDenominacion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la Denominación no puede estar vacío");
        ui->txtDenominacion->setFocus();
    }
    else if(ui->txtCuantia->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la cuantía no puede estar vacío");
        ui->txtCuantia->setFocus();
    }
    else{
        guardar();
        initUi();
    }
}

void RegistroRetribuciones::on_btnEliminar_clicked(){
    QString         strRegCod;
    QString         strReg;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;
    QString         strCodigoCod = "";

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_eliminar_reg");

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
    // Busco en la tabla retribuciones el registro a eliminar
    //
    strSql = "SELECT *FROM Retribuciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strRegCod   = sql.record().value("Codigo").toString();
        strReg      = FuncAux().desCifrar(strRegCod);
        if(strReg == ui->txtCodigo->text()){
            strCodigoCod = strRegCod;
            sql.last();
        }
        sql.next();
    }

    if(strCodigoCod != ""){
        strSql = "DELETE FROM Retribuciones WHERE Codigo='" + strCodigoCod + "';";
        sql.exec(strSql);
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_eliminar_reg");

    //
    // Limpio Controles, desactivo el boton eliminar y relleno el listado
    //
    controlesClean();
    ui->btnEliminar->setEnabled(false);
    rellenaListado();
}

void RegistroRetribuciones::on_btnCancelar_clicked(){

    salir();
}

void RegistroRetribuciones::on_btnAdd_clicked(){

    controlesOn();
    controlesClean();
    ui->listRetribuciones->clearSelection();
    ui->btnGuardar->setEnabled(true);
    ui->btnEliminar->setEnabled(false);
    ui->txtCodigo->setFocus();
}

void RegistroRetribuciones::on_txtCodigo_textChanged(const QString &arg1){
    QString str;
    double  d;

    //
    // Lo pasamos a double
    //
    str = arg1;
    d   = str.toDouble();

    //
    // Si su longitud es 1, solo puede ser str == 0
    //
    if(str.length() == 1){
        if(str != "0"){
            if(d == 0){
                str.remove(str.length() - 1, 1);
                ui->txtCodigo->setText(str);
            }
        }

    }

    //
    // Si su longitud es dos solo permito str == 0.
    if(str.length() == 2){
        if(str != "0."){
            if(d == 0){
                str.remove(str.length() - 1, 1);
                ui->txtCodigo->setText(str);
            }
        }
    }

    //
    // S i su longitud es mayor de 2 solo si es numero
    //
    if(str.length() > 2 && d == 0){
        str.remove(str.length() - 1, 1);
        ui->txtCodigo->setText(str);
    }
}

void RegistroRetribuciones::on_txtCuantia_textChanged(const QString &arg1){
    QString str;
    double  d;

    //
    // Lo pasamos a double
    //
    str = arg1;
    d   = str.toDouble();

    //
    // Si su longitud es 1, solo puede ser str == 0
    //
    if(str.length() == 1){
        if(str != "0"){
            if(d == 0){
                str.remove(str.length() - 1, 1);
                ui->txtCuantia->setText(str);
            }
        }

    }

    //
    // Si su longitud es dos solo permito str == 0.
    if(str.length() == 2){
        if(str != "0."){
            if(d == 0){
                str.remove(str.length() - 1, 1);
                ui->txtCuantia->setText(str);
            }
        }
    }

    //
    // S i su longitud es mayor de 2 solo si es numero
    //
    if(str.length() > 2 && d == 0){
        str.remove(str.length() - 1, 1);
        ui->txtCuantia->setText(str);
    }
}

void RegistroRetribuciones::on_txtDenominacion_textChanged(const QString &arg1){
    QString str;
    int     i;

    str = arg1;
    i   = 0;
    while (i < str.length()) {
        if(str[i].isLower()){
            str[i] = str[i].toUpper();
            ui->txtDenominacion->setText(str);
        }
        i++;
    }


}

void RegistroRetribuciones::on_listRetribuciones_itemClicked(QListWidgetItem *item){
    QString         strRegCod;
    QString         strReg;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Desactivo los controles
    //
    controlesOff();
    ui->btnGuardar->setEnabled(false);

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_item_click");

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
    strSql = "SELECT *FROM Retribuciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strRegCod   = sql.record().value("Denominacion").toString();
        strReg      = FuncAux().desCifrar(strRegCod);
        if(strReg == item->text()){
            ui->txtCodigo->setText(FuncAux().desCifrar(sql.record().value("Codigo").toString()));
            ui->cmbClave->setCurrentText(FuncAux().desCifrar(sql.record().value("Clave").toString()));
            ui->txtDenominacion->setText(strReg);
            ui->txtCuantia->setText(FuncAux().desCifrar(sql.record().value("Cuantia").toString()));
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_item_click");

    //
    // Activamos el boton de suprimir
    //
    ui->btnEliminar->setEnabled(true);
}

void RegistroRetribuciones::on_listRetribuciones_itemDoubleClicked(QListWidgetItem *item){

    // Activo los controles
    //
    controlesOn();

    //
    // Activo el boton Guardar y desactivo el boton  -
    //
    ui->btnGuardar->setEnabled(true);

    ui->btnEliminar->setEnabled(false);
    ui->btnEliminar->setToolTip("");

    //
    // situo el foco en txtCodigo
    //
    ui->txtCodigo->setFocus();
    ui->txtCodigo->selectAll();
}

