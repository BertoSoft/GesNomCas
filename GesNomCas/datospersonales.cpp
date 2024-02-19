#include "datospersonales.h"
#include "ui_datospersonales.h"

DatosPersonales::DatosPersonales(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatosPersonales){

    ui->setupUi(this);

    initUi();
}

DatosPersonales::~DatosPersonales(){
    delete ui;
}

void DatosPersonales::initUi(){

    ui->txtNombre->setFocus();

}

void DatosPersonales::on_btnCancelar_clicked(){

    this->close();
}

void DatosPersonales::on_txtNombre_returnPressed(){

    ui->txtApellidos->setFocus();
    ui->txtApellidos->selectAll();
}

void DatosPersonales::on_txtApellidos_returnPressed(){

    ui->txtDireccion->setFocus();
    ui->txtDireccion->selectAll();
}

void DatosPersonales::on_txtDireccion_returnPressed(){

    ui->txtCodigoPostal->setFocus();
    ui->txtCodigoPostal->selectAll();
}

void DatosPersonales::on_txtCodigoPostal_returnPressed(){

    ui->txtPoblacion->setFocus();
    ui->txtPoblacion->selectAll();
}

void DatosPersonales::on_txtPoblacion_returnPressed(){

    ui->txtProvincia->setFocus();
    ui->txtProvincia->selectAll();
}

void DatosPersonales::on_txtProvincia_returnPressed(){

    ui->txtPais->setFocus();
    ui->txtPais->selectAll();
}

void DatosPersonales::on_txtPais_returnPressed(){

    on_btnGuardar_clicked();
}

void DatosPersonales::on_btnGuardar_clicked(){

}



