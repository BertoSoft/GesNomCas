#include "funcaux.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/rdrand.h>


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>


#include <QCoreApplication>
#include <QByteArray>

#define KEY "U82HuXLNzbX3f6r"
#define IV  "epDKqfVtYXhdXgb"


using namespace CryptoPP;

FuncAux::FuncAux() {

    //
    // Aqui irá el constructor
    //
    rutaDbGesNomCas = qApp->applicationDirPath() + "/Data/GesNomCas.db";

}

FuncAux::~FuncAux(){}

QString FuncAux::getAppName(){

    return "GesNomCas V 1.0";
}

QString FuncAux::getRutaDb(){

    return rutaDbGesNomCas;
}

QString FuncAux::cifrar(QString strTextoPlano){
    QString                     strTextoCod;
    byte                        key[AES::DEFAULT_KEYLENGTH] = KEY;
    byte                        iv[AES::BLOCKSIZE];
    CBC_Mode<AES>::Encryption   Encrypt;
    std::string                 std_Str, std_TextoCod, std_textoCodHex, std_strCompletelyEncrypted;
    RandomPool                  prng;
    std::string                 std_iv, std_ivHex;

    //
    // Generamos la Iv Aleatoria y no salimos hasta que tenga 16 bytes
    //
    std_iv.clear();

    while (std_iv.length() != 16) {
        std_iv.clear();
        prng.GenerateBlock(iv, 16);
        char char_iv[16];
        memcpy(&char_iv, iv, sizeof(iv));
        std_iv.append(char_iv, 0, 16);
    }

    //
    // Pasamos de QString a std::string
    //
    std_Str = strTextoPlano.toStdString();

    //
    // Codificamos
    //
    Encrypt.SetKeyWithIV(key,sizeof(key),iv);
    StringSource(std_Str,true,new StreamTransformationFilter(Encrypt,new StringSink(std_TextoCod)));

    //
    // Pasamos Texto a Hex
    //
    StringSource(std_TextoCod,true,new HexEncoder(new StringSink(std_textoCodHex)));

    //
    // Pasamos iv a Hex
    //
    StringSource(std_iv,true,new HexEncoder(new StringSink(std_ivHex)));

    //
    // Fusionamos iv y texto
    //
    std_strCompletelyEncrypted = std_ivHex;
    std_strCompletelyEncrypted.append(std_textoCodHex);

    strTextoCod = QString::fromStdString(std_strCompletelyEncrypted);

    return strTextoCod;
}

QString FuncAux::desCifrar(QString strTextoCodHex){
    QString                     strTextoDes;
    byte                        key[AES::DEFAULT_KEYLENGTH] = KEY;
    byte                        iv[AES::BLOCKSIZE];
    RandomPool                  prng;
    CBC_Mode<AES>::Decryption   Decrypt;
    std::string                 std_Str, std_TextoCod, std_textoCodHex, std_strCompletelyEncrypted;
    std::string                 std_iv, std_ivHex;

    //
    // Sacamos la ivHex
    //
    std_strCompletelyEncrypted = strTextoCodHex.toStdString();

    std_ivHex       = std_strCompletelyEncrypted.substr(0, 32);
    std_textoCodHex = std_strCompletelyEncrypted.substr(32, std_strCompletelyEncrypted.length() - 32);


    //
    // Pasamos de Hex a Char
    //
    StringSource(std_textoCodHex,true,new HexDecoder(new StringSink(std_TextoCod)));
    StringSource(std_ivHex,true,new HexDecoder(new StringSink(std_iv)));

    //
    // Asignamos std_iv a byte iv
    //
    memcpy(iv, std_iv.c_str(), std_iv.length());

    //
    // Decodificamos
    //
    Decrypt.SetKeyWithIV(key,sizeof(key),iv);
    StringSource(std_TextoCod,true,new StreamTransformationFilter(Decrypt,new StringSink(std_Str)));

    strTextoDes = QString::fromStdString(std_Str);

    return strTextoDes;
}

bool FuncAux::crearDb(){
    bool            todoOk = true;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_crear_bd");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "CREATE TABLE if not exists RegistroSesiones(_ID INTEGER PRIMARY KEY AUTOINCREMENT,FechaInicio TEXT, "
                  "                                                                                 HoraInicio TEXT,"
                  "                                                                                 FechaCierre TEXT,"
                  "                                                                                 HoraCierre TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists Usuario(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Usuario TEXT, "
                  "                                                                        Passwd TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists DatosPersonales(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Nombre TEXT, "
                 "                                                                                 Apellidos TEXT,"
                 "                                                                                 Direccion TEXT,"
                 "                                                                                 CodigoPostal TEXT,"
                 "                                                                                 Poblacion TEXT,"
                 "                                                                                 Provincia TEXT,"
                 "                                                                                 Pais TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists DatosEmpresa(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Empresa TEXT, "
                 "                                                                              Domicilio TEXT,"
                 "                                                                              NumeroPatronal TEXT,"
                 "                                                                              CentroTrabajo TEXT,"
                 "                                                                              Cif TEXT,"
                 "                                                                              Actividad TEXT,"
                 "                                                                              Convenio TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists DatosEmpleado(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Empleado TEXT, "
                 "                                                                               Categoria TEXT,"
                 "                                                                               Ingreso TEXT,"
                 "                                                                               Nif TEXT,"
                 "                                                                               Puesto TEXT,"
                 "                                                                               NumeroAfiliacion TEXT,"
                 "                                                                               GrupoCotizacion TEXT,"
                 "                                                                               CodigoOcupacion TEXT,"
                 "                                                                               Contrato TEXT,"
                 "                                                                               FinContrato TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists Retribuciones(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Codigo TEXT, "
                 "                                                                               Clave TEXT,"
                 "                                                                               Denominacion TEXT,"
                 "                                                                               Cuantia TEXT);";
        sql.exec(strSql);
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_crear_bd");

    return todoOk;
}

bool FuncAux::existeUsuario(){
    bool    retorno     = false;
    bool    todoOk      = false;
    QString usuarioCod  = "";

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_existe_usuario");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Cargamos la tabla Usuario
    //
    strSql = "SELECT *FROM Usuario";
    sql.exec(strSql);
    sql.first();
    if(sql.isValid()){
        usuarioCod = sql.record().value("Usuario").toString();
        if(usuarioCod != ""){
            retorno = true;
        }
    }
    else{
        retorno = false;
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_existe_usuario");

    return retorno;
}

void FuncAux::setInicioSesion(QString fecha, QString hora){
    QString fechaCod            = cifrar(fecha);
    QString horaCod             = cifrar(hora);
    QString fechaCierre         = "";
    bool    todoOk              = false;
    bool    haySesionIniciada   = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_inicio_sesion");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Comprobamos si ya hay una sesion iniciada
    //
    strSql = "SELECT *FROM RegistroSesiones";
    sql.exec(strSql);
    sql.last();

    //
    // Si el ultimo registro es valido, comprobamos si hay cierre de sesion
    //
    if(sql.isValid()){
        fechaCierre = sql.record().value("FechaCierre").toString();
        if(fechaCierre == ""){
            haySesionIniciada = true;
        }
    }

    if(!haySesionIniciada){
        strSql = "INSERT INTO RegistroSesiones(FechaInicio, HoraInicio) VALUES ('" + fechaCod + "', '" + horaCod + "')";
        sql.exec(strSql);
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_inicio_sesion");

}

void FuncAux::setCierreSesion(QString fecha, QString hora){
    QString fechaCierreCod    = cifrar(fecha);
    QString horaCierreCod     = cifrar(hora);
    QString fechaInicioCod;
    QString horaInicioCod;
    bool    todoOk             = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_cierre_sesion");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Vamos al ultimo registro que es la sesion iniciada
    //
    strSql = "SELECT *FROM RegistroSesiones";
    sql.exec(strSql);
    sql.last();

    fechaInicioCod  = sql.record().value("FechaInicio").toString();
    horaInicioCod   = sql.record().value("HoraInicio").toString();

    strSql= "UPDATE RegistroSesiones SET FechaCierre ='" + fechaCierreCod + "', "
                                         "HoraCierre ='" + horaCierreCod + "'  WHERE FechaInicio ='" + fechaInicioCod + "' AND "
                                                                                      "HoraInicio ='" + horaInicioCod + "';";

    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_cierre_sesion");

}

void FuncAux::setUsuario(QString usuario, QString passwd){
    QString     usuarioCod;
    QString     passwdCod;
    bool        todoOk     = false;

    //
    // Codificamos los valores
    //
    usuarioCod = cifrar(usuario);
    passwdCod = cifrar(passwd);

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_usuario");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Si existe Usuario lo borramos
    //
    strSql = "DELETE *FROM Usuario";
    sql.exec(strSql);

    //
    // Insertamos los valores
    //
    strSql = "INSERT INTO Usuario(Usuario, Passwd) VALUES ('" + usuarioCod + "', '" + passwdCod + "')";
    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_usuario");
}

QString FuncAux::getUser(){
    QString usuario     = "";
    QString usuarioCod;
    bool    todoOk     = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_user");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    strSql = "SELECT *FROM Usuario";
    sql.exec(strSql);
    sql.first();
    usuarioCod  = sql.record().value("Usuario").toString();
    usuario     = desCifrar(usuarioCod);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_user");

    return usuario;
}

QString FuncAux::getPasswd(){
    QString passwd      = "";
    QString passwdCod;
    bool    todoOk     = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_passwd");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    strSql = "SELECT *FROM Usuario";
    sql.exec(strSql);
    sql.first();
    passwdCod   = sql.record().value("Passwd").toString();
    passwd      = desCifrar(passwdCod);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_passwd");

    return passwd;
}

bool FuncAux::esFormatoDatos(QString rutaArchivo){
    bool    esFormatoDatos  = false;
    bool    todoOk          = false;
    QString usuarioCod      = "";
    QString usuario         = "";

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_es_formato_datos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaArchivo);

    //
    // Si se abre y no da error, creamos la sqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "SELECT *FROM Usuario";
        sql.exec(strSql);
        sql.first();

        usuarioCod  = sql.record().value("Usuario").toString();
    }

    //
    // Desciframos un registro, si no da error es que es correcto el formato del archivo
    //
    if(usuarioCod != ""){
        try {
            esFormatoDatos = true;
            usuario = desCifrar(usuarioCod);
        }
        catch(...) {
            esFormatoDatos = false;
        }
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_es_formato_datos");

    return esFormatoDatos;
}

QString FuncAux::primerRegistroDatos(QString rutaArchivo){
    QString fechaPrimerRegistroCod  = "";
    QString fechaPrimerRegistro     = "";
    bool    todoOk                  = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_primer_registro_datos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaArchivo);

    //
    // Si se abre y no da error, creamos la sqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "SELECT *FROM RegistroSesiones";
        sql.exec(strSql);
        sql.first();
    }

    if(sql.isValid()) fechaPrimerRegistroCod = sql.record().value("FechaInicio").toString();
    if(fechaPrimerRegistroCod != "")fechaPrimerRegistro = desCifrar(fechaPrimerRegistroCod);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_primer_registro_datos");

    return fechaPrimerRegistro;
}

QString FuncAux::ultimoRegistroDatos(QString rutaArchivo){
    QString fechaUltimoRegistroCod  = "";
    QString fechaUltimoRegistro     = "";
    bool    todoOk                  = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_ultimo_registro_datos");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaArchivo);

    //
    // Si se abre y no da error, creamos la sqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "SELECT *FROM RegistroSesiones";
        sql.exec(strSql);

        sql.last();
    }

    if(sql.isValid()) fechaUltimoRegistroCod = sql.record().value("FechaInicio").toString();
    if(fechaUltimoRegistroCod != "") fechaUltimoRegistro = desCifrar(fechaUltimoRegistroCod);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_ultimo_registro_datos");

    return fechaUltimoRegistro;
}

bool FuncAux::esFormatoIncidencias(QString rutaArchivo){
    bool    esFormatoIncidencias    = false;
    bool    todoOk                  = false;
    QDate   date;
    struct  Incidencias datosIncidencias;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_es_formato_incidencias");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaArchivo);

    //
    // Si se abre y no da error, creamos la sqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "SELECT *FROM Incidencias";
        sql.exec(strSql);
        sql.first();
    }


    while (sql.isValid()) {
        datosIncidencias.fecha = sql.record().value("Fecha").toString();
        datosIncidencias.hed = sql.record().value("Hed").toString();
        datosIncidencias.hen = sql.record().value("Hen").toString();
        datosIncidencias.hef = sql.record().value("Hef").toString();
        datosIncidencias.voladuras = sql.record().value("Voladuras").toString();

        date = fechaCortaToDate(datosIncidencias.fecha);
        if(date.isValid()){
            if(datosIncidencias.hed != "" || datosIncidencias.hen != "" || datosIncidencias.hef != "" || datosIncidencias.voladuras != ""){
                esFormatoIncidencias = true;
                sql.last();
            }
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_es_formato_incidencias");

    return esFormatoIncidencias;

}

QString FuncAux::primerRegistroIncidencias(QString rutaArchivo){
    QString fechaPrimerRegistro     = "";
    bool    todoOk                  = false;
    QDate   date                    = QDate::currentDate();
    QDate   dateMenor               = QDate::currentDate();
    struct  Incidencias incidencias;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_primer_registro_incidencias");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaArchivo);

    //
    // Si se abre y no da error, creamos la sqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "SELECT *FROM Incidencias";
        sql.exec(strSql);
        sql.first();
    }

    while (sql.isValid()) {
        incidencias.fecha = sql.record().value("Fecha").toString();
        date = fechaCortaToDate(incidencias.fecha);
        if(date.isValid() && date < dateMenor){
            dateMenor = date;
            fechaPrimerRegistro = incidencias.fecha;
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_primer_registro_incidencias");

    return fechaPrimerRegistro;
}

QString FuncAux::ultimoRegistroIncidencias(QString rutaArchivo){
    QString fechaUltimoRegistro     = "";
    bool    todoOk                  = false;
    QDate   date                    = QDate::currentDate();
    QDate   dateMayor;
    struct  Incidencias incidencias;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_ultimo_registro_incidencias");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaArchivo);

    //
    // Si se abre y no da error, creamos la sqlQuery
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
        strSql = "SELECT *FROM Incidencias";
        sql.exec(strSql);
        sql.first();
    }

    while (sql.isValid()) {
        incidencias.fecha = sql.record().value("Fecha").toString();
        date = fechaCortaToDate(incidencias.fecha);
        if(date.isValid() && date > dateMayor){
            dateMayor = date ;
            fechaUltimoRegistro = incidencias.fecha;
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_ultimo_registro_incidencias");

    return fechaUltimoRegistro;
}

QDate FuncAux::fechaCortaToDate(QString strFecha){
    QDate datFecha;
    int iY,iM,iD;
    QString strY,strM,strD,str;

    //
    // Si el caracter 3 y el 6  son / formato correcto
    //
    if(strFecha.length() == 10 && strFecha[2] == '/' && strFecha[5] == '/'){
        str=strFecha;
        str.truncate(2);
        strD=str;
        str=strFecha;
        str.truncate(5);
        str.remove(0,3);
        strM=str;
        str=strFecha;
        str.remove(0,(str.length()-4));
        strY=str;
        iY=strY.toInt();
        iM=strM.toInt();
        iD=strD.toInt();
        datFecha.setDate(iY,iM,iD);
    }
    //
    // Formato incorrecto
    //
    else{
        datFecha.setDate(-1,-1,-1);
    }
    return datFecha;
}
