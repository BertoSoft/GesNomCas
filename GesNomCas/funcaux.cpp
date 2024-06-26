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
#include <QLocale>


#include <QCoreApplication>
#include <QByteArray>

#define KEY "U82HuXLNzbX3f6r"
#define IV  "epDKqfVtYXhdXgb"


using namespace CryptoPP;


FuncAux::FuncAux() {

    //
    // Aqui irá el constructor
    //
    rutaDbGesNomCas     = qApp->applicationDirPath() + "/Data/GesNomCas.db";
    rutaDbIncidencias   = qApp->applicationDirPath() + "/Data/Incidencias.db";

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

    if(strTextoCodHex != ""){

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

    }
    else{
        strTextoDes = "";
    }

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

        strSql = "CREATE TABLE if not exists Festivos(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Fecha TEXT, "
                 "                                                                          TipoFestivo TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists Vacaciones(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Ano TEXT, "
                 "                                                                            FechaInicio TEXT,"
                 "                                                                            FechaFin TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists VacacionesPendientes(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Ano TEXT, "
                 "                                                                                      Dias TEXT);";
        sql.exec(strSql);

        strSql = "CREATE TABLE if not exists Nominas(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Ano TEXT, "
                 "                                                                         Mes TEXT,"
                 "                                                                         Codigo TEXT,"
                 "                                                                         Clave TEXT,"
                 "                                                                         Denominacion TEXT,"
                 "                                                                         Cantidad TEXT,"
                 "                                                                         Precio TEXT,"
                 "                                                                         Importe TEXT,"
                 "                                                                         Remuneracion TEXT,"
                 "                                                                         RemuneracionPE TEXT,"
                 "                                                                         Prorrateo TEXT,"
                 "                                                                         Deducciones TEXT,"
                 "                                                                         Irpf TEXT,"
                 "                                                                         TipoCC TEXT,"
                 "                                                                         TipoATEP TEXT,"
                 "                                                                         TipoDesempleo TEXT,"
                 "                                                                         TipoFormacion TEXT,"
                 "                                                                         TipoFogasa TEXT,"
                 "                                                                         TipoMei TEXT,"
                 "                                                                         SumaSalarioBruto TEXT,"
                 "                                                                         SumaIrpf TEXT,"
                 "                                                                         SumaGastosDeducibles TEXT);";
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

void FuncAux::setVacacionesPendientes(DatosVacacionesPendientes dato){
    QString strAnoOldCod    = "-1";
    QString strAnoCod;
    QString strDiasCod;
    bool    todoOk          = false;

    //
    // Codificamos el dato
    //
    strAnoCod   = cifrar(dato.strAno);
    strDiasCod  = cifrar(dato.strDias);

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_vacaciones_pendientes");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, abrimos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Comprobamos si existe registro ese año
    //
    strSql = "SELECT *FROM VacacionesPendientes";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        if(dato.strAno == desCifrar(sql.record().value("Ano").toString())){
            strAnoOldCod = sql.record().value("Ano").toString();
            sql.finish();
        }
        sql.next();
    }

    if(strAnoOldCod == "-1"){
        strSql = " INSERT INTO VacacionesPendientes(Ano,"
                 "                                  Dias) VALUES ('" + strAnoCod + "',"
                 "                                                '" + strDiasCod + "');";
    }
    else{


        strSql= "UPDATE VacacionesPendientes SET Ano ='"   + strAnoCod +"', "
                "                                Dias ='"  + strDiasCod + "'  WHERE  Ano ='" + strAnoOldCod + "';";
    }
    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_vacaciones_pendientes");

}

void FuncAux::setIncidencia(DatosIncidencias incidencia){
    QString strFecha    = "-1";
    bool    todoOk      = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_incidencia");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbIncidencias);

    //
    // Si se abre y no da error, abrimos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Comprobamos si existe registro con esa fecha
    //
    strSql = "SELECT *FROM Incidencias";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        if(incidencia.fecha == sql.record().value("Fecha").toString()){
            strFecha = sql.record().value("Fecha").toString();
            sql.finish();
        }
        sql.next();
    }

    if(strFecha == "-1"){
        strSql = " INSERT INTO Incidencias(Fecha,"
                 "                         Hed,"
                 "                         Hen,"
                 "                         Hef,"
                 "                         Voladuras) VALUES ('" + incidencia.fecha + "',"
                 "                                            '" + incidencia.hed + "',"
                 "                                            '" + incidencia.hen + "',"
                 "                                            '" + incidencia.hef + "',"
                 "                                            '" + incidencia.voladuras + "');";
    }
    else{
        strSql= "UPDATE Incidencias SET Fecha ='"     + incidencia.fecha + "', "
                                       "Hed ='"       + incidencia.hed + "', "
                                       "Hen ='"       + incidencia.hen + "', "
                                       "Hef ='"       + incidencia.hef + "', "
                                       "Voladuras ='" + incidencia.voladuras + "'  WHERE  Fecha ='" + strFecha + "';";
    }
    sql.exec(strSql);

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_incidencia");
}

void FuncAux::delIncidencia(QDate qdFecha){

}

void FuncAux::setNomina(QList<DatosNomina> listaNomina){
    QList<QString>  listaDelete;
    QString         strMesDb;
    QString         strAnoDb;
    QString         strAnoCod;
    QString         strMesCod;
    QString         codigoCod;
    QString         claveCod;
    QString         denominacionCod;
    QString         cantidadCod;
    QString         precioCod;
    QString         importeCod;
    QString         strRenumeracionCod;
    QString         strRemuneracionPECod;
    QString         strProrrateoCod;
    QString         strDeduccionesCod;
    QString         strIrpfCod;
    QString         strTipoCCEmpresaCod;
    QString         strTipoATEPEmpresaCod;
    QString         strTipoDesempleoEmpresaCod;
    QString         strTipoFormacionEmpresaCod;
    QString         strTipoFogasaEmpresaCod;
    QString         strTipoMeiEmpresaCod;
    QString         strSumaSalarioBrutoCod;
    QString         strSumaIrpfCod;
    QString         strSumaGastosDeduciblesCod;
    bool            todoOk          = false;
    int             i               = 0;
    QString         strAnoOldCod    = "-1";


    //
    // Codificamos la primera linea
    //
    strAnoCod                   = cifrar(listaNomina[0].strAno);
    strMesCod                   = cifrar(listaNomina[0].strMes);
    strRenumeracionCod          = cifrar(listaNomina[0].strRenumeracion);
    strRemuneracionPECod        = cifrar(listaNomina[0].strRemuneracionPE);
    strProrrateoCod             = cifrar(listaNomina[0].strProrrateo);
    strDeduccionesCod           = cifrar(listaNomina[0].strDeducciones);
    strIrpfCod                  = cifrar(listaNomina[0].strIrpf);
    strTipoCCEmpresaCod         = cifrar(listaNomina[0].strTipoCCEmpresa);
    strTipoATEPEmpresaCod       = cifrar(listaNomina[0].strTipoATEPEmpresa);
    strTipoDesempleoEmpresaCod  = cifrar(listaNomina[0].strTipoDesempleoEmpresa);
    strTipoFormacionEmpresaCod  = cifrar(listaNomina[0].strTipoFormacionEmpresa);
    strTipoFogasaEmpresaCod     = cifrar(listaNomina[0].strTipoFogasaEmpresa);
    strTipoMeiEmpresaCod        = cifrar(listaNomina[0].strTipoMeiEmpresa);
    strSumaSalarioBrutoCod      = cifrar(listaNomina[0].strSumaSalarioBruto);
    strSumaIrpfCod              = cifrar(listaNomina[0].strSumaIrpf);
    strSumaGastosDeduciblesCod  = cifrar(listaNomina[0].strSumaGastosDeducibles);


    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_set_nominas");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbGesNomCas);

    //
    // Si se abre y no da error, abrimos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    //
    // Borramos todos los registros con Mes y Año igual al que vamos a guardar
    //
    strSql ="SELECT *FROM Nominas";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {

        strMesDb = desCifrar(sql.record().value("Mes").toString());
        strAnoDb = desCifrar(sql.record().value("Ano").toString());

        if(strAnoDb == listaNomina[0].strAno && strMesDb == listaNomina[0].strMes){
            strAnoOldCod = sql.record().value("Ano").toString();
            listaDelete.append(strAnoOldCod);
        }


        i++;
        sql.next();
    }
    while (listaDelete.count() > 0) {
        strSql = "DELETE FROM Nominas WHERE Ano='" + listaDelete[0] + "';";
        sql.exec(strSql);
        listaDelete.remove(0);
    }

    //
    // Ahora Insertamos la primera linea de la nueva nomina
    //
    strSql = " INSERT INTO Nominas(Ano,"
             "                     Mes,"
             "                     Remuneracion,"
             "                     RemuneracionPE,"
             "                     Prorrateo,"
             "                     Deducciones,"
             "                     Irpf,"
             "                     TipoCC,"
             "                     TipoATEP,"
             "                     TipoDesempleo,"
             "                     TipoFormacion,"
             "                     TipoFogasa,"
             "                     TipoMei,"
             "                     SumaSalarioBruto,"
             "                     SumaIrpf,"
             "                     SumaGastosDeducibles) VALUES ('" + strAnoCod + "',"
             "                                                   '" + strMesCod + "',"
             "                                                   '" + strRenumeracionCod + "',"
             "                                                   '" + strRemuneracionPECod + "',"
             "                                                   '" + strProrrateoCod + "',"
             "                                                   '" + strDeduccionesCod + "',"
             "                                                   '" + strIrpfCod + "',"
             "                                                   '" + strTipoCCEmpresaCod + "',"
             "                                                   '" + strTipoATEPEmpresaCod + "',"
             "                                                   '" + strTipoDesempleoEmpresaCod + "',"
             "                                                   '" + strTipoFormacionEmpresaCod + "',"
             "                                                   '" + strTipoFogasaEmpresaCod + "',"
             "                                                   '" + strTipoMeiEmpresaCod + "',"
             "                                                   '" + strSumaSalarioBrutoCod + "',"
             "                                                   '" + strSumaIrpfCod + "',"
             "                                                   '" + strSumaGastosDeduciblesCod + "');";

    sql.exec(strSql);

    //
    // Ahora todas las lineas de la nomina
    //
    i = 1;
    while (i < listaNomina.count()) {

        strAnoCod           = cifrar(listaNomina[i].strAno);
        strMesCod           = cifrar(listaNomina[i].strMes);
        codigoCod           = cifrar(listaNomina[i].codigo);
        claveCod            = cifrar(listaNomina[i].clave);
        denominacionCod     = cifrar(listaNomina[i].denominacion);
        cantidadCod         = cifrar(listaNomina[i].cantidad);
        precioCod           = cifrar(listaNomina[i].precio);
        importeCod          = cifrar(listaNomina[i].importe);

        strSql = " INSERT INTO Nominas(Ano,"
                 "                     Mes,"
                 "                     Codigo,"
                 "                     Clave,"
                 "                     Denominacion,"
                 "                     Cantidad,"
                 "                     Precio,"
                 "                     Importe) VALUES ('" + strAnoCod + "',"
                 "                                      '" + strMesCod + "',"
                 "                                      '" + codigoCod + "',"
                 "                                      '" + claveCod + "',"
                 "                                      '" + denominacionCod + "',"
                 "                                      '" + cantidadCod + "',"
                 "                                      '" + precioCod + "',"
                 "                                      '" + importeCod + "');";

        sql.exec(strSql);
        i++;
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_set_nominas");
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

QString FuncAux::getSabados(QString strAno){
    QLocale qLocale;
    QDate   qdFecha;
    QString strFecha;
    int     iAno;
    int     iSabados = 0;

    qdFecha.setDate(strAno.toInt(), 1, 1);
    iAno = qdFecha.year();
    while (qdFecha.year() == iAno) {
        strFecha = qLocale.toString(qdFecha, "dddd ',' dd 'de' MMMM 'de' yyyy");
        strFecha.remove(4, strFecha.length() - 4);
        if(strFecha == "sába"){
            iSabados++;
        }
        qdFecha = qdFecha.addDays(1);
    }

    return QString::number(iSabados);
}

QString FuncAux::getDomingos(QString strAno){
    QLocale qLocale;
    QDate   qdFecha;
    QString strFecha;
    int     iAno;
    int     iDomingos = 0;

    qdFecha.setDate(strAno.toInt(), 1, 1);
    iAno = qdFecha.year();
    while (qdFecha.year() == iAno) {
        strFecha = qLocale.toString(qdFecha, "dddd ',' dd 'de' MMMM 'de' yyyy");
        strFecha.remove(4, strFecha.length() - 4);
        if(strFecha == "domi"){
            iDomingos++;
        }
        qdFecha = qdFecha.addDays(1);
    }

    return QString::number(iDomingos);
}

QString FuncAux::getFestivosNacionales(QString strAno){
    QString strFechaDb;
    QString strAnoDb;
    QString strTipoFestivo;
    int     iFestivos   = 0;
    bool    todoOk      = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_festivos_nacionales");

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

    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDb  = desCifrar(sql.record().value("Fecha").toString());
        strAnoDb    = strFechaDb.remove(0, strFechaDb.length() - 4);
        if(strAno == strAnoDb){
            strTipoFestivo = desCifrar(sql.record().value("TipoFestivo").toString());
            if(strTipoFestivo == "Nacional"){
                iFestivos ++;
            }
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_festivos_nacionales");

    return QString::number(iFestivos);
}

QString FuncAux::getFestivosAutonomicos(QString strAno){
    QString strFechaDb;
    QString strAnoDb;
    QString strTipoFestivo;
    int     iFestivos   = 0;
    bool    todoOk      = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_festivos_autonomicos");

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

    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDb  = desCifrar(sql.record().value("Fecha").toString());
        strAnoDb    = strFechaDb.remove(0, strFechaDb.length() - 4);
        if(strAno == strAnoDb){
            strTipoFestivo = desCifrar(sql.record().value("TipoFestivo").toString());
            if(strTipoFestivo == "Autonómico"){
                iFestivos ++;
            }
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_festivos_autonomicos");

    return QString::number(iFestivos);
}

QString FuncAux::getFestivosLocales(QString strAno){
    QString strFechaDb;
    QString strAnoDb;
    QString strTipoFestivo;
    int     iFestivos   = 0;
    bool    todoOk      = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_festivos_locales");

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

    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDb  = desCifrar(sql.record().value("Fecha").toString());
        strAnoDb    = strFechaDb.remove(0, strFechaDb.length() - 4);
        if(strAno == strAnoDb){
            strTipoFestivo = desCifrar(sql.record().value("TipoFestivo").toString());
            if(strTipoFestivo == "Local"){
                iFestivos ++;
            }
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_festivos_locales");

    return QString::number(iFestivos);
}

QString FuncAux::getFestivosConvenio(QString strAno){
    QString strFechaDb;
    QString strAnoDb;
    QString strTipoFestivo;
    int     iFestivos   = 0;
    bool    todoOk      = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_festivos_convenio");

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

    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()) {
        strFechaDb  = desCifrar(sql.record().value("Fecha").toString());
        strAnoDb    = strFechaDb.remove(0, strFechaDb.length() - 4);
        if(strAno == strAnoDb){
            strTipoFestivo = desCifrar(sql.record().value("TipoFestivo").toString());
            if(strTipoFestivo == "Convenio"){
                iFestivos ++;
            }
        }
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_festivos_convenio");

    return QString::number(iFestivos);
}

double FuncAux::getAcumuladoSalarioBruto(QString strAno, QString strMes){
    QList<FuncAux::DatosNomina>     listaNominas;
    double                          dAcumulado  = 0.0;
    int                             i           = 0;
    int                             iMesDb;
    int                             iMes        = strMesToInt(strMes);

    listaNominas = getAllDatosNominas();

    while (i < listaNominas.count()) {

        iMesDb  = strMesToInt(listaNominas[i].strMes);

        if(listaNominas[i].strAno == strAno && iMesDb < iMes){

            dAcumulado      += (listaNominas[i].strRenumeracion.toDouble() + listaNominas[i].strRemuneracionPE.toDouble());
        }

        i++;
    }


    return dAcumulado;
}

double FuncAux::getAcumuladoIrpf(QString strAno, QString strMes){
    QList<FuncAux::DatosNomina>     listaNominas;
    double                          dAcumulado  = 0.0;
    int                             i           = 0;

    listaNominas = getAllDatosNominas();

    while (i < listaNominas.count()) {

        if(listaNominas[i].strAno == strAno && listaNominas[i].strMes != strMes){

            dAcumulado += (listaNominas[i].strIrpf.toDouble());
        }

        i++;
    }


    return dAcumulado;
}

double FuncAux::getAcumuladoGastosDeducibles(QString strAno, QString strMes){
    QList<FuncAux::DatosNomina>     listaNominas;
    double                          dAcumulado  = 0.0;
    int                             i           = 0;

    listaNominas = getAllDatosNominas();

    while (i < listaNominas.count()) {

        if(listaNominas[i].strAno == strAno && listaNominas[i].strMes != strMes){

            dAcumulado += (listaNominas[i].strDeducciones.toDouble());
        }

        i++;
    }


    return dAcumulado;
}

FuncAux::DatosEmpleado FuncAux::getDatosEmpleado(){
    DatosEmpleado   datos;
    bool            todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_datos_empleado");

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

    strSql = "SELECT *FROM DatosEmpleado";
    sql.exec(strSql);
    sql.first();
    if(sql.isValid()){

        datos.empleado          = desCifrar(sql.record().value("Empleado").toString());
        datos.categoria         = desCifrar(sql.record().value("Categoria").toString());
        datos.ingreso           = desCifrar(sql.record().value("Ingreso").toString());
        datos.nif               = desCifrar(sql.record().value("Nif").toString());
        datos.puesto            = desCifrar(sql.record().value("Puesto").toString());
        datos.numeroAfiliacion  = desCifrar(sql.record().value("NumeroAfiliacion").toString());
        datos.grupoCotizacion   = desCifrar(sql.record().value("GrupoCotizacion").toString());
        datos.codigoOcupacion   = desCifrar(sql.record().value("CodigoOcupacion").toString());
        datos.contrato          = desCifrar(sql.record().value("Contrato").toString());
        datos.finContrato       = desCifrar(sql.record().value("FinContrato").toString());
    }
    else{

        datos.empleado          = "";
        datos.categoria         = "";
        datos.ingreso           = "";
        datos.nif               = "";
        datos.puesto            = "";
        datos.numeroAfiliacion  = "";
        datos.grupoCotizacion   = "";
        datos.codigoOcupacion   = "";
        datos.contrato          = "";
        datos.finContrato       = "";
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_datos_empleado");

    return datos;
}

QList<FuncAux::DatosVacacionesPendientes> FuncAux::getAllVacacionesPendientes(){
    DatosVacacionesPendientes           dato;
    QList<DatosVacacionesPendientes>    listaVacacionesPendientes;
    bool                                todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_vacaciones_pendientes");

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

    strSql = "SELECT *FROM VacacionesPendientes";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()){
        dato.strAno     = desCifrar(sql.record().value("Ano").toString());
        dato.strDias    = desCifrar(sql.record().value("Dias").toString());
        listaVacacionesPendientes.append(dato);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_vacaciones_pendientes");

    return listaVacacionesPendientes;
}

QList<FuncAux::DatosVacaciones> FuncAux::getAllVacaciones(){
    QList<DatosVacaciones>  listaVacaciones;
    DatosVacaciones         dato;
    bool                    todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_vacaciones");

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

    strSql = "SELECT *FROM Vacaciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()){
        dato.strAno     = desCifrar(sql.record().value("Ano").toString());
        dato.qdFecha0   = fechaCortaToDate(desCifrar(sql.record().value("FechaInicio").toString()));
        dato.qdFecha1   = fechaCortaToDate(desCifrar(sql.record().value("FechaFin").toString()));
        listaVacaciones.append(dato);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_vacaciones");

    return listaVacaciones;
}

QList<FuncAux::DatosFestivos> FuncAux::getAllFestivos(){
    QList<FuncAux::DatosFestivos>   listaFestivos;
    FuncAux::DatosFestivos          dato;
    bool                            todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_Festivos");

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

    strSql = "SELECT *FROM Festivos";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()){

        dato.qdFecha        = FuncAux().fechaCortaToDate(FuncAux().desCifrar(sql.record().value("Fecha").toString()));
        dato.strTipoFestivo = FuncAux().desCifrar(sql.record().value("TipoFestivo").toString());
        listaFestivos.append(dato);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_Festivos");

    return listaFestivos;
}

QList<FuncAux::DatosNomina> FuncAux::getAllDatosNominas(){
    QList<FuncAux::DatosNomina>  listaNominas;
    FuncAux::DatosNomina         dato;
    bool                         todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_all_nominas");

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

    strSql = "SELECT *FROM Nominas";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()){

        dato.codigo                     = FuncAux::desCifrar(sql.record().value("Codigo").toString());
        dato.clave                      = FuncAux::desCifrar(sql.record().value("Clave").toString());
        dato.denominacion               = FuncAux::desCifrar(sql.record().value("Denominacion").toString());
        dato.cantidad                   = FuncAux::desCifrar(sql.record().value("Cantidad").toString());
        dato.precio                     = FuncAux::desCifrar(sql.record().value("Precio").toString());
        dato.importe                    = FuncAux::desCifrar(sql.record().value("Importe").toString());
        dato.strAno                     = FuncAux::desCifrar(sql.record().value("Ano").toString());
        dato.strMes                     = FuncAux::desCifrar(sql.record().value("Mes").toString());
        dato.strRenumeracion            = FuncAux::desCifrar(sql.record().value("Remuneracion").toString());
        dato.strRemuneracionPE          = FuncAux::desCifrar(sql.record().value("RemuneracionPE").toString());
        dato.strProrrateo               = FuncAux::desCifrar(sql.record().value("Prorrateo").toString());
        dato.strDeducciones             = FuncAux::desCifrar(sql.record().value("Deducciones").toString());
        dato.strIrpf                    = FuncAux::desCifrar(sql.record().value("Irpf").toString());
        dato.strTipoCCEmpresa           = FuncAux::desCifrar(sql.record().value("TipoCC").toString());
        dato.strTipoATEPEmpresa         = FuncAux::desCifrar(sql.record().value("TipoATEP").toString());
        dato.strTipoDesempleoEmpresa    = FuncAux::desCifrar(sql.record().value("TipoDesempleo").toString());
        dato.strTipoFormacionEmpresa    = FuncAux::desCifrar(sql.record().value("TipoFormacion").toString());
        dato.strTipoFogasaEmpresa       = FuncAux::desCifrar(sql.record().value("TipoFogasa").toString());
        dato.strTipoMeiEmpresa          = FuncAux::desCifrar(sql.record().value("TipoMei").toString());
        dato.strSumaSalarioBruto        = FuncAux::desCifrar(sql.record().value("SumaSalarioBruto").toString());
        dato.strSumaIrpf                = FuncAux::desCifrar(sql.record().value("SumaIrpf").toString());
        dato.strSumaGastosDeducibles    = FuncAux::desCifrar(sql.record().value("SumaGastosDeducibles").toString());

        listaNominas.append(dato);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_all_nominas");

    return listaNominas;

}

QList<FuncAux::DatosRetribuciones> FuncAux::getAllRetribuciones(){
    QList<FuncAux::DatosRetribuciones>  listaRetribuciones;
    FuncAux::DatosRetribuciones         dato;
    bool                                todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_retribuciones");

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

    strSql = "SELECT *FROM Retribuciones";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()){

        dato.codigo         = FuncAux().desCifrar(sql.record().value("Codigo").toString());
        dato.clave          = FuncAux().desCifrar(sql.record().value("Clave").toString());
        dato.denominacion   = FuncAux().desCifrar(sql.record().value("Denominacion").toString());
        dato.cuantia        = FuncAux().desCifrar(sql.record().value("Cuantia").toString());

        listaRetribuciones.append(dato);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_retribuciones");

    return listaRetribuciones;
}

QList<FuncAux::DatosIncidencias> FuncAux::getAllIncidencias(){
    QList<FuncAux::DatosIncidencias>    listaIncidencias;
    FuncAux::DatosIncidencias           dato;
    bool                                todoOk = false;

    //
    // Creo la conexion con la BD
    //
    dbSql = QSqlDatabase::addDatabase("QSQLITE", "con_get_all_incidencias");

    //
    // Establezco la ruta de la BD
    //
    dbSql.setDatabaseName(rutaDbIncidencias);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todoOk = dbSql.open();
    if(todoOk){
        sql = QSqlQuery(dbSql);
    }

    strSql = "SELECT *FROM Incidencias";
    sql.exec(strSql);
    sql.first();
    while (sql.isValid()){

        dato.fecha      = sql.record().value("Fecha").toString();
        dato.hed        = sql.record().value("Hed").toString();
        dato.hen        = sql.record().value("Hen").toString();
        dato.hef        = sql.record().value("Hef").toString();
        dato.voladuras  = sql.record().value("Voladuras").toString();

        listaIncidencias.append(dato);
        sql.next();
    }

    //
    // Cerramos la BD y la Conexion
    //
    dbSql.close();
    dbSql = QSqlDatabase();
    dbSql.removeDatabase("con_get_all_incidencias");

    return listaIncidencias;
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
    DatosIncidencias datosIncidencias;

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
    DatosIncidencias incidencias;

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
    DatosIncidencias incidencias;

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

QDate FuncAux::fechaLargaToDate(QString strFechaLarga){
    QDate   qdFecha;
    QString strDia;
    QString strMes;
    QString strAno;
    int     i;
    QString str;

    //
    // Obtenemos el dia
    //
    str = strFechaLarga;
    i   = 0;
    while (i < str.length()) {
        if(str[i] == ','){
            str.remove(0, i +2);
            i = str.length();
        }
        i++;
    }
    strDia  = str;
    strDia  = strDia.remove(2, str.length() -1);

    //
    // Ahora el año
    //
    strAno = str;
    strAno = strAno.remove(0, str.length() -4);

    //
    // Ahora el mes
    //
    str     = str.remove(0, 6);
    str     = str.remove(str.length() -8, 8);
    strMes  = str;

    //
    // Establecemos la fecha
    //
    qdFecha.setDate(strAno.toInt(), strMesToInt(strMes), strDia.toInt());

    return qdFecha;
}

QString FuncAux::dateToFechaCorta(QDate qdFecha){
    QString strFecha;
    QLocale qLocale;

    strFecha = qLocale.toString(qdFecha, "dd/MM/yyyy");
    return strFecha;
}

QString FuncAux::dateToFechaLarga(QDate qdFecha){
    QString strFecha;
    QLocale qLocale;

    strFecha = qLocale.toString(qdFecha, "dddd ',' dd 'de' MMMM 'de' yyyy");
    return strFecha;
}

int FuncAux::strMesToInt(QString strMes){
    int iMes = -1;

    strMes = strMes.toUpper();

    if(strMes == "ENERO"){iMes = 1;}
    if(strMes == "FEBRERO"){iMes = 2;}
    if(strMes == "MARZO"){iMes = 3;}
    if(strMes == "ABRIL"){iMes = 4;}
    if(strMes == "MAYO"){iMes = 5;}
    if(strMes == "JUNIO"){iMes = 6;}
    if(strMes == "JULIO"){iMes = 7;}
    if(strMes == "AGOSTO"){iMes = 8;}
    if(strMes == "SEPTIEMBRE"){iMes = 9;}
    if(strMes == "OCTUBRE"){iMes = 10;}
    if(strMes == "NOVIEMBRE"){iMes = 11;}
    if(strMes == "DICIEMBRE"){iMes = 12;}

    return iMes;
}

bool FuncAux::isFormatoFecha(QString strFecha){
    bool        isFecha = false;
    QString     str;
    QString     strDia;
    QString     strMes;
    QString     strAno;
    int         iDia;
    int         iMes;
    int         iAno;
    QDate       qdFecha;

    if(strFecha[2] != '/' || strFecha[5] != '/'){
        return false;
    }
    else{
        str     = strFecha;
        strDia  = str.remove(2, str.length() - 2);
        iDia    = strDia.toInt();

        str     = strFecha;
        str     = str.remove(0, 3);
        strMes  = str.remove(2, str.length() -2);
        iMes    = strMes.toInt();

        str     = strFecha;
        strAno  = str.remove(0, str.length() - 4);
        iAno    = strAno.toInt();

        //
        // Establecemos la fecha y vemos si es no null
        //
        qdFecha.setDate(iAno, iMes, iDia);
        if(!qdFecha.isNull()){
            isFecha = true;
        }
    }

    return isFecha;
}

bool FuncAux::isFestivo(QDate qdFecha){
    QList<FuncAux::DatosFestivos>   listaFestivos;
    bool                            isFestivo   = false;
    int                             i           = 0;

    listaFestivos = FuncAux().getAllFestivos();
    while (i < listaFestivos.count()) {
        if(listaFestivos[i].qdFecha == qdFecha){
            isFestivo = true;
            i = listaFestivos.count();
        }
        i++;
    }

    return isFestivo;
}

bool FuncAux::isLaborable(QDate qdFecha){
    bool    isLaborable = true;
    QString str;

    str = dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() -4);

    if(str == "sába" || str == "domi" || isFestivo(qdFecha) == true ){
        isLaborable = false;
    }


    return isLaborable;
}

bool FuncAux::isVacaciones(QDate qdFecha){
    QList<FuncAux::DatosVacaciones>     listaVacaciones;
    bool                                isVacaciones    = false;
    int                                 i               = 0;
    QString                             strAno;

    strAno          = QString::number(qdFecha.year());
    listaVacaciones = FuncAux().getAllVacaciones();

    while (i < listaVacaciones.count()) {
        if(listaVacaciones[i].strAno == strAno){
            if(listaVacaciones[i].qdFecha0 < qdFecha && qdFecha < listaVacaciones[i].qdFecha1){
                isVacaciones = true;
                i = listaVacaciones.count();
            }
        }
        i++;
    }

    return isVacaciones;
}
