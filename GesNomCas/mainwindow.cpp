#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QSplashScreen>
#include <QPixmap>
#include <QProgressBar>
#include <QTimer>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    QString         error_msg = "";

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
        error_msg = " Error al crear " + qApp->applicationDirPath() + "/Data";
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
    if(!existeDb()){
        error_msg = " Error al crear la base de datos";
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

    //
    // Iniciando la barra de stado
    //
    initBarraEstado();

}

void MainWindow::initBarraEstado(){

}

void MainWindow::initLogin(){

}

void MainWindow::initSplash(QSplashScreen *splash, QProgressBar *progress){
    QImage          img;
    QImage          img_scaled;
    QPixmap         pix_map;
    QEventLoop      loop;

    const int       ancho = 400;
    const int       alto = 300;

    //
    // Cargamos la imagen
    //
    img.load(":/logo.png");
    img_scaled = img.scaled(ancho, alto, Qt::KeepAspectRatio);
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
    QString     ruta_data;
    QDir        dir_data;
    bool        todo_ok = true;

    //
    // Obtenemos la ruta del directorio Data y si no existe lo creamos
    //
    ruta_data = qApp->applicationDirPath() + "/Data";
    dir_data.setPath(ruta_data);
    if(!dir_data.exists()){
        todo_ok = dir_data.mkdir(ruta_data);
    }

    return todo_ok;
}

bool MainWindow::existeDb(){
    QString     ruta_data;
    QString     ruta_db;
    QFile       file_db;
    bool        todo_ok = true;

    //
    // Si no existe la base de datos la Creamos
    //
    ruta_data = qApp->applicationDirPath() + "/Data";
    ruta_db = ruta_data + "/GesNomCas.db";
    file_db.setFileName(ruta_db);
    if(!file_db.exists()){
        todo_ok = crearDb(ruta_db);
    }

    return todo_ok;
}

bool MainWindow::crearDb(QString ruta_db){
    QSqlDatabase    db_sql;
    QSqlQuery       query_sql;
    QString         str_sql;
    bool            todo_ok = true;

    //
    // Creo la conexion con la BD
    //
    db_sql = QSqlDatabase::addDatabase("QSQLITE", "conecta_sql");

    //
    // Establezco la ruta de la BD
    //
    db_sql.setDatabaseName(ruta_db);

    //
    // Si se abre y no da error, creamos la Base de Datos
    //
    todo_ok = db_sql.open();
    if(todo_ok){
        query_sql = QSqlQuery(db_sql);
        str_sql = "CREATE TABLE if not exists RegistroSesiones(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Usuario TEXT, "
                  "                                                                                 FechaInicio TEXT,"
                  "                                                                                 HoraInicio TEXT,"
                  "                                                                                 FechaCierre TEXT,"
                  "                                                                                 HoraCierre TEXT);";
        query_sql.exec(str_sql);

        str_sql = "CREATE TABLE if not exists Usuario(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Usuario TEXT, "
                  "                                                                          Passwd TEXT);";
        query_sql.exec(str_sql);

        //
        // Cerramos la BD y la Conexion
        //
        db_sql.close();
        db_sql.removeDatabase("conecta_sql");
    }

    return todo_ok;
}


