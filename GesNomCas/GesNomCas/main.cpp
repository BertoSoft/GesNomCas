#include "mainwindow.h"
#include <QApplication>

const char* nombre_programa = "GesNomCas V 1.0";

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    MainWindow      w;

    w.setWindowTitle(nombre_programa);
    w.setWindowIcon(QIcon(":/icono.png"));
    w.showMaximized();
    w.show();

    return a.exec();
}

