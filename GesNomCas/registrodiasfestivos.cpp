#include "registrodiasfestivos.h"
#include "ui_registrodiasfestivos.h"

RegistroDiasFestivos::RegistroDiasFestivos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroDiasFestivos)
{
    ui->setupUi(this);
}

RegistroDiasFestivos::~RegistroDiasFestivos()
{
    delete ui;
}

void RegistroDiasFestivos::on_btnCancelar_clicked(){

    this->close();
}

