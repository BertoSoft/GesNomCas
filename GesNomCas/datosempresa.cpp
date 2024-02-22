#include "datosempresa.h"
#include "ui_datosempresa.h"

#include "funcaux.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

DatosEmpresa::DatosEmpresa(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatosEmpresa)
{
    ui->setupUi(this);

    initUi();
}

DatosEmpresa::~DatosEmpresa(){
    delete ui;
}

void DatosEmpresa::initUi(){

    rellenaCampos();
    ui->txtEmpresa->setFocus();
    ui->txtEmpresa->selectAll();
}

void DatosEmpresa::on_txtEmpresa_returnPressed(){

    ui->txtDomicilio->setFocus();
    ui->txtDomicilio->selectAll();
}

void DatosEmpresa::on_txtDomicilio_returnPressed(){

    ui->txtNumeroPatronal->setFocus();
    ui->txtNumeroPatronal->selectAll();
}

void DatosEmpresa::on_txtNumeroPatronal_returnPressed(){

    ui->txtCentroTrabajo->setFocus();
    ui->txtCentroTrabajo->selectAll();
}

void DatosEmpresa::on_txtCentroTrabajo_returnPressed(){

    ui->txtCif->setFocus();
    ui->txtCif->selectAll();
}

void DatosEmpresa::on_txtCif_returnPressed(){

    ui->txtActividad->setFocus();
    ui->txtActividad->selectAll();
}

void DatosEmpresa::on_txtActividad_returnPressed(){

    ui->txtConvenio->setFocus();
    ui->txtConvenio->selectAll();
}

void DatosEmpresa::on_txtConvenio_returnPressed(){

    on_btnGuardar_clicked();
}

void DatosEmpresa::on_btnCancelar_clicked(){

    salir();
}

void DatosEmpresa::on_btnGuardar_clicked(){

    if(ui->txtEmpresa->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Nombre de la Empresa no puede estar vacío");
        ui->txtEmpresa->setFocus();
    }
    else if(ui->txtDomicilio->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la direccion de la Empresa no puede estar vacío");
        ui->txtDomicilio->setFocus();
    }
    else if(ui->txtNumeroPatronal->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Número de Patronal no puede estar vacío");
        ui->txtNumeroPatronal->setFocus();
    }
    else if(ui->txtCentroTrabajo->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Centro de Trabajo no puede estar vacío");
        ui->txtCentroTrabajo->setFocus();
    }
    else if(ui->txtCif->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del C.I.F. de la Empresa no puede estar vacío");
        ui->txtCif->setFocus();
    }
    else if(ui->txtActividad->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la Actividad de la Empresa no puede estar vacío");
        ui->txtActividad->setFocus();
    }
    else if(ui->txtConvenio->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Convenio no puede estar vacío");
        ui->txtConvenio->setFocus();
    }
    else{
        guardar();
        salir();
    }
}

void DatosEmpresa::salir(){

    this->close();
}

void DatosEmpresa::guardar(){
    QString         strEmpresaCod           = FuncAux().cifrar(ui->txtEmpresa->text());
    QString         strDomicilioCod         = FuncAux().cifrar(ui->txtDomicilio->text());
    QString         strNumeroPatronalCod    = FuncAux().cifrar(ui->txtNumeroPatronal->text());
    QString         strCentroTrabajoCod     = FuncAux().cifrar(ui->txtCentroTrabajo->text());
    QString         strCifCod               = FuncAux().cifrar(ui->txtCif->text());
    QString         strActividadCod         = FuncAux().cifrar(ui->txtActividad->text());
    QString         strConvenioCod          = FuncAux().cifrar(ui->txtConvenio->text());
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_datos_empresa");

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
    strSql = "DELETE FROM DatosEmpresa;";
    sql.exec(strSql);

    //
    // Insertamos los datos
    //
    strSql = " INSERT INTO DatosEmpresa(Empresa,"
             "                          Domicilio,"
             "                          NumeroPatronal,"
             "                          CentroTrabajo,"
             "                          Cif,"
             "                          Actividad,"
             "                          Convenio) VALUES ('" + strEmpresaCod + "',"
             "                                            '" + strDomicilioCod + "',"
             "                                            '" + strNumeroPatronalCod + "',"
             "                                            '" + strCentroTrabajoCod + "',"
             "                                            '" + strCifCod + "',"
             "                                            '" + strActividadCod + "',"
             "                                            '" + strConvenioCod + "');";

    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_datos_empresa");

}

void DatosEmpresa::rellenaCampos(){
    QString         strEmpresaCod;
    QString         strDomicilioCod;
    QString         strNumeroPatronalCod;
    QString         strCentroTrabajoCod;
    QString         strCifCod;
    QString         strActividadCod;
    QString         strConvenioCod;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_rellena_campos_empresa");

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
        strSql = "SELECT *FROM DatosEmpresa;";
        sql.exec(strSql);
    }

    //
    // Cogemos los valores codificados
    //
    sql.first();
    if(sql.isValid()){
        strEmpresaCod           = sql.record().value("Empresa").toString();
        strDomicilioCod         = sql.record().value("Domicilio").toString();
        strNumeroPatronalCod    = sql.record().value("NumeroPatronal").toString();
        strCentroTrabajoCod     = sql.record().value("CentroTrabajo").toString();
        strCifCod               = sql.record().value("Cif").toString();
        strActividadCod         = sql.record().value("Actividad").toString();
        strConvenioCod          = sql.record().value("Convenio").toString();
    }

    //
    // completamos los txt
    //
    if(strEmpresaCod == ""){ui->txtEmpresa->setText("");}else{ui->txtEmpresa->setText(FuncAux().desCifrar(strEmpresaCod));}
    if(strDomicilioCod == ""){ui->txtDomicilio->setText("");}else{ui->txtDomicilio->setText(FuncAux().desCifrar(strDomicilioCod));}
    if(strNumeroPatronalCod == ""){ui->txtNumeroPatronal->setText("");}else{ui->txtNumeroPatronal->setText(FuncAux().desCifrar(strNumeroPatronalCod));}
    if(strCentroTrabajoCod == ""){ui->txtCentroTrabajo->setText("");}else{ui->txtCentroTrabajo->setText(FuncAux().desCifrar(strCentroTrabajoCod));}
    if(strCifCod == ""){ui->txtCif->setText("");}else{ui->txtCif->setText(FuncAux().desCifrar(strCifCod));}
    if(strActividadCod == ""){ui->txtActividad->setText("");}else{ui->txtActividad->setText(FuncAux().desCifrar(strActividadCod));}
    if(strConvenioCod == ""){ui->txtConvenio->setText("");}else{ui->txtConvenio->setText(FuncAux().desCifrar(strConvenioCod));}


    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_rellena_campos_empresa");
}

