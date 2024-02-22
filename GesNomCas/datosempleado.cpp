#include "datosempleado.h"
#include "ui_datosempleado.h"

#include "funcaux.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>


DatosEmpleado::DatosEmpleado(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatosEmpleado)
{
    ui->setupUi(this);

    initUi();
}

DatosEmpleado::~DatosEmpleado(){
    delete ui;
}

void DatosEmpleado::initUi(){

    rellenaCampos();
    ui->txtEmpleado->setFocus();
    ui->txtEmpleado->selectAll();
}

void DatosEmpleado::on_txtEmpleado_returnPressed(){

    ui->txtCategoria->setFocus();
    ui->txtCategoria->selectAll();
}

void DatosEmpleado::on_txtCategoria_returnPressed(){

    ui->txtIngreso->setFocus();
    ui->txtIngreso->selectAll();
}

void DatosEmpleado::on_txtIngreso_returnPressed(){

    ui->txtNif->setFocus();
    ui->txtNif->selectAll();
}

void DatosEmpleado::on_txtNif_returnPressed(){

    ui->txtPuesto->setFocus();
    ui->txtPuesto->selectAll();
}

void DatosEmpleado::on_txtPuesto_returnPressed(){

    ui->txtNumeroAfiliacion->setFocus();
    ui->txtNumeroAfiliacion->selectAll();
}

void DatosEmpleado::on_txtNumeroAfiliacion_returnPressed(){

    ui->txtGrupoCotizacion->setFocus();
    ui->txtGrupoCotizacion->selectAll();
}

void DatosEmpleado::on_txtGrupoCotizacion_returnPressed(){

    ui->txtCodigoOcupacion->setFocus();
    ui->txtCodigoOcupacion->selectAll();
}

void DatosEmpleado::on_txtCodigoOcupacion_returnPressed(){

    ui->txtContrato->setFocus();
    ui->txtContrato->selectAll();
}

void DatosEmpleado::on_txtContrato_returnPressed(){

    ui->txtFinContrato->setFocus();
    ui->txtFinContrato->selectAll();
}

void DatosEmpleado::on_txtFinContrato_returnPressed(){

    on_btnGuardar_clicked();
}

void DatosEmpleado::on_btnCancelar_clicked(){

    salir();
}

void DatosEmpleado::on_btnGuardar_clicked(){
    if(ui->txtEmpleado->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Empleado no puede estar vacío");
        ui->txtEmpleado->setFocus();
    }
    else if(ui->txtCategoria->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la Categoría no puede estar vacío");
        ui->txtCategoria->setFocus();
    }
    else if(ui->txtIngreso->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Ingreso no puede estar vacío");
        ui->txtIngreso->setFocus();
    }
    else if(ui->txtNif->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Nif no puede estar vacío");
        ui->txtNif->setFocus();
    }
    else if(ui->txtPuesto->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Puesto no puede estar vacío");
        ui->txtPuesto->setFocus();
    }
    else if(ui->txtNumeroAfiliacion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Numero de Afiliacion no puede estar vacío");
        ui->txtNumeroAfiliacion->setFocus();
    }
    else if(ui->txtGrupoCotizacion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Grupo de Cotización no puede estar vacío");
        ui->txtGrupoCotizacion->setFocus();
    }
    else if(ui->txtCodigoOcupacion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Código de Ocupación no puede estar vacío");
        ui->txtCodigoOcupacion->setFocus();
    }
    else if(ui->txtContrato->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Contrato no puede estar vacío");
        ui->txtContrato->setFocus();
    }
    else{
        guardar();
        salir();
    }
}

void DatosEmpleado::salir(){

    this->close();
}

void DatosEmpleado::guardar(){
    QString         strEmpleadoCod          = FuncAux().cifrar(ui->txtEmpleado->text());
    QString         strCategoriaCod         = FuncAux().cifrar(ui->txtCategoria->text());
    QString         strIngresoCod           = FuncAux().cifrar(ui->txtIngreso->text());
    QString         strNifCod               = FuncAux().cifrar(ui->txtNif->text());
    QString         strPuestoCod            = FuncAux().cifrar(ui->txtPuesto->text());
    QString         strNumeroAfiliacionCod  = FuncAux().cifrar(ui->txtNumeroAfiliacion->text());
    QString         strGrupoCotizacionCod   = FuncAux().cifrar(ui->txtGrupoCotizacion->text());
    QString         strCodigoOcupacionCod   = FuncAux().cifrar(ui->txtCodigoOcupacion->text());
    QString         strContratoCod          = FuncAux().cifrar(ui->txtContrato->text());
    QString         strFinContratoCod       = "";

    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_datos_empleado");

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
    strSql = "DELETE FROM DatosEmpleado;";
    sql.exec(strSql);

    //
    // Insertamos los datos
    //
    strSql = " INSERT INTO DatosEmpleado(Empleado,"
             "                          Categoria,"
             "                          Ingreso,"
             "                          Nif,"
             "                          Puesto,"
             "                          NumeroAfiliacion,"
             "                          GrupoCotizacion,"
             "                          CodigoOcupacion,"
             "                          Contrato,"
             "                          FinContrato) VALUES ('" + strEmpleadoCod + "',"
             "                                               '" + strCategoriaCod + "',"
             "                                               '" + strIngresoCod + "',"
             "                                               '" + strNifCod + "',"
             "                                               '" + strPuestoCod + "',"
             "                                               '" + strNumeroAfiliacionCod + "',"
             "                                               '" + strGrupoCotizacionCod + "',"
             "                                               '" + strCodigoOcupacionCod + "',"
             "                                               '" + strContratoCod + "',"
             "                                               '" + strFinContratoCod + "');";

    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_datos_empleado");

}

void DatosEmpleado::rellenaCampos(){
    QString         strEmpleadoCod;
    QString         strCategoriaCod;
    QString         strIngresoCod;
    QString         strNifCod;
    QString         strPuestoCod;
    QString         strNumeroAfiliacionCod;
    QString         strGrupoCotizacionCod;
    QString         strCodigoOcupacionCod;
    QString         strContratoCod;

    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;
    bool            todoOk;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_rellena_campos_empleados");

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
        strSql = "SELECT *FROM DatosEmpleado;";
        sql.exec(strSql);
    }

    //
    // Cogemos los valores codificados
    //
    sql.first();
    if(sql.isValid()){
        strEmpleadoCod          = sql.record().value("Empleado").toString();
        strCategoriaCod         = sql.record().value("Categoria").toString();
        strIngresoCod           = sql.record().value("Ingreso").toString();
        strNifCod               = sql.record().value("Nif").toString();
        strPuestoCod            = sql.record().value("Puesto").toString();
        strNumeroAfiliacionCod  = sql.record().value("NumeroAfiliacion").toString();
        strGrupoCotizacionCod   = sql.record().value("GrupoCotizacion").toString();
        strCodigoOcupacionCod   = sql.record().value("CodigoOcupacion").toString();
        strContratoCod          = sql.record().value("Contrato").toString();
    }

    //
    // completamos los txt
    //
    if(strEmpleadoCod == ""){ui->txtEmpleado->setText("");}else{ui->txtEmpleado->setText(FuncAux().desCifrar(strEmpleadoCod));}
    if(strCategoriaCod == ""){ui->txtCategoria->setText("");}else{ui->txtCategoria->setText(FuncAux().desCifrar(strCategoriaCod));}
    if(strIngresoCod == ""){ui->txtIngreso->setText("");}else{ui->txtIngreso->setText(FuncAux().desCifrar(strIngresoCod));}
    if(strNifCod == ""){ui->txtNif->setText("");}else{ui->txtNif->setText(FuncAux().desCifrar(strNifCod));}
    if(strPuestoCod == ""){ui->txtPuesto->setText("");}else{ui->txtPuesto->setText(FuncAux().desCifrar(strPuestoCod));}
    if(strNumeroAfiliacionCod == ""){ui->txtNumeroAfiliacion->setText("");}else{ui->txtNumeroAfiliacion->setText(FuncAux().desCifrar(strNumeroAfiliacionCod));}
    if(strGrupoCotizacionCod == ""){ui->txtGrupoCotizacion->setText("");}else{ui->txtGrupoCotizacion->setText(FuncAux().desCifrar(strGrupoCotizacionCod));}
    if(strCodigoOcupacionCod == ""){ui->txtCodigoOcupacion->setText("");}else{ui->txtCodigoOcupacion->setText(FuncAux().desCifrar(strCodigoOcupacionCod));}
    if(strContratoCod == ""){ui->txtContrato->setText("");}else{ui->txtContrato->setText(FuncAux().desCifrar(strContratoCod));}


    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_rellena_campos_empleados");
}
