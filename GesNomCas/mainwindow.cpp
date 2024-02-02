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

    inicio();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inicio(){
    QSplashScreen   *splash = new QSplashScreen();
    QProgressBar    *progress = new QProgressBar(splash);
    QEventLoop      loop;

    //
    //Iniciamos el splash
    //
    iniciarSplash(splash, progress);

    //
    //Comprobamos si existe data
    //
    progress->setValue(34);
    progress->setFormat("Comprobando /data/...");
    QTimer::singleShot(1200, &loop, SLOT(quit()));
    loop.exec();
    if(!existeData()){
        crearData();
    }

    //
    //Comprobamos si existe DbGesNomCas
    //
    progress->setValue(66);
    progress->setFormat("Comprobando /data/DbGesNomCas...");
    QTimer::singleShot(800, &loop, SLOT(quit()));
    loop.exec();
    if(!existeDbGesNomCas()){
        crearDb();
    }

    //
    //Cerramos el splash
    //
    progress->setValue(100);
    progress->setFormat("Cargando datos...");
    QTimer::singleShot(600, &loop, SLOT(quit()));
    loop.exec();
    cerrarSplash(splash);


}

void MainWindow::iniciarSplash(QSplashScreen *splash, QProgressBar *progress){
    QImage          img;
    QPixmap         pix_map;
    QEventLoop      loop;

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

    //
    // Iniciamos el progress
    //
    progress->setValue(17);
    progress->setFormat("Iniciando...");
    QTimer::singleShot(750, &loop, SLOT(quit()));
    loop.exec();
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

void MainWindow::cerrarSplash(QSplashScreen *splash){

    //
    // Cerramos el splash y cargamos MainWindow
    //
    splash->finish(this);
}
