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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QTime>
#include <QLocale>

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
    initUi();
    initLogin();

    //
    // Hacemos que cada segundo refresque la hora
    //
    QTimer *qtReloj = new QTimer();
    connect( qtReloj, &QTimer::timeout, [this](){refrescaReloj();} );
    qtReloj->start(1000);

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
        QTimer::singleShot(1, &loop, SLOT(quit()));
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
        QTimer::singleShot(1, &loop, SLOT(quit()));
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

    lblTexto->setText(nombre_programa);
    refrescaReloj();

}

void MainWindow::initLogin(){
    FuncAux *pFuncAux = new FuncAux();
    //
    // Comprobamos si existe algun usuario
    //
    if(pFuncAux->existeUsuario()){
        toLogin();
    }
    else{
        toRegistro();
    }

    delete pFuncAux;
}

void MainWindow::toLogin(){
    Login *pLogin = new Login(this);

    pLogin->setWindowModality(Qt::ApplicationModal);
    pLogin->setWindowFlag(Qt::FramelessWindowHint);
    pLogin->setWindowTitle(nombre_programa);
    pLogin->exec();

    delete pLogin;
}

void MainWindow::toRegistro(){
    Registro *pRegistro = new Registro(this);

    pRegistro->setWindowModality(Qt::ApplicationModal);
    pRegistro->setWindowFlag(Qt::FramelessWindowHint);
    pRegistro->setWindowTitle(nombre_programa);
    pRegistro->exec();

    delete pRegistro;
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
        QTimer::singleShot(1, &loop, SLOT(quit()));
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
    QSqlQuery       sql;
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
        sql = QSqlQuery(db_sql);
        str_sql = "CREATE TABLE if not exists RegistroSesiones(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Usuario TEXT, "
                  "                                                                                 FechaInicio TEXT,"
                  "                                                                                 HoraInicio TEXT,"
                  "                                                                                 FechaCierre TEXT,"
                  "                                                                                 HoraCierre TEXT);";
        sql.exec(str_sql);

        str_sql = "CREATE TABLE if not exists Usuario(_ID INTEGER PRIMARY KEY AUTOINCREMENT,Usuario TEXT, "
                  "                                                                          Passwd TEXT);";
        sql.exec(str_sql);

    }

    //
    // Cerramos la BD y la Conexion
    //
    db_sql.close();
    db_sql.removeDatabase("conecta_sql");

    return todo_ok;
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

    exit(0);
}
