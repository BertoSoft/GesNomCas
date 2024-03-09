#ifndef FUNCAUX_H
#define FUNCAUX_H

#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>

class FuncAux
{
public:
    FuncAux();
    ~FuncAux();

    //
    // Variables Globales
    //
    QString         rutaDbGesNomCas;
    QString         strSql;
    QSqlDatabase    dbSql;
    QSqlQuery       sql;

    //
    // Structuras
    //
    struct Incidencias
    {
        QString fecha;
        QString hed;
        QString hen;
        QString hef;
        QString voladuras;
    };

    //
    // Funciones Publicas
    //
    QString getAppName();
    QString getRutaDb();
    QString cifrar(QString strTextoPlano);
    QString desCifrar(QString strTextoCod);
    bool    crearDb();
    bool    existeUsuario();
    void    setInicioSesion(QString, QString);
    void    setCierreSesion(QString, QString);
    void    setUsuario(QString usuario, QString passwd);
    bool    esFormatoDatos(QString);
    bool    esFormatoIncidencias(QString);
    QString primerRegistroDatos(QString);
    QString ultimoRegistroDatos(QString);
    QString primerRegistroIncidencias(QString);
    QString ultimoRegistroIncidencias(QString);
    QString getUser();
    QString getPasswd();
    QString getSabados(QString);
    QString getDomingos(QString);
    QString getFestivosNacionales(QString);
    QString getFestivosLocales(QString);
    QString getFestivosAutonomicos(QString);
    QString getFestivosConvenio(QString);
    QString dateToFechaCorta(QDate);
    QString dateToFechaLarga(QDate);
    QDate   fechaCortaToDate(QString);
    bool    isFormatoFecha(QString strFecha);


};

#endif // FUNCAUX_H
