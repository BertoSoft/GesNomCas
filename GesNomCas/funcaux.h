#ifndef FUNCAUX_H
#define FUNCAUX_H

#include <QString>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    // Funciones Publicas
    //
    QString cifrar(QString strTextoPlano);
    QString desCifrar(QString strTextoCod);
    bool    crearDb();
    bool    existeUsuario();
    void    setInicioSesion(QString, QString);
    void    setCierreSesion(QString, QString);
    void    setUsuario(QString usuario, QString passwd);
    QString getUser();
    QString getPasswd();


};

#endif // FUNCAUX_H
