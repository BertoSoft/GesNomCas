#include "mainwindow.h"
#include <QApplication>

#include "funcaux.h"

int main(int argc, char *argv[]){
    QApplication    a(argc, argv);
    MainWindow      w;

    w.setWindowTitle(FuncAux().getAppName());
    w.setWindowIcon(QIcon(":/icono.png"));
    w.showMaximized();
    w.show();

    return a.exec();
}

