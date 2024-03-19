#include "calendariolaboral.h"
#include "ui_calendariolaboral.h"

#include "funcaux.h"

#include <QApplication>
#include <QScreen>
#include <QDate>
#include <QTableWidgetItem>

CalendarioLaboral::CalendarioLaboral(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CalendarioLaboral){

    ui->setupUi(this);

    initSp();
    initCalendario();
    initUi();
}

CalendarioLaboral::~CalendarioLaboral(){
    delete ui;
}

void CalendarioLaboral::on_btnCancelar_clicked(){
    this->close();
}

void CalendarioLaboral::initUi(){
    dibujaCalendario();
    coloreaCalendario();
}

void CalendarioLaboral::initSp(){
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
    while (iAno>iLimite) {
        if(iAno > 2021){
            ui->cmbAno->addItem(QString::number(iAno));
        }
        iAno--;
    }
    ui->cmbAno->setCurrentIndex(1);
}

void CalendarioLaboral::initCalendario(){
    int     ancho = (int) ui->tableEnero->width() * 0.95;
    int     alto = (int) ui->tableEnero->height() * 0.91;
    int     iFila;
    int     iCol;

    QStringList headers;
    headers += tr("L");
    headers += tr("M");
    headers += tr("X");
    headers += tr("J");
    headers += tr("V");
    headers += tr("S");
    headers += tr("D");

    //
    // Enero
    //
    ui->tableEnero->setRowCount(6);
    ui->tableEnero->setColumnCount(7);

    ui->tableEnero->setHorizontalHeaderLabels(headers);

    ui->tableEnero->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableEnero->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableEnero->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableEnero->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableEnero->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableEnero->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableEnero->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableEnero->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableEnero->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableEnero->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableEnero->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableEnero->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableEnero->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableEnero->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }


    ui->tableEnero->setEnabled(false);

    //
    // Febrero
    //
    ui->tableFebrero->setRowCount(6);
    ui->tableFebrero->setColumnCount(7);

    ui->tableFebrero->setHorizontalHeaderLabels(headers);

    ui->tableFebrero->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableFebrero->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableFebrero->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableFebrero->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableFebrero->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableFebrero->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableFebrero->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableFebrero->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableFebrero->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableFebrero->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableFebrero->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableFebrero->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableFebrero->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableFebrero->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableFebrero->setEnabled(false);

    //
    // Marzo
    //
    ui->tableMarzo->setRowCount(6);
    ui->tableMarzo->setColumnCount(7);

    ui->tableMarzo->setHorizontalHeaderLabels(headers);

    ui->tableMarzo->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableMarzo->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableMarzo->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableMarzo->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableMarzo->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableMarzo->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableMarzo->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableMarzo->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableMarzo->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableMarzo->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableMarzo->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableMarzo->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableMarzo->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableMarzo->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableMarzo->setEnabled(false);

    //
    // Abril
    //
    ui->tableAbril->setRowCount(6);
    ui->tableAbril->setColumnCount(7);

    ui->tableAbril->setHorizontalHeaderLabels(headers);

    ui->tableAbril->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableAbril->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableAbril->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableAbril->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableAbril->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableAbril->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableAbril->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableAbril->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableAbril->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableAbril->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableAbril->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableAbril->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableAbril->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableAbril->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableAbril->setEnabled(false);

    //
    // Mayo
    //
    ui->tableMayo->setRowCount(6);
    ui->tableMayo->setColumnCount(7);

    ui->tableMayo->setHorizontalHeaderLabels(headers);

    ui->tableMayo->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableMayo->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableMayo->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableMayo->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableMayo->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableMayo->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableMayo->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableMayo->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableMayo->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableMayo->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableMayo->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableMayo->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableMayo->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableMayo->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableMayo->setEnabled(false);

    //
    // Junio
    //
    ui->tableJunio->setRowCount(6);
    ui->tableJunio->setColumnCount(7);

    ui->tableJunio->setHorizontalHeaderLabels(headers);

    ui->tableJunio->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableJunio->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableJunio->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableJunio->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableJunio->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableJunio->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableJunio->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableJunio->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableJunio->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableJunio->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableJunio->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableJunio->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableJunio->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableJunio->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableJunio->setEnabled(false);

    //
    // Julio
    //
    ui->tableJulio->setRowCount(6);
    ui->tableJulio->setColumnCount(7);

    ui->tableJulio->setHorizontalHeaderLabels(headers);

    ui->tableJulio->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableJulio->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableJulio->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableJulio->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableJulio->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableJulio->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableJulio->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableJulio->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableJulio->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableJulio->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableJulio->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableJulio->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableJulio->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableJulio->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableJulio->setEnabled(false);

    //
    // Agosto
    //
    ui->tableAgosto->setRowCount(6);
    ui->tableAgosto->setColumnCount(7);

    ui->tableAgosto->setHorizontalHeaderLabels(headers);

    ui->tableAgosto->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableAgosto->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableAgosto->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableAgosto->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableAgosto->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableAgosto->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableAgosto->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableAgosto->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableAgosto->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableAgosto->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableAgosto->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableAgosto->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableAgosto->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableAgosto->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableAgosto->setEnabled(false);

    //
    // Septiembre
    //
    ui->tableSeptiembre->setRowCount(6);
    ui->tableSeptiembre->setColumnCount(7);

    ui->tableSeptiembre->setHorizontalHeaderLabels(headers);

    ui->tableSeptiembre->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableSeptiembre->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableSeptiembre->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableSeptiembre->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableSeptiembre->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableSeptiembre->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableSeptiembre->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableSeptiembre->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableSeptiembre->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableSeptiembre->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableSeptiembre->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableSeptiembre->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableSeptiembre->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableSeptiembre->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableSeptiembre->setEnabled(false);

    //
    // Octubre
    //
    ui->tableOctubre->setRowCount(6);
    ui->tableOctubre->setColumnCount(7);

    ui->tableOctubre->setHorizontalHeaderLabels(headers);

    ui->tableOctubre->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableOctubre->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableOctubre->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableOctubre->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableOctubre->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableOctubre->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableOctubre->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableOctubre->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableOctubre->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableOctubre->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableOctubre->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableOctubre->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableOctubre->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableOctubre->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableOctubre->setEnabled(false);

    //
    // Noviembre
    //
    ui->tableNoviembre->setRowCount(6);
    ui->tableNoviembre->setColumnCount(7);

    ui->tableNoviembre->setHorizontalHeaderLabels(headers);

    ui->tableNoviembre->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableNoviembre->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableNoviembre->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableNoviembre->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableNoviembre->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableNoviembre->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableNoviembre->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableNoviembre->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableNoviembre->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableNoviembre->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableNoviembre->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableNoviembre->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableNoviembre->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableNoviembre->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableNoviembre->setEnabled(false);

    //
    // Diciembre
    //
    ui->tableDiciembre->setRowCount(6);
    ui->tableDiciembre->setColumnCount(7);

    ui->tableDiciembre->setHorizontalHeaderLabels(headers);

    ui->tableDiciembre->setColumnWidth(0, (int) ( ancho / 7 ) );
    ui->tableDiciembre->setColumnWidth(1, (int) ( ancho / 7 ) );
    ui->tableDiciembre->setColumnWidth(2, (int) ( ancho / 7 ) );
    ui->tableDiciembre->setColumnWidth(3, (int) ( ancho / 7 ) );
    ui->tableDiciembre->setColumnWidth(4, (int) ( ancho / 7 ) );
    ui->tableDiciembre->setColumnWidth(5, (int) ( ancho / 7 ) );
    ui->tableDiciembre->setColumnWidth(6, (int) ( ancho / 7 ) );

    ui->tableDiciembre->setRowHeight(0, (int) ( alto / 6 ) );
    ui->tableDiciembre->setRowHeight(1, (int) ( alto / 6 ) );
    ui->tableDiciembre->setRowHeight(2, (int) ( alto / 6 ) );
    ui->tableDiciembre->setRowHeight(3, (int) ( alto / 6 ) );
    ui->tableDiciembre->setRowHeight(4, (int) ( alto / 6 ) );
    ui->tableDiciembre->setRowHeight(5, (int) ( alto / 6 ) );

    iFila   = 0;
    iCol    = 0;

    while(iFila < 6){
        while(iCol < 7){
            QTableWidgetItem *item = new QTableWidgetItem("");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableDiciembre->setItem(iFila, iCol, item);

            iCol++;
        }
        iFila++;
        iCol = 0;
    }

    ui->tableDiciembre->setEnabled(false);

}

void CalendarioLaboral::dibujaCalendario(){
    QDate   qdFecha;
    int     iAno;
    int     iCol;
    int     iFila;
    QString str;


    //
    // Coloco las leyendas
    //
    ui->colorNacional->setStyleSheet("background-color:rgb(255, 0, 0)");
    ui->colorAutonmicos->setStyleSheet("background-color:rgb(0, 255, 0)");
    ui->colorLocales->setStyleSheet("background-color:rgb(0, 0, 255)");
    ui->colorConvenio->setStyleSheet("background-color:rgb(125, 125, 125)");
    ui->colorExcesoJornada->setStyleSheet("background-color:rgb(125, 255, 255)");
    ui->colorVacaciones->setStyleSheet("background-color:rgb(255, 125, 125)");

    iAno = ui->cmbAno->currentText().toInt();
    qdFecha.setDate(iAno, 1, 1);

    //
    // Enero
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 1) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableEnero->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableEnero->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Febrero
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 2) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableFebrero->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableFebrero->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Marzo
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 3) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableMarzo->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableMarzo->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Abril
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 4) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableAbril->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableAbril->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Mayo
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 5) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableMayo->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableMayo->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Junio
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 6) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableJunio->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableJunio->item(iFila, iCol)->setText(QString::number(qdFecha.day()));
        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Julio
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 7) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableJulio->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableJulio->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Agosto
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 8) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableAgosto->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableAgosto->item(iFila, iCol)->setText(QString::number(qdFecha.day()));
        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Septiembre
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 9) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableSeptiembre->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableSeptiembre->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Octubre
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 10) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableOctubre->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableOctubre->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Noviembre
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 11) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableNoviembre->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableNoviembre->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }

    //
    // Diciembre
    //
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFecha);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    while (qdFecha.month() == 12) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(iCol == 5 || iCol == 6){
            ui->tableDiciembre->item(iFila, iCol)->setBackground(QBrush(Qt::red));
        }
        ui->tableDiciembre->item(iFila, iCol)->setText(QString::number(qdFecha.day()));

        qdFecha = qdFecha.addDays(1);
        iCol++;
    }
}

void CalendarioLaboral::coloreaCalendario(){
    QList<FuncAux::DatosFestivos>   listaFestivos;
    int                             i = 0;
    QList<int>                      iPos;
    int                             iFila;
    int                             iCol;
    QColor                          color;

    listaFestivos = FuncAux().getAllFestivos();

    while (i < listaFestivos.count()) {
        if(listaFestivos[i].qdFecha.year() == ui->cmbAno->currentText().toInt()){
            iPos    = dateToPos(listaFestivos[i].qdFecha);
            iFila   = iPos[0];
            iCol    = iPos[1];

            if(listaFestivos[i].strTipoFestivo == "Nacional"){color = colorNacional;}
            if(listaFestivos[i].strTipoFestivo == "Autonómico"){color = colorAutonomico;}
            if(listaFestivos[i].strTipoFestivo == "Local"){color = colorLocal;}
            if(listaFestivos[i].strTipoFestivo == "Convenio"){color = colorConvenio;}
            if(listaFestivos[i].strTipoFestivo == "Exceso Jornada"){color = colorExcesoJornada;}

            //
            //Enero
            //
            if(listaFestivos[i].qdFecha.month() == 1){
                ui->tableEnero->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Febrero
            //
            if(listaFestivos[i].qdFecha.month() == 2){
                ui->tableFebrero->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Marzo
            //
            if(listaFestivos[i].qdFecha.month() == 3){
                ui->tableMarzo->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Abril
            //
            if(listaFestivos[i].qdFecha.month() == 4){
                ui->tableAbril->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Mayo
            //
            if(listaFestivos[i].qdFecha.month() == 5){
                ui->tableMayo->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Junio
            //
            if(listaFestivos[i].qdFecha.month() == 6){
                ui->tableJunio->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Julio
            //
            if(listaFestivos[i].qdFecha.month() == 7){
                ui->tableJulio->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Agosto
            //
            if(listaFestivos[i].qdFecha.month() == 8){
                ui->tableAgosto->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Septiembre
            //
            if(listaFestivos[i].qdFecha.month() == 9){
                ui->tableSeptiembre->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Octubre
            //
            if(listaFestivos[i].qdFecha.month() == 10){
                ui->tableOctubre->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Noviembre
            //
            if(listaFestivos[i].qdFecha.month() == 11){
                ui->tableNoviembre->item(iFila, iCol)->setBackground(QBrush(color));
            }

            //
            //Diciembre
            //
            if(listaFestivos[i].qdFecha.month() == 12){
                ui->tableDiciembre->item(iFila, iCol)->setBackground(QBrush(color));
            }
        }
        i++;
    }
}

QList<int> CalendarioLaboral::dateToPos(QDate qdFecha){
    QList<int>  iPos;
    QString     str;
    QDate       qdFechaTmp;
    int         iFila;
    int         iCol;

    //
    // Recorremos el mes con qdFechaTmp
    //
    qdFechaTmp.setDate(qdFecha.year(), qdFecha.month(), 1);
    iFila = 0;
    str = FuncAux().dateToFechaLarga(qdFechaTmp);
    str = str.remove(4, str.length() - 4);

    if(str == "lune"){
        iCol = 0;
    }
    else if(str == "mart"){
        iCol = 1;
    }
    else if(str == "miér"){
        iCol = 2;
    }
    else if(str == "juev"){
        iCol = 3;
    }
    else if(str == "vier"){
        iCol = 4;
    }
    else if(str == "sába"){
        iCol = 5;
    }
    else{
        iCol = 6;
    }

    //
    // Si coinciden qdFecha y qdFechaTmp, devolvemos iFila e iCol
    while (qdFechaTmp.month() == qdFecha.month()) {

        if(iCol > 6){
            iCol = 0;
            iFila++;
        }

        if(qdFecha == qdFechaTmp){
            iPos.append(iFila);
            iPos.append(iCol);
            qdFechaTmp = qdFechaTmp.addMonths(1);
        }

        qdFechaTmp = qdFechaTmp.addDays(1);
        iCol++;
    }

    return iPos;
}
