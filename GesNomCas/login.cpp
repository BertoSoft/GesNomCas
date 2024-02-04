#include "login.h"
#include "ui_login.h"

#include <QApplication>
#include <QScreen>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    centrar();
}

Login::~Login()
{
    delete ui;
}


void Login::centrar(){

    QRect rect_pantalla = QApplication::primaryScreen()->geometry();
    this->move((rect_pantalla.width() - this->width()) / 2, (rect_pantalla.height() - this->height()) / 2);
}
