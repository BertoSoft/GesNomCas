#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    MainWindow      w;

    QImage          img;
    QPixmap         pixMap;
    QSplashScreen   splash;

    //
    // Cargamos la imagen
    //
    img.load(":/logo1.png");
    img.scaled(400, 300, Qt::KeepAspectRatio);

    pixMap = QPixmap::fromImage(img);

    //
    // Mostramos el splash
    //
    splash.setPixmap(pixMap);
    splash.show();
    splash.showMessage("Espere...", Qt::AlignBottom);

    //
    // Cerramos el splash y cargamos MainWindow
    //
    splash.finish(&w);
    w.show();

    return a.exec();
}
