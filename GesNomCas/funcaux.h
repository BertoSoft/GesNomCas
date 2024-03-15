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
    struct DatosIncidencias{
        QString fecha;
        QString hed;
        QString hen;
        QString hef;
        QString voladuras;
    };

    struct DatosVacacionesPendientes{
        QString strAno;
        QString strDias;
    };

    struct DatosFestivos{
        QDate       qdFecha;
        QString     strTipoFestivo;
    };

    struct DatosVacaciones{
        QString strAno;
        QDate   qdFecha0;
        QDate   qdFecha1;
    };

    //
    // Funciones Publicas
    //
    QString                             cifrar(QString strTextoPlano);
    QString                             desCifrar(QString strTextoCod);
    bool                                crearDb();
    bool                                existeUsuario();
    bool                                esFormatoDatos(QString);
    bool                                esFormatoIncidencias(QString);
    QString                             primerRegistroDatos(QString);
    QString                             ultimoRegistroDatos(QString);
    QString                             primerRegistroIncidencias(QString);
    QString                             ultimoRegistroIncidencias(QString);
    QString                             getAppName();
    QString                             getRutaDb();
    QString                             getUser();
    QString                             getPasswd();
    QString                             getSabados(QString);
    QString                             getDomingos(QString);
    QString                             getFestivosNacionales(QString);
    QString                             getFestivosLocales(QString);
    QString                             getFestivosAutonomicos(QString);
    QString                             getFestivosConvenio(QString);
    QList<DatosVacacionesPendientes>    getAllVacacionesPendientes();
    QList<DatosVacaciones>              getAllVacaciones();
    QList<DatosFestivos>                getAllFestivos();
    void                                setInicioSesion(QString, QString);
    void                                setCierreSesion(QString, QString);
    void                                setUsuario(QString usuario, QString passwd);
    void                                setVacacionesPendientes(DatosVacacionesPendientes dato);
    QString                             dateToFechaCorta(QDate);
    QString                             dateToFechaLarga(QDate);
    QDate                               fechaCortaToDate(QString);
    bool                                isFormatoFecha(QString strFecha);
    bool                                isFestivo(QDate);


};

#endif // FUNCAUX_H
