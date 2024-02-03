#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QSplashScreen>
#include <QPixmap>
#include <QProgressBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    initUi();
    initLogin();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi(){
    QSplashScreen   *splash = new QSplashScreen();
    QProgressBar    *progress = new QProgressBar(splash);
    QEventLoop      loop;
    int             i;

    //
    //Iniciamos el splash
    //
    initSplash(splash, progress);

    //
    // Comprobamos si exise Data
    //
    progress->setFormat("Comprobando directorios...");
    i = 17;
    while (i<34) {
        progress->setValue(i);
        QTimer::singleShot(20, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }
    if(!existeData()){
        crearData();
    }

    //
    // Comprobando datos
    //
    progress->setFormat("Comprobando datos...");
    i = 34;
    while (i<66) {
        progress->setValue(i);
        QTimer::singleShot(15, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }
    if(!existeDbGesNomCas()){
        crearDb();
    }

    //
    // cerrando el splash
    //
    progress->setFormat("Cargando...");
    i = 66;
    while (i<100) {
        progress->setValue(i);
        QTimer::singleShot(10, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }
    splash->finish(this);


}

void MainWindow::initLogin(){

}

void MainWindow::initSplash(QSplashScreen *splash, QProgressBar *progress){
    QImage          img;
    QPixmap         pix_map;
    QEventLoop      loop;

    const int       ancho = 400;
    const int       alto = 300;

    //
    // Cargamos la imagen
    //
    img.load(":/logo.png");
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

    //
    // Iniciamos el progress
    //
    progress->setFormat("Iniciando...");
    int i = 0;
    while (i<17) {
        progress->setValue(i);
        QTimer::singleShot(15, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }

}

bool MainWindow::existeData(){

    return true;
}

void MainWindow::crearData(){

}

bool MainWindow::existeDbGesNomCas(){

    return true;
}

void MainWindow::crearDb(){

}


