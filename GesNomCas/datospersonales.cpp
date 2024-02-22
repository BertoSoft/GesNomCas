#include "datospersonales.h"
#include "ui_datospersonales.h"

#include "funcaux.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

DatosPersonales::DatosPersonales(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatosPersonales){

    ui->setupUi(this);

    initUi();
}

DatosPersonales::~DatosPersonales(){
    delete ui;
}

void DatosPersonales::initUi(){

    rellenaCampos();
    ui->txtNombre->setFocus();
    ui->txtNombre->selectAll();
}

void DatosPersonales::rellenaCampos(){
    QString         strNombreCod;
    QString         strApellidosCod;
    QString         strDireccionCod;
    QString         strCodigoPostalCod;
    QString         strPoblacionCod;
    QString         strProvinciaCod;
    QString         strPaisCod;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_rellena_campos");

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
        strSql = "SELECT *FROM DatosPersonales;";
        sql.exec(strSql);
    }

    //
    // Cogemos los valores codificados
    //
    sql.first();
    if(sql.isValid()){
        strNombreCod        = sql.record().value("Nombre").toString();
        strApellidosCod     = sql.record().value("Apellidos").toString();
        strDireccionCod     = sql.record().value("Direccion").toString();
        strCodigoPostalCod  = sql.record().value("CodigoPostal").toString();
        strPoblacionCod     = sql.record().value("Poblacion").toString();
        strProvinciaCod     = sql.record().value("Provincia").toString();
        strPaisCod          = sql.record().value("Pais").toString();
    }

    //
    // completamos los txt
    //
    if(strNombreCod == ""){ui->txtNombre->setText("");}else{ui->txtNombre->setText(FuncAux().desCifrar(strNombreCod));}
    if(strApellidosCod == ""){ui->txtApellidos->setText("");}else{ui->txtApellidos->setText(FuncAux().desCifrar(strApellidosCod));}
    if(strDireccionCod == ""){ui->txtDireccion->setText("");}else{ui->txtDireccion->setText(FuncAux().desCifrar(strDireccionCod));}
    if(strCodigoPostalCod == ""){ui->txtCodigoPostal->setText("");}else{ui->txtCodigoPostal->setText(FuncAux().desCifrar(strCodigoPostalCod));}
    if(strPoblacionCod == ""){ui->txtPoblacion->setText("");}else{ui->txtPoblacion->setText(FuncAux().desCifrar(strPoblacionCod));}
    if(strProvinciaCod == ""){ui->txtProvincia->setText("");}else{ui->txtProvincia->setText(FuncAux().desCifrar(strProvinciaCod));}
    if(strPaisCod == ""){ui->txtPais->setText("");}else{ui->txtPais->setText(FuncAux().desCifrar(strPaisCod));}


    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_rellena_campos");
}

void DatosPersonales::on_txtNombre_returnPressed(){

    ui->txtApellidos->setFocus();
    ui->txtApellidos->selectAll();
}

void DatosPersonales::on_txtApellidos_returnPressed(){

    ui->txtDireccion->setFocus();
    ui->txtDireccion->selectAll();
}

void DatosPersonales::on_txtDireccion_returnPressed(){

    ui->txtCodigoPostal->setFocus();
    ui->txtCodigoPostal->selectAll();
}

void DatosPersonales::on_txtCodigoPostal_returnPressed(){

    ui->txtPoblacion->setFocus();
    ui->txtPoblacion->selectAll();
}

void DatosPersonales::on_txtPoblacion_returnPressed(){

    ui->txtProvincia->setFocus();
    ui->txtProvincia->selectAll();
}

void DatosPersonales::on_txtProvincia_returnPressed(){

    ui->txtPais->setFocus();
    ui->txtPais->selectAll();
}

void DatosPersonales::on_txtPais_returnPressed(){

    on_btnGuardar_clicked();
}

void DatosPersonales::on_btnCancelar_clicked(){

    salir();
}

void DatosPersonales::on_btnGuardar_clicked(){

    if(ui->txtNombre->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Nombre no puede estar vacío");
        ui->txtNombre->setFocus();
    }
    else if(ui->txtApellidos->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de los apellidos no puede estar vacío");
        ui->txtApellidos->setFocus();
    }
    else if(ui->txtDireccion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la dirección no puede estar vacío");
        ui->txtDireccion->setFocus();
    }
    else if(ui->txtCodigoPostal->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Código Postal no puede estar vacío");
        ui->txtCodigoPostal->setFocus();
    }
    else if(ui->txtPoblacion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la población no puede estar vacío");
        ui->txtPoblacion->setFocus();
    }
    else if(ui->txtProvincia->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la provincia no puede estar vacío");
        ui->txtProvincia->setFocus();
    }
    else if(ui->txtPais->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del País no puede estar vacío");
        ui->txtPais->setFocus();
    }
    else{
        guardar();
        salir();
    }
}

void DatosPersonales::salir(){

    this->close();
}

void DatosPersonales::guardar(){
    QString         strNombreCod        = FuncAux().cifrar(ui->txtNombre->text());
    QString         strApellidosCod     = FuncAux().cifrar(ui->txtApellidos->text());
    QString         strDireccionCod     = FuncAux().cifrar(ui->txtDireccion->text());
    QString         strCodigoPostalCod  = FuncAux().cifrar(ui->txtCodigoPostal->text());
    QString         strPoblacionCod     = FuncAux().cifrar(ui->txtPoblacion->text());
    QString         strProvinciaCod     = FuncAux().cifrar(ui->txtProvincia->text());
    QString         strPaisCod          = FuncAux().cifrar(ui->txtPais->text());
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_datos_personales");

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
    // Si existe algun registro lo borramos
    //
    strSql = "DELETE FROM DatosPersonales;";
    sql.exec(strSql);

    //
    // Insertamos los datos
    //
    strSql = " INSERT INTO DatosPersonales(Nombre,"
             "                             Apellidos,"
             "                             Direccion,"
             "                             CodigoPostal,"
             "                             Poblacion,"
             "                             Provincia,"
             "                             Pais) VALUES ('" + strNombreCod + "',"
             "                                           '" + strApellidosCod + "',"
             "                                           '" + strDireccionCod + "',"
             "                                           '" + strCodigoPostalCod + "',"
             "                                           '" + strPoblacionCod + "',"
             "                                           '" + strProvinciaCod + "',"
             "                                           '" + strPaisCod + "');";

    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_datos_personales");
}


