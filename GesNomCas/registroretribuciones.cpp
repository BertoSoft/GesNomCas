#include "registroretribuciones.h"
#include "ui_registroretribuciones.h"

RegistroRetribuciones::RegistroRetribuciones(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroRetribuciones)
{
    ui->setupUi(this);
}

RegistroRetribuciones::~RegistroRetribuciones()
{
    delete ui;
}

void RegistroRetribuciones::salir(){

    this->close();
}

void RegistroRetribuciones::on_btnCancelar_clicked(){

    salir();
}

