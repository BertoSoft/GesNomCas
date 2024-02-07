#include "login.h"
#include "ui_login.h"

#include <QApplication>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QScreen>
#include <QKeyEvent>


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
    ui->etUsuario->setFocus();
}

void Login::centrar(){
    QRect rect_pantalla = QApplication::primaryScreen()->geometry();
    this->move((rect_pantalla.width() - this->width()) / 2, (rect_pantalla.height() - this->height()) / 2);
}

void Login::salir(){
    exit(0);
}

void Login::on_buttonBox_clicked(QAbstractButton *button){
    QAbstractButton *ok = ui->buttonBox->buttons()[0];
    QAbstractButton *cancel = ui->buttonBox->buttons()[1];

    if(button == ok){

    }
    if(button == cancel){
        salir();
    }
}

