#include "funcaux.h"

#include <QSqlDatabase>
#include <QSqlQuery>

FuncAux::FuncAux() {

    //
    // Aqui irá el constructor
    //
    ruta_db_GesNomCas = qApp->applicationDirPath() + "/Data/GesNomCas.db";

}

bool FuncAux::existeUsuario(){
    QSqlDatabase    db_sql;
    QSqlQuery       sql;
    bool            todo_ok = false;
    bool            retorno = false;

    //
    // Creo la conexion con la BD
    //
    db_sql = QSqlDatabase::addDatabase("QSQLITE", "conecta_sql");

    //
    // Establezco la ruta de la BD
    //
    db_sql.setDatabaseName(ruta_db_GesNomCas);

    //
    // Si se abre y no da error, creamos el sqlQuery
    //
    todo_ok = db_sql.open();
    if(todo_ok){
        sql = QSqlQuery(db_sql);
    }

    //
    // Cargamos la tabla Usuario
    //
    str_sql = "SELECT *FROM Usuario";
    sql.exec(str_sql);
    sql.first();
    if(sql.isValid()){
        retorno = true;
    }
    else{
        retorno = false;
    }
    //
    // Cerramos la Bd
    //
    db_sql.close();
    db_sql.removeDatabase("conecta_sql");

    return retorno;
}
