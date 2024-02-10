#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "funcaux.h"
#include "login.h"
#include "registro.h"

#include <QTimer>
#include <QSplashScreen>
#include <QPixmap>
#include <QProgressBar>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QTime>
#include <QLocale>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //
    // Instalamos un filtro de eventos en la app
    //
    qApp->installEventFilter(this);
    this->installEventFilter(this);

    //
    // Desarrollamos la app
    //
    initReloj();
    initUi();
    initLogin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev){

    //
    // Si pulsamos la x de salir, vamos a salir
    //
    if(obj == this && ev->type() == QEvent::Close){
        salir();
    }

    return QObject::eventFilter(obj, ev);
}

void MainWindow::initUi(){
    QSplashScreen   *splash     = new QSplashScreen();
    QProgressBar    *progress   = new QProgressBar(splash);
    QEventLoop      loop;
    int             i;
    QString         errorMsg   = "";
    bool            existeDb    = FuncAux().crearDb();

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
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }
    if(!existeData()){
        errorMsg = " Error al crear " + qApp->applicationDirPath() + "/Data";
    }

    //
    // Comprobando datos
    //
    progress->setFormat("Comprobando datos...");
    i = 34;
    while (i<66) {
        progress->setValue(i);
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }
    if(!existeDb){
        errorMsg = " Error al crear la base de datos";
    }

    //
    // cerrando el splash
    //
    progress->setFormat("Cargando...");
    i = 66;
    while (i<100) {
        progress->setValue(i);
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }
    splash->finish(this);

    //
    // Iniciando la barra de stado
    //
    initBarraEstado();

}

void MainWindow::initReloj(){

    //
    // Hacemos que cada segundo refresque la hora
    //
    QTimer *qtReloj = new QTimer();
    connect( qtReloj, &QTimer::timeout, [this](){refrescaReloj();} );
    qtReloj->start(1000);
}

void MainWindow::initBarraEstado(){


    //
    // Establezco la barra de estado
    //
    lblTexto->setStyleSheet("color: blue; background-color: lightgray; font-size: 11pt; font-weight: bold");
    lblFecha->setStyleSheet("color: blue; background-color: lightgray; font-size: 11pt; font-weight: bold");
    lblHora->setStyleSheet("color: blue; background-color: lightgray; font-size: 11pt; font-weight: bold");

    lblHora->setFrameShape(QFrame::Shape::WinPanel);
    lblFecha->setFrameShape(QFrame::Shape::WinPanel);
    lblTexto->setFrameShape(QFrame::Shape::WinPanel);

    lblHora->setFrameShadow(QFrame::Shadow::Sunken);
    lblFecha->setFrameShadow(QFrame::Shadow::Sunken);
    lblTexto->setFrameShadow(QFrame::Shadow::Sunken);

    ui->statusbar->addWidget(lblTexto, 10);
    ui->statusbar->addWidget(lblFecha, 3);
    ui->statusbar->addWidget(lblHora, 1);

    lblTexto->setText(nombrePrograma);
    refrescaReloj();

}

void MainWindow::initLogin(){
    //
    // Comprobamos si existe algun usuario
    //
    if(FuncAux().existeUsuario()){
        toLogin();
    }
    else{
        toRegistro();
    }
}

void MainWindow::toLogin(){
    Login *pLogin = new Login(this);

    pLogin->setWindowModality(Qt::ApplicationModal);
    pLogin->setWindowFlag(Qt::FramelessWindowHint);
    pLogin->setWindowTitle(nombrePrograma);
    pLogin->nombrePrograma = nombrePrograma;
    pLogin->exec();

    delete pLogin;
}

void MainWindow::toRegistro(){
    Registro *pRegistro = new Registro(this);

    pRegistro->setWindowModality(Qt::ApplicationModal);
    pRegistro->setWindowFlag(Qt::FramelessWindowHint);
    pRegistro->setWindowTitle(nombrePrograma);
    pRegistro->nombrePrograma = nombrePrograma;
    pRegistro->exec();

    delete pRegistro;
}

void MainWindow::initSplash(QSplashScreen *splash, QProgressBar *progress){
    QImage          img;
    QImage          imgScaled;
    QPixmap         pixMap;
    QEventLoop      loop;

    const int       ancho = 400;
    const int       alto = 300;

    //
    // Cargamos la imagen
    //
    img.load(":/logo.png");
    imgScaled = img.scaled(ancho, alto, Qt::KeepAspectRatio);
    pixMap = QPixmap::fromImage(img);

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
    splash->setPixmap(pixMap);
    splash->show();

    //
    // Iniciamos el progress
    //
    progress->setFormat("Iniciando...");
    int i = 0;
    while (i<17) {
        progress->setValue(i);
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i++;
    }

}

bool MainWindow::existeData(){
    QString     rutaData;
    QDir        dirData;
    bool        todoOk = true;

    //
    // Obtenemos la ruta del directorio Data y si no existe lo creamos
    //
    rutaData = qApp->applicationDirPath() + "/Data";
    dirData.setPath(rutaData);
    if(!dirData.exists()){
        todoOk = dirData.mkdir(rutaData);
    }

    return todoOk;
}

bool existeDb(){
    QFile   fileDb;
    QString rutaDb;
    bool    existe = false;

    rutaDb = qApp->applicationDirPath() + "/Data/GesNomCas.db";
    fileDb.setFileName(rutaDb);
    if(!fileDb.exists()){
        existe = FuncAux().crearDb();
    }
    return existe;
}

void MainWindow::refrescaReloj(){
    QLocale locale;
    QDate   fecha   = QDate::currentDate();
    QTime   hora    = QTime::currentTime();

    //
    // Rellenamos fecha y hora
    //
    lblFecha->setText(locale.toString(fecha, "dddd ',' dd 'de' MMMM 'de' yyyy"));
    lblHora->setText(hora.toString("hh:mm:ss"));
}

void MainWindow::salir(){
    QString fecha   = QDate::currentDate().toString("dd/MM/yyyy");
    QString hora    = QTime::currentTime().toString("hh:mm:ss");

    FuncAux().setCierreSesion(fecha, hora);
    exit(0);
}

void MainWindow::on_actionSalir_triggered(){

    salir();
}

void MainWindow::on_actionImportar_Archivo_de_Datos_triggered(){
    QString rutaArchivoOrigen;
    QString rutaArchivoDestino;
    QString rutaArchivoOld;
    QString rutaDescargas;
    QFile   fileDestino;

    rutaDescargas       = QDir::homePath() + "/Descargas";
    rutaArchivoOrigen   = QFileDialog::getOpenFileName(this, nombrePrograma, rutaDescargas);
    rutaArchivoDestino  = qApp->applicationDirPath() + "/Data/GesNomCas.db";
    rutaArchivoOld      = qApp->applicationDirPath() + "/Data/GesNomCas.old";

    fileDestino.setFileName(rutaArchivoDestino);

    //
    // Si ya existe el archivo destino, lo renombramos
    //
    if(fileDestino.exists()){
        fileDestino.rename(rutaArchivoOld);
    }

    //
    // Copiamos el fichero
    //
    QFile::copy(rutaArchivoOrigen, rutaArchivoDestino);

}

