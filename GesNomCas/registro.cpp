#include "registro.h"
#include "ui_registro.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QAbstractButton>
#include <QScreen>
#include <QKeyEvent>

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
        }
    }

    return QObject::eventFilter(obj, ev);
}

void Registro::initUi(){
    centrar();
    ui->etUsuario->setFocus();


}

void Registro::centrar(){
    QRect rect_pantalla = QApplication::primaryScreen()->geometry();
    this->move((rect_pantalla.width() - this->width()) / 2, (rect_pantalla.height() - this->height()) / 2);
}

void Registro::on_buttonBox_clicked(QAbstractButton *button){
    QAbstractButton *ok = ui->buttonBox->buttons()[0];
    QAbstractButton *cancel = ui->buttonBox->buttons()[1];


    if(button == ok){
        enter();
    }
    if(button == cancel){
        salir();
    }
}

void Registro::salir(){
    exit(0);
}

void Registro::enter(){
    int i = 0;
}

void Registro::on_etUsuario_returnPressed(){
    ui->etPasswd->setFocus();
    ui->etPasswd->selectAll();
}

