#include "registro.h"
#include "ui_registro.h"

#include "mainwindow.h"
#include "funcaux.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QAbstractButton>
#include <QScreen>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDate>
#include <QTime>

Registro::Registro(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registro)
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

Registro::~Registro()
{
    delete ui;
}

bool Registro::eventFilter(QObject *obj, QEvent *ev){

    //
    // Detectamos si se pulsa la tecla esc
    //
    if(obj == this && ev->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(ev);
        if(keyEvent->key() == Qt::Key_Escape){
            salir();
            return true;
        }
    }
    return QObject::eventFilter(obj, ev);
}

void Registro::initUi(){
    centrar();
    ui->etUsuario->setFocus();
    QMessageBox::information(this, nombre_programa, "Debes establecer un Uusario y una Contraseña...");
}

void Registro::centrar(){
    QRect rect_pantalla = QApplication::primaryScreen()->geometry();
    this->move((rect_pantalla.width() - this->width()) / 2, (rect_pantalla.height() - this->height()) / 2);
}

void Registro::salir(){
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::warning(this, nombre_programa, "¿ Realmente quieres salir del programa ?", QMessageBox::Yes|QMessageBox::No);
    if(respuesta == QMessageBox::Yes){
        exit(0);
    }
    else{
        ui->etUsuario->setFocus();
        ui->etUsuario->selectAll();
    }
}

void Registro::on_etUsuario_returnPressed(){
    ui->etPasswd->setFocus();
    ui->etPasswd->selectAll();
}

void Registro::on_etPasswd_returnPressed(){
    ui->etPasswd1->setFocus();
    ui->etPasswd1->selectAll();
}

void Registro::on_etPasswd1_returnPressed(){
    ui->btnLogin->clicked();
}

void Registro::on_btnSalir_clicked(){
    salir();
}

void Registro::on_btnLogin_clicked(){

    //
    // si el campo de usuario esta vacio avisamos
    //
    if(ui->etUsuario->text() == ""){
        QMessageBox::information(this, nombre_programa, "El campo de usuario no puede estar vacío");
        ui->etUsuario->setFocus();
    }
    //
    // si el campo de passwd esta vacio avisamos
    //
    else if(ui->etPasswd->text() == ""){
        QMessageBox::information(this, nombre_programa, "El campo de password no puede estar vacío");
        ui->etPasswd->setFocus();
    }
    //
    // si el campo de passwd1 esta vacio avisamos
    //
    else if(ui->etPasswd->text() == ""){
        QMessageBox::information(this, nombre_programa, "Este campo no puede estar vacío");
        ui->etPasswd1->setFocus();
    }
    //
    // si las contraseñas no coinciden avisamos
    //
    else if(ui->etPasswd->text() != ui->etPasswd1->text()){
        QMessageBox::information(this, nombre_programa, "Las contraseñas no coinciden");
        ui->etPasswd->setFocus();
        ui->etPasswd->selectAll();
    }
    //
    // Todo corecto entramos
    //
    else{
        entrar();
    }
}

void Registro::entrar(){
    QString fecha   = QDate::currentDate().toString("dd/MM/yyyy");
    QString hora    = QTime::currentTime().toString("hh:mm:ss");

    FuncAux *pFuncAux = new FuncAux();

    pFuncAux->setUsuario(ui->etUsuario->text(), ui->etPasswd->text());
    pFuncAux->setInicioSesion(fecha, hora);
    this->close();

    delete pFuncAux;
}




