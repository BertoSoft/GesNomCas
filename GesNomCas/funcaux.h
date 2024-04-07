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
    QString         rutaDbIncidencias;
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

    struct DatosEmpleado{
        QString empleado;
        QString categoria;
        QString ingreso;
        QString nif;
        QString puesto;
        QString numeroAfiliacion;
        QString grupoCotizacion;
        QString codigoOcupacion;
        QString contrato;
        QString finContrato;
    };

    struct DatosRetribuciones{
        QString codigo;
        QString clave;
        QString denominacion;
        QString cuantia;

    };

    struct DatosNomina{
        QString strAno;
        QString strMes;
        QString codigo;
        QString clave;
        QString denominacion;
        QString cantidad;
        QString precio;
        QString importe;
        QString strRenumeracion;
        QString strRemuneracionPE;
        QString strProrrateo;
        QString strDeducciones;
        QString strIrpf;
        QString strTipoCCEmpresa;
        QString strTipoATEPEmpresa;
        QString strTipoDesempleoEmpresa;
        QString strTipoFormacionEmpresa;
        QString strTipoFogasaEmpresa;
        QString strTipoMeiEmpresa;
        QString strSumaSalarioBruto;
        QString strSumaIrpf;
        QString strSumaGastosDeducibles;
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
    double                              getAcumuladoSalarioBruto(QString, QString);
    double                              getAcumuladoIrpf(QString, QString);
    double                              getAcumuladoGastosDeducibles(QString, QString);
    DatosEmpleado                       getDatosEmpleado();
    QList<DatosNomina>                  getAllDatosNominas();
    QList<DatosVacacionesPendientes>    getAllVacacionesPendientes();
    QList<DatosVacaciones>              getAllVacaciones();
    QList<DatosFestivos>                getAllFestivos();
    QList<DatosRetribuciones>           getAllRetribuciones();
    QList<DatosIncidencias>             getAllIncidencias();
    void                                setInicioSesion(QString, QString);
    void                                setCierreSesion(QString, QString);
    void                                setUsuario(QString usuario, QString passwd);
    void                                setVacacionesPendientes(DatosVacacionesPendientes dato);
    void                                setNomina(QList<DatosNomina>);
    void                                setIncidencia(FuncAux::DatosIncidencias);
    void                                delIncidencia(QDate);
    QString                             dateToFechaCorta(QDate);
    QString                             dateToFechaLarga(QDate);
    QDate                               fechaCortaToDate(QString);
    QDate                               fechaLargaToDate(QString);
    int                                 strMesToInt(QString);
    bool                                isFormatoFecha(QString strFecha);
    bool                                isFestivo(QDate);
    bool                                isLaborable(QDate);
    bool                                isVacaciones(QDate);


};

#endif // FUNCAUX_H
