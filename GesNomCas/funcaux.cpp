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
    ruta_db_GesNomCas = qApp->applicationDirPath() + "/Data/GesNomCas.db";

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
    QSqlDatabase    db_sql;
    QSqlQuery       sql;
    QString         str_sql;
    bool            todo_ok = true;

    //
    // Creo la conexion con la BD
    //
    db_sql = QSqlDatabase::addDatabase("QSQLITE", "con_crear_bd");


    //
    // Establezco la ruta de la BD
    //
    db_sql.setDatabaseName(ruta_db_GesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todo_ok = db_sql.open();
    if(todo_ok){
        sql = QSqlQuery(db_sql);
        str_sql = "CREATE TABLE if not exists RegistroSesiones(_ID INTEGER PRIMARY KEY AUTOINCREMENT,FechaInicio TEXT, "
                  "                                                                                 HoraInicio TEXT,"
                  "                                                                                 FechaCierre TEXT,"
                  "                                                                                 HoraCierre TEXT);";
        sql.exec(str_sql);

        str_sql = "CREATE TABLE if not exists Usuario(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Usuario TEXT, "
                  "                                                                          Passwd TEXT);";
        sql.exec(str_sql);

    }
    //
    // Cerramos la BD y la Conexion
    //
    db_sql.close();
    db_sql = QSqlDatabase();
    db_sql.removeDatabase("con_crear_bd");

    return todo_ok;

}

bool FuncAux::existeUsuario(){
    bool    retorno = false;
    bool    todo_ok = false;

    //
    // Creo la conexion con la BD
    //
    db_sql = QSqlDatabase::addDatabase("QSQLITE", "con_existe_usuario");

    //
    // Establezco la ruta de la BD
    //
    db_sql.setDatabaseName(ruta_db_GesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
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
    // Cerramos la BD y la Conexion
    //
    db_sql.close();
    db_sql = QSqlDatabase();
    db_sql.removeDatabase("con_existe_usuario");

    return retorno;
}

bool FuncAux::haySesionIniciada(){
    QString fechaCierre = "";
    bool    retorno     = false;
    bool    todo_ok     = false;

    //
    // Creo la conexion con la BD
    //
    db_sql = QSqlDatabase::addDatabase("QSQLITE", "con_hay_sesion_iniciada");

    //
    // Establezco la ruta de la BD
    //
    db_sql.setDatabaseName(ruta_db_GesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todo_ok = db_sql.open();
    if(todo_ok){
        sql = QSqlQuery(db_sql);
    }

    //
    // Cargamos la tabla Registro de sesiones
    //
    str_sql = "SELECT *FROM RegistroSesiones";
    sql.exec(str_sql);
    sql.last();

    //
    // Si el ultimo registro no es valido devolvemos false
    //
    if(!sql.isValid()){
        retorno = false;
    }
    //
    // Si es valido, comprobamos si hay cierre de sesion
    //
    else{
        fechaCierre = sql.record().value("FechaCierre").toString();
    }

    if(fechaCierre != ""){
        retorno = true;
    }

    //
    // Cerramos la BD y la Conexion
    //
    db_sql.close();
    db_sql = QSqlDatabase();
    db_sql.removeDatabase("con_hay_sesion_iniciada");


    return retorno;
}

void FuncAux::setInicioSesion(QString fecha, QString hora){
    QString     fechaCod    = cifrar(fecha);
    QString     horaCod     = cifrar(hora);
    bool        todo_ok     = false;

    //
    // Creo la conexion con la BD
    //
    db_sql = QSqlDatabase::addDatabase("QSQLITE", "con_set_inicio_sesion");

    //
    // Establezco la ruta de la BD
    //
    db_sql.setDatabaseName(ruta_db_GesNomCas);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todo_ok = db_sql.open();
    if(todo_ok){
        sql = QSqlQuery(db_sql);
    }

    //
    // Comprobamos si ya hay una sesion iniciada
    //
    if(!(bool)haySesionIniciada()){
        str_sql = "INSERT INTO RegistroSesiones(FechaInicio, HoraInicio) VALUES ('" + fechaCod + "', '" + horaCod + "')";
        sql.exec(str_sql);
    }

    //
    // Cerramos la BD y la Conexion
    //
    db_sql.close();
    db_sql = QSqlDatabase();
    db_sql.removeDatabase("con_set_inicio_sesion");


}

void FuncAux::setCierreSesion(){

}

void FuncAux::setUsuario(QString usuario, QString passwd){
    QString         usuarioCod;
    QString         passwdCod;

    //
    // Codificamos los valores
    //
    usuarioCod = cifrar(usuario);
    passwdCod = cifrar(passwd);

    //
    // Si existe Usuario lo borramos
    //
    str_sql = "DELETE *FROM Usuario";
    sql.exec(str_sql);

    //
    // Insertamos los valores
    //
    str_sql = "INSERT INTO Usuario(Usuario, Passwd) VALUES ('" + usuarioCod + "', '" + passwdCod + "')";
    sql.exec(str_sql);
}
