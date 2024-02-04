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
    bool existeUsuario();
};

#endif // FUNCAUX_H
