#ifndef FUNCAUX_H
#define FUNCAUX_H

#include <QString>
#include <QApplication>

class FuncAux
{
public:
    FuncAux();

    //
    // Variables Globales
    //
    QString     ruta_db_GesNomCas;
    QString     str_sql;

    //
    // Funciones Publicas
    //
    QString cifrar(QString strTextoPlano);
    QString desCifrar(QString strTextoCod);
    bool existeUsuario();
    void setInicioSesion();
    void setCierreSesion();
    void setUsuario(QString usuario, QString passwd);
};

#endif // FUNCAUX_H
