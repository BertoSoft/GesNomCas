#include "precargarnomina.h"
#include "ui_precargarnomina.h"

#include "funcaux.h"

#include <QDate>

PreCargarNomina::PreCargarNomina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PreCargarNomina){

    ui->setupUi(this);

    initSp();
    initUi();
}

PreCargarNomina::~PreCargarNomina(){
    delete ui;
}

void PreCargarNomina::initSp(){
    QDate   qdFecha;
    int     iAno;
    int     iLimite;

    //
    // Colocamos el año actual, uno despues y 10 anteriores, empezando en 2022
    //
    qdFecha = QDate::currentDate();
    iAno    = qdFecha.year();
    iLimite = iAno - 10;
    iAno++;
    while (iAno > iLimite) {
        if(iAno > 2021){
            ui->cmbAno->addItem(QString::number(iAno));
        }
        iAno--;
    }
    ui->cmbAno->setCurrentIndex(1);

    ui->cmbAno->setStyleSheet("color:rgb(0,0,255)");

}

void PreCargarNomina::initUi(){

    ui->listNominas->setStyleSheet("color:rgb(0,0,255)");
    rellenaListado();
    ui->btnCargar->setEnabled(false);
}

void PreCargarNomina::rellenaListado(){
    QList<FuncAux::DatosNomina>     listaAllNominas;
    QList<QString>                  listaNominasAno;
    int                             i   = 0;
    int                             j   = 0;
    bool                            bExiste;

    listaAllNominas = FuncAux().getAllDatosNominas();
    i = 0;
    while (i < listaAllNominas.count()) {

        //
        // Si la nomina es de este año la añadimos
        //
        if(listaAllNominas[i].strAno == ui->cmbAno->currentText()){
            bExiste = false;
            j = 0;
            while(j < listaNominasAno.count()){

                //
                // Comprobamos si esta nomina ya existe
                //
                if(listaNominasAno[j] == listaAllNominas[i].strMes){
                    bExiste = true;
                    j = listaNominasAno.count();
                }

                j++;
            }

            //
            // Si la nomina no existe la aumentamos a la lista
            //
            if(!bExiste){
                listaNominasAno.append(listaAllNominas[i].strMes);
            }
        }

        i++;
    }

    //
    // Borramos el listado antiguo
    //
    while (ui->listNominas->count() > 0) {
        ui->listNominas->takeItem(0);
    }

    //
    // Rellenamos el list
    //
    i = 0;
    while (i < listaNominasAno.count()) {
        ui->listNominas->addItem(listaNominasAno[i]);
        i++;
    }

}

void PreCargarNomina::on_btnCancelar_clicked(){

    strMes = "-1";
    strAno = "-1";
    this->close();

}

void PreCargarNomina::on_btnCargar_clicked(){

    this->close();
}

void PreCargarNomina::on_cmbAno_activated(int index){
    initUi();
}

void PreCargarNomina::on_listNominas_itemClicked(QListWidgetItem *item){

    ui->btnCargar->setEnabled(true);

    strAno = ui->cmbAno->currentText();
    strMes = item->text();
}

void PreCargarNomina::on_listNominas_itemDoubleClicked(QListWidgetItem *item){

    on_btnCargar_clicked();
}

