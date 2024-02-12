#include "importarincidencias.h"
#include "ui_importarincidencias.h"

#include "funcaux.h"

#include <QDir>
#include <QFileDialog>

importarincidencias::importarincidencias(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::importarincidencias){

    ui->setupUi(this);

    initUi();
}

importarincidencias::~importarincidencias(){
    delete ui;
}

void importarincidencias::initUi(){
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
    if(FuncAux().esFormatoIncidencias(rutaArchivoOrigen)){
        ui->lblTipoArchivo->setText("Archivo de datos de Incidencias (Android)");
        ui->lblDesde->setText(FuncAux().primerRegistroIncidencias(rutaArchivoOrigen));
        ui->lblHasta->setText(FuncAux().ultimoRegistroIncidencias(rutaArchivoOrigen));
        ui->btnImportar->setEnabled(true);
    }
    else{
        ui->lblTipoArchivo->setText("Archivo de datos no reconocido...");
        ui->btnImportar->setEnabled(false);
    }
}

void importarincidencias::on_btnImportar_clicked(){
    QString rutaOrigen  = ui->lblNombreArchivo->text();
    QString rutaDestino = qApp->applicationDirPath() + "/Data/Incidencias.db";
    QString rutaOld     = qApp->applicationDirPath() + "/Data/Incidencias.old";
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

void importarincidencias::on_btnCancelar_clicked(){

    this->close();
}

void importarincidencias::on_btnAbrirArchivo_clicked(){

    initUi();
}

