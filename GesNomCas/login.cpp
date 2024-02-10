#include "login.h"
#include "ui_login.h"

#include "funcaux.h"

#include <QApplication>
#include <QMessageBox>
#include <QScreen>
#include <QKeyEvent>
#include <QDate>
#include <QTime>
#include <QMessageBox>


Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    //
    // Instalamos un filtro de eventos
    //
    this->installEventFilter(this);

    //
    // Iniciamos la pantalla
    //
    initUi();
}

Login::~Login()
{
    delete ui;
}

bool Login::eventFilter(QObject *obj, QEvent *ev){

    //
    // Detectamos si se pulsa la tecla esc
    //
    if(obj == this && ev->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(ev);
        if(keyEvent->key() == Qt::Key_Escape){
            salir();
        }
    }

    return QObject::eventFilter(obj, ev);
}

void Login::initUi(){

    centrar();
    ui->lblUsuario->setStyleSheet("color: blue; font-size: 11pt; font-weight: bold");
    ui->lblUsuario->setAlignment(Qt::AlignCenter);
    ui->lblUsuario->setText("Hola, Alberto");
    ui->etPasswd->setFocus();
}

void Login::centrar(){
    QRect rect_pantalla = QApplication::primaryScreen()->geometry();
    this->move((rect_pantalla.width() - this->width()) / 2, (rect_pantalla.height() - this->height()) / 2);
}

void Login::salir(){
    QMessageBox::StandardButton respuesta;

    respuesta = QMessageBox::warning(this, nombre_programa, "¿ Realmente quieres salir del programa ?", QMessageBox::Yes|QMessageBox::No);
    if(respuesta == QMessageBox::Yes){
        exit(0);
    }
    else{
        ui->etPasswd->setFocus();
        ui->etPasswd->selectAll();
    }
}

void Login::entrar(){
    QString fecha   = QDate::currentDate().toString("dd/MM/yyyy");
    QString hora    = QTime::currentTime().toString("hh:mm:ss");

    FuncAux().setInicioSesion(fecha, hora);
    this->close();
}

void Login::on_btnSalir_clicked(){
    salir();
}

void Login::on_btnLogin_clicked(){
    entrar();
}

