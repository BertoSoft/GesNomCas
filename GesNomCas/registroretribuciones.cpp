#include "registroretribuciones.h"
#include "ui_registroretribuciones.h"

#include "funcaux.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

RegistroRetribuciones::RegistroRetribuciones(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistroRetribuciones)
{
    ui->setupUi(this);

    initUi();
}

RegistroRetribuciones::~RegistroRetribuciones(){
    delete ui;
}

void RegistroRetribuciones::initUi(){

    initChks();
    ui->btnEliminar->setEnabled(false);
    ui->btnGuardar->setEnabled(false);
    controlesOff();
}

void RegistroRetribuciones::initChks(){

    ui->cmbClave->addItem("SALARIO");
    ui->cmbClave->addItem("COTIZACION");
    ui->cmbClave->addItem("RETENCION");
}

void RegistroRetribuciones::controlesClean(){

    ui->txtCodigo->setText("");
    ui->txtDenominacion->setText("");
    ui->txtCuantia->setText("");
    ui->cmbClave->setCurrentIndex(0);
}

void RegistroRetribuciones::controlesOn(){

    ui->txtCodigo->setEnabled(true);
    ui->cmbClave->setEnabled(true);
    ui->txtDenominacion->setEnabled(true);
    ui->txtCuantia->setEnabled(true);
}

void RegistroRetribuciones::controlesOff(){

    ui->txtCodigo->setEnabled(false);
    ui->cmbClave->setEnabled(false);
    ui->txtDenominacion->setEnabled(false);
    ui->txtCuantia->setEnabled(false);
}

void RegistroRetribuciones::on_cmbClave_activated(int index){

}

void RegistroRetribuciones::on_txtCodigo_returnPressed(){

    ui->txtDenominacion->setFocus();
    ui->txtDenominacion->selectAll();
}

void RegistroRetribuciones::on_txtDenominacion_returnPressed(){

    ui->txtCuantia->setFocus();
    ui->txtCuantia->selectAll();
}

void RegistroRetribuciones::on_txtCuantia_returnPressed(){

    on_btnGuardar_clicked();
}

void RegistroRetribuciones::on_btnGuardar_clicked(){

    if(ui->txtCodigo->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo del Código no puede estar vacío");
        ui->txtCodigo->setFocus();
    }
    else if(ui->txtDenominacion->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la Denominación no puede estar vacío");
        ui->txtDenominacion->setFocus();
    }
    else if(ui->txtCuantia->text() == ""){
        QMessageBox::information(this, FuncAux().getAppName(), "El campo de la cuantía no puede estar vacío");
        ui->txtCuantia->setFocus();
    }
    else{
        guardar();
        controlesClean();
        initUi();
    }
}

void RegistroRetribuciones::on_btnEliminar_clicked(){

}

void RegistroRetribuciones::on_btnCancelar_clicked(){

    salir();
}

void RegistroRetribuciones::on_btnAdd_clicked(){

    controlesOn();
    controlesClean();
    ui->btnGuardar->setEnabled(true);
    ui->txtCodigo->setFocus();
}

void RegistroRetribuciones::salir(){

    this->close();
}

void RegistroRetribuciones::guardar(){

}

void RegistroRetribuciones::on_txtCodigo_textChanged(const QString &arg1){
    QString     str = arg1;
    int         len;
    int         i;

    i=0;
    len = str.length();
    while(i<len) {

        //
        // Si len = 1, solo puede ser numerico, sino lo borramos
        //
        if(i==0){
            if(!str[0].isDigit()){
                str.remove(0, 1);
                ui->txtCodigo->setText(str);
            }
        }

        //
        // Si len = 2, puede ser numerico o punto, sino borramos
        //
        if(i==1){
            if(!str[1].isDigit() && str[1] != '.'){
                str.remove(1, 1);
                ui->txtCodigo->setText(str);
            }
        }

        //
        // Si len > 2, solo puede ser numerico, sino lo borramos
        //
        if(i>1 && i<len){
            if(!str[i].isDigit()){
                str.remove(i, 1);
                ui->txtCodigo->setText(str);
            }
        }
        i++;
    }
}

void RegistroRetribuciones::on_txtCodigo_cursorPositionChanged(int arg1, int arg2){
    int posOld  = arg1;
    int posNew  = arg2;
    int dif     = (posNew - posOld);

    //
    // Si la nueva pos es anterior a la vieja y esta no es 1, seleccionamos todo
    //
    if((dif < 0) && (posNew != 1)){
        ui->txtCodigo->selectAll();
    }
}

