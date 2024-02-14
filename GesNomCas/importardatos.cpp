#include "importardatos.h"
#include "ui_importardatos.h"

#include "funcaux.h"

#include <QDir>
#include <QFileDialog>

importarDatos::importarDatos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::importarDatos){

    ui->setupUi(this);

    initUi();
}

importarDatos::~importarDatos(){
    delete ui;
}

void importarDatos::initUi(){
    QString strArchivoOrigen = "";
    QString strDescargas;

    strDescargas       = QDir::homePath() + "/Descargas";
    strArchivoOrigen   = QFileDialog::getOpenFileName(this, NOMBRE_PROGRAMA, strDescargas);

    //
    // Establecemos los estilos
    //
    ui->lblNombreArchivo->setStyleSheet("color: blue");
    ui->lblDesde->setStyleSheet("color: blue");
    ui->lblHasta->setStyleSheet("color: blue");
    ui->lblTipoArchivo->setStyleSheet("color: blue");

    //
    // Mostramos la ruta del archivo
    //
    ui->lblNombreArchivo->setText(strArchivoOrigen);
    ui->lblNombreArchivo->setToolTip(strArchivoOrigen);

    //
    // Miramos si es un formato valido
    //
    if(FuncAux().esFormatoDatos(strArchivoOrigen)){
        ui->lblTipoArchivo->setText("Archivo de datos de GesNomCas");
        ui->lblDesde->setText(FuncAux().primerRegistroDatos(strArchivoOrigen));
        ui->lblHasta->setText(FuncAux().ultimoRegistroDatos(strArchivoOrigen));
        ui->btnImportar->setEnabled(true);
    }
    else{
        if(ui->lblNombreArchivo->text() != ""){
            ui->lblTipoArchivo->setText("Archivo de datos no reconocido...");
            ui->btnImportar->setEnabled(false);
        }
    }
}

void importarDatos::on_btnCancelar_clicked(){

    this->close();
}

void importarDatos::on_btnImportar_clicked(){
    QString strOrigen  = ui->lblNombreArchivo->text();
    QString strDestino = qApp->applicationDirPath() + "/Data/GesNomCas.db";
    QString strOld     = qApp->applicationDirPath() + "/Data/GesNomCas.old";
    QFile   fileDestino;
    QFile   fileOld;

    fileDestino.setFileName(strDestino);
    fileOld.setFileName(strDestino);

    if(fileDestino.exists()){
        fileOld.rename(strOld);
    }

    QFile::copy(strOrigen, strDestino);

    this->close();
}

void importarDatos::on_btnAbrirArchivo_clicked(){

    initUi();
}

