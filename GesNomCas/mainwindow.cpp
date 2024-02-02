#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QSplashScreen>
#include <QPixmap>
#include <QProgressBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inicio(){
    QSplashScreen   *splash = new QSplashScreen();
    QProgressBar *progress = new QProgressBar(splash);

    iniciarSplash(splash, progress);

    //
    // Establecemos una espera para la carga del progress bar
    //
    progress->setValue(17);
    progress->setFormat("Probando texto");
    QEventLoop loop;
    QTimer::singleShot(300, &loop, SLOT(quit()));
    loop.exec();

    progress->setValue(38);
    QTimer::singleShot(300, &loop, SLOT(quit()));
    loop.exec();

    progress->setValue(62);
    QTimer::singleShot(150, &loop, SLOT(quit()));
    loop.exec();

    progress->setValue(79);
    QTimer::singleShot(200, &loop, SLOT(quit()));
    loop.exec();

    progress->setValue(100);


    cerrarSplash(splash);


}

void MainWindow::iniciarSplash(QSplashScreen *splash, QProgressBar *progress){
    QImage          img;
    QPixmap         pix_map;

    const int       ancho = 400;
    const int       alto = 300;

    //
    // Cargamos la imagen
    //
    img.load(":/logo2.png");
    img.scaled(ancho, alto, Qt::KeepAspectRatio);
    pix_map = QPixmap::fromImage(img);

    //
    // Creamos el progressBar
    //
    //progress = new QProgressBar(splash);
    progress->setRange(0, 100);
    progress->setGeometry(10, alto - 25, ancho -20, 20);
    progress->show();

    //
    // Mostramos el splash
    //
    splash->setPixmap(pix_map);
    splash->show();

}


void MainWindow::cerrarSplash(QSplashScreen *splash){

    //
    // Cerramos el splash y cargamos MainWindow
    //
    splash->finish(this);
}
