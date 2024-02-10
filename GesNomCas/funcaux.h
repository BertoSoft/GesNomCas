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
    QString         ruta_db_GesNomCas;
    QString         str_sql;
    QSqlDatabase    db_sql;
    QSqlQuery       sql;

    //
    // Funciones Publicas
    //
    QString cifrar(QString strTextoPlano);
    QString desCifrar(QString strTextoCod);
    bool crearDb();
    bool existeUsuario();
    void setInicioSesion(QString, QString);
    void setCierreSesion(QString, QString);
    void setUsuario(QString usuario, QString passwd);


};

#endif // FUNCAUX_H
