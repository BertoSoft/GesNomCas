#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "funcaux.h"
#include "login.h"
#include "registro.h"
#include "importardatos.h"
#include "importarincidencias.h"
#include "datospersonales.h"
#include "datosempresa.h"
#include "datosempleado.h"
#include "registroretribuciones.h"
#include "registrodiasfestivos.h"
#include "registrovacaciones.h"

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
#include <QFile>
#include <QMessageBox>


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

    //
    // Comprobando los actions enableds
    //
    compruebaActions();

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

    lblTexto->setText(FuncAux().getAppName());
    refrescaReloj();

}

void MainWindow::compruebaActions(){
    QFile fileIncidencias = QFile(qApp->applicationDirPath() + "/Data/Incidencias.db");

    if(fileIncidencias.exists()){
        ui->actionExportar_Archivo_de_Incidencias->setEnabled(true);
    }
    else{
        ui->actionExportar_Archivo_de_Incidencias->setEnabled(false);
    }

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
    pLogin->exec();

    delete pLogin;
}

void MainWindow::toRegistro(){
    Registro *pRegistro = new Registro(this);

    pRegistro->setWindowModality(Qt::ApplicationModal);
    pRegistro->setWindowFlag(Qt::FramelessWindowHint);
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

    lblTexto->setText("Importando una copia de los datos del programa...");

    importarDatos *pImportarDatos = new importarDatos(this);

    pImportarDatos->setWindowModality(Qt::ApplicationModal);
    pImportarDatos->setWindowFlag(Qt::FramelessWindowHint);
    pImportarDatos->exec();

    delete pImportarDatos;

}

void MainWindow::on_actionImportar_Archivo_de_Incidencias_triggered(){

    lblTexto->setText("Importando una copia de los datos de incidencias...");

    importarincidencias *pImportarIncidencias = new importarincidencias(this);

    pImportarIncidencias->setWindowModality(Qt::ApplicationModal);
    pImportarIncidencias->setWindowFlag(Qt::FramelessWindowHint);
    pImportarIncidencias->exec();

    delete pImportarIncidencias;

    //
    // Debemos comprobar si ya existe un archivo incidencias
    //
    compruebaActions();
}

void MainWindow::on_actionExportar_Archivo_de_Datos_triggered(){
    QString                     strOrigen  = qApp->applicationDirPath() + "/Data/GesNomCas.db";
    QString                     strDestino;
    QFile                       fileOrigen;
    QFile                       fileDestino;

    lblTexto->setText("Exportando una copia de los datos del programa...");

    strDestino = QFileDialog::getSaveFileName(this, FuncAux().getAppName(), qApp->applicationDirPath());

    //
    // Si el nombre de la ruta destino no es vacia
    //
    if(strDestino != ""){
        fileOrigen.setFileName(strOrigen);
        fileDestino.setFileName(strDestino);
        //
        // Si el archivo destino ya existe , preguntamos
        //
        if(fileDestino.exists()){
            QFile::remove(strDestino);
            if(!QFile::copy(strOrigen, strDestino)){
                QMessageBox::information(this, FuncAux().getAppName(), "Ha ocurrido un error en la copia de datos...");
            }
        }
        //
        // Hacemos la copia y notificamos
        //
        else{
            if(QFile::copy(strOrigen, strDestino)){
                QMessageBox::information(this, FuncAux().getAppName(), "Copia de datos guardada con exito");
            }
        }
    }
}

void MainWindow::on_actionExportar_Archivo_de_Incidencias_triggered(){
    QString                     strOrigen  = qApp->applicationDirPath() + "/Data/Incidencias.db";
    QString                     strDestino;
    QFile                       fileOrigen;
    QFile                       fileDestino;

    lblTexto->setText("Exportando una copia de los datos de incidencias...");

    strDestino = QFileDialog::getSaveFileName(this, FuncAux().getAppName(), qApp->applicationDirPath());

    //
    // Si el nombre de la ruta destino no es vacia
    //
    if(strDestino != ""){
        fileOrigen.setFileName(strOrigen);
        fileDestino.setFileName(strDestino);
        //
        // Si el archivo destino ya existe , preguntamos
        //
        if(fileDestino.exists()){
            QFile::remove(strDestino);
            if(!QFile::copy(strOrigen, strDestino)){
                QMessageBox::information(this, FuncAux().getAppName(), "Ha ocurrido un error en la copia de datos...");
            }
        }
        //
        // Hacemos la copia y notificamos
        //
        else{
            if(QFile::copy(strOrigen, strDestino)){
                QMessageBox::information(this, FuncAux().getAppName(), "Copia de datos guardada con exito");
            }
        }
    }
}

void MainWindow::on_actionDatos_Personales_triggered(){

    lblTexto->setText("Editando los datos personales...");

    DatosPersonales *pDatosPersonales = new DatosPersonales(this);

    pDatosPersonales->setWindowModality(Qt::ApplicationModal);
    pDatosPersonales->setWindowFlag(Qt::FramelessWindowHint);
    pDatosPersonales->exec();

    delete pDatosPersonales;
}

void MainWindow::on_actionDatos_Centro_Trabajo_triggered(){

    lblTexto->setText("Editando los datos de la Empresa...");

    DatosEmpresa *pDatosEmpresa = new DatosEmpresa(this);

    pDatosEmpresa->setWindowModality(Qt::ApplicationModal);
    pDatosEmpresa->setWindowFlag(Qt::FramelessWindowHint);
    pDatosEmpresa->exec();

    delete pDatosEmpresa;
}

void MainWindow::on_actionDatos_Empleado_triggered(){

    lblTexto->setText("Editando los datos del Empleado...");

    DatosEmpleado *pDatosEmpleado = new DatosEmpleado(this);

    pDatosEmpleado->setWindowModality(Qt::ApplicationModal);
    pDatosEmpleado->setWindowFlag(Qt::FramelessWindowHint);
    pDatosEmpleado->exec();

    delete pDatosEmpleado;
}

void MainWindow::on_actionRegistro_Unidades_N_mina_triggered(){

    lblTexto->setText("Editando el registro de Unidades de Nómina...");

    RegistroRetribuciones *pRegistroRetribuciones = new RegistroRetribuciones(this);

    pRegistroRetribuciones->setWindowModality(Qt::ApplicationModal);
    pRegistroRetribuciones->setWindowFlag(Qt::FramelessWindowHint);
    pRegistroRetribuciones->exec();

    delete pRegistroRetribuciones;
}

void MainWindow::on_actionRegistro_D_as_Festivos_triggered(){

    lblTexto->setText("Editando el registro de Días Festivos...");

    RegistroDiasFestivos *pRegistroDiasFestivos = new RegistroDiasFestivos(this);

    pRegistroDiasFestivos->setWindowModality(Qt::ApplicationModal);
    pRegistroDiasFestivos->setWindowFlag(Qt::FramelessWindowHint);
    pRegistroDiasFestivos->exec();

    delete pRegistroDiasFestivos;
}

void MainWindow::on_actionRegistro_Vacaciones_triggered(){

    lblTexto->setText("Editando el registro de Vacaciones...");

    RegistroVacaciones *pRegistroVacaciones = new RegistroVacaciones(this);

    pRegistroVacaciones->setWindowModality(Qt::ApplicationModal);
    pRegistroVacaciones->setWindowFlag(Qt::FramelessWindowHint);
    pRegistroVacaciones->exec();

    delete pRegistroVacaciones;
}

