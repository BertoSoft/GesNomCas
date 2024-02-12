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
    QString rutaArchivoOrigen = "";
    QString rutaDescargas;

    rutaDescargas       = QDir::homePath() + "/Descargas";
    rutaArchivoOrigen   = QFileDialog::getOpenFileName(this, nombrePrograma, rutaDescargas);

    //
    // Mostramos la ruta del archivo
    //
    ui->lblNombreArchivo->setText(rutaArchivoOrigen);
    ui->lblNombreArchivo->setToolTip(rutaArchivoOrigen);

    //
    // Miramos si es un formato valido
    //
    if(FuncAux().esFormatoDatos(rutaArchivoOrigen)){
        ui->lblTipoArchivo->setText("Archivo de datos de GesNomCas");
        ui->lblDesde->setText(FuncAux().primerRegistroDatos(rutaArchivoOrigen));
        ui->lblHasta->setText(FuncAux().ultimoRegistroDatos(rutaArchivoOrigen));
        ui->btnImportar->setEnabled(true);
    }
    else{
        ui->lblTipoArchivo->setText("Archivo de datos no reconocido...");
        ui->btnImportar->setEnabled(false);
    }
}

void importarDatos::on_btnCancelar_clicked(){

    this->close();
}

void importarDatos::on_btnImportar_clicked(){
    QString rutaOrigen  = ui->lblNombreArchivo->text();
    QString rutaDestino = qApp->applicationDirPath() + "/Data/GesNomCas.db";
    QString rutaOld     = qApp->applicationDirPath() + "/Data/GesNomCas.old";
    QFile   fileDestino;
    QFile   fileOld;

    fileDestino.setFileName(rutaDestino);
    fileOld.setFileName(rutaDestino);

    if(fileDestino.exists()){
        fileOld.rename(rutaOld);
    }

    QFile::copy(rutaOrigen, rutaDestino);

    this->close();
}

void importarDatos::on_btnAbrirArchivo_clicked(){

    initUi();
}

