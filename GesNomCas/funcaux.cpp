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
                  "                                                                          Passwd TEXT);";
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
    bool    retorno = false;
    bool    todoOk = false;

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
        retorno = true;
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
