#include "importarincidencias.h"
#include "ui_importarincidencias.h"

#include "funcaux.h"

#include <QDir>
#include <QFileDialog>

extern QString NOMBRE_PROGRAMA;

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
    QString strOrigen = "";
    QString strDescargas;

    strDescargas       = QDir::homePath() + "/Descargas";
    strOrigen   = QFileDialog::getOpenFileName(this);

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
    ui->lblNombreArchivo->setText(strOrigen);
    ui->lblNombreArchivo->setToolTip(strOrigen);

    //
    // Miramos si es un formato valido
    //
    if(FuncAux().esFormatoIncidencias(strOrigen)){
        ui->lblTipoArchivo->setText("Archivo de datos de Incidencias (Android)");
        ui->lblDesde->setText(FuncAux().primerRegistroIncidencias(strOrigen));
        ui->lblHasta->setText(FuncAux().ultimoRegistroIncidencias(strOrigen));
        ui->btnImportar->setEnabled(true);
    }
    else{
        if(ui->lblNombreArchivo->text() != ""){
            ui->lblTipoArchivo->setText("Archivo de datos no reconocido...");
            ui->btnImportar->setEnabled(false);
        }
    }
}

void importarincidencias::on_btnImportar_clicked(){
    QString strOrigen  = ui->lblNombreArchivo->text();
    QString strDestino = qApp->applicationDirPath() + "/Data/Incidencias.db";
    QString strOld     = qApp->applicationDirPath() + "/Data/Incidencias.old";
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

void importarincidencias::on_btnCancelar_clicked(){

    this->close();
}

void importarincidencias::on_btnAbrirArchivo_clicked(){

    initUi();
}

