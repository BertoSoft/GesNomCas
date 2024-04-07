#include "cargarnomina.h"
#include "ui_cargarnomina.h"

#include "funcaux.h"

#include <QDate>

CargarNomina::CargarNomina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CargarNomina){

    ui->setupUi(this);

    initTable();
    initUi();
}

CargarNomina::~CargarNomina(){
    delete ui;
}

void CargarNomina::on_btnCancelar_clicked(){

    this->close();
}

void CargarNomina::initTable(){

    //
    // Colocamos las columnas del tablelist
    //
    ui->tableNomina->setColumnCount(6);

    QStringList headers;
    headers += tr("Cpto");
    headers += tr("Clave");
    headers += tr("Denominación");
    headers += tr("Cantidad");
    headers += tr("Precio");
    headers += tr("Importe");

    ui->tableNomina->setHorizontalHeaderLabels(headers);

    ui->tableNomina->setColumnWidth(0, (int) ( ( this->width() * 0.45) / 6 ) );
    ui->tableNomina->setColumnWidth(1, (int) ( ( this->width() * 0.80) / 6 ) );
    ui->tableNomina->setColumnWidth(2, (int) ( ( this->width() * 2) / 6 ) );
    ui->tableNomina->setColumnWidth(3, (int) ( ( this->width() * 0.80) / 6 ) );
    ui->tableNomina->setColumnWidth(4, (int) ( ( this->width() * 0.80) / 6 ) );
    ui->tableNomina->setColumnWidth(5, (int) ( ( this->width() * 0.80) / 6 ) );

}

void CargarNomina::initUi(){
    QList<FuncAux::DatosNomina>     listaNominas;
    QList<FuncAux::DatosNomina>     listaNomina;
    FuncAux::DatosNomina            dato;
    FuncAux::DatosEmpleado          datosEmpleado;
    QString                         str;
    QDate                           qdFecha;
    int                             i       = 0;
    int                             iFila   = 0;
    double                          dTipoCCEmpresarial;
    double                          dTipoAcEcEmpresarial;
    double                          dTipoDesempleoEmpresarial;
    double                          dTipoFormacionEmpresarial;
    double                          dTipoFogasaEmpresarial;
    double                          dtipoMeiEmpresarial;
    double                          dSumaSalario;
    double                          dSumaIrpf;
    double                          dSumaGastos;

    //
    // Obtenemos todas las nominas
    //
    listaNominas = FuncAux().getAllDatosNominas();

    //
    //Borramos todas las que no sean la buscada
    //
    i = 0;
    while (i < listaNominas.count()) {

        if(listaNominas[i].strAno == strAno && listaNominas[i].strMes == strMes){

            dato.strAno                     = listaNominas[i].strAno;
            dato.strMes                     = listaNominas[i].strMes;
            dato.codigo                     = listaNominas[i].codigo;
            dato.clave                      = listaNominas[i].clave;
            dato.denominacion               = listaNominas[i].denominacion;
            dato.cantidad                   = listaNominas[i].cantidad;
            dato.precio                     = listaNominas[i].precio;
            dato.importe                    = listaNominas[i].importe;
            dato.strRenumeracion            = listaNominas[i].strRenumeracion;
            dato.strRemuneracionPE          = listaNominas[i].strRemuneracionPE;
            dato.strProrrateo               = listaNominas[i].strProrrateo;
            dato.strDeducciones             = listaNominas[i].strDeducciones;
            dato.strIrpf                    = listaNominas[i].strIrpf;
            dato.strTipoCCEmpresa           = listaNominas[i].strTipoCCEmpresa;
            dato.strTipoATEPEmpresa         = listaNominas[i].strTipoATEPEmpresa;
            dato.strTipoDesempleoEmpresa    = listaNominas[i].strTipoDesempleoEmpresa;
            dato.strTipoFormacionEmpresa    = listaNominas[i].strTipoFormacionEmpresa;
            dato.strTipoFogasaEmpresa       = listaNominas[i].strTipoFogasaEmpresa;
            dato.strTipoMeiEmpresa          = listaNominas[i].strTipoMeiEmpresa;
            dato.strSumaSalarioBruto        = listaNominas[i].strSumaSalarioBruto;
            dato.strSumaIrpf                = listaNominas[i].strSumaIrpf;
            dato.strSumaGastosDeducibles    = listaNominas[i].strSumaGastosDeducibles;

            listaNomina.append(dato);
        }

        i++;
    }

    qdFecha.setDate(strAno.toInt(), FuncAux().strMesToInt(strMes), 1);
    //
    // Rellenamos los datos de la nomina
    //
    str = "Nómina de ";
    str.append(strMes);
    ui->lblNomina->setText(str);

    ui->lblTipo->setText("Mensual");

    str = "Del  ";
    str.append(FuncAux().dateToFechaCorta(qdFecha));
    str.append("  al  ");
    qdFecha.setDate(qdFecha.year(), qdFecha.month(), qdFecha.daysInMonth());
    str.append(FuncAux().dateToFechaCorta(qdFecha));
    ui->lblPeriodo->setText(str);

    ui->lblDiasTotales->setText(QString::number(qdFecha.daysInMonth()));

    //
    // Rellenamos los datos del empleado
    //
    datosEmpleado = FuncAux().getDatosEmpleado();

    ui->lblEmpleado->setText(datosEmpleado.empleado);
    ui->lblCategoria->setText(datosEmpleado.categoria);
    ui->lblIngreso->setText(datosEmpleado.ingreso);
    ui->lblNif->setText(datosEmpleado.nif);
    ui->lblPuesto->setText(datosEmpleado.puesto);

    //
    // Rellenamos la tabla
    //
    i       = 1;
    iFila   = 0;
    while (i < listaNomina.count()) {

        ui->tableNomina->setRowCount(iFila + 1);

        QTableWidgetItem *itemCodigo        = new QTableWidgetItem(listaNomina[i].codigo);
        QTableWidgetItem *itemClave         = new QTableWidgetItem(listaNomina[i].clave);
        QTableWidgetItem *itemDenominacion  = new QTableWidgetItem(listaNomina[i].denominacion);
        QTableWidgetItem *itemCantidad      = new QTableWidgetItem(listaNomina[i].cantidad);
        QTableWidgetItem *itemPrecio        = new QTableWidgetItem(listaNomina[i].precio);
        QTableWidgetItem *itemImporte       = new QTableWidgetItem(listaNomina[i].importe);

        itemCodigo->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemClave->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        itemDenominacion->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        itemCantidad->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        itemPrecio->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        itemImporte->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        ui->tableNomina->setItem(iFila, 0, itemCodigo);
        ui->tableNomina->setItem(iFila, 1, itemClave);
        ui->tableNomina->setItem(iFila, 2, itemDenominacion);
        ui->tableNomina->setItem(iFila, 3, itemCantidad);
        ui->tableNomina->setItem(iFila, 4, itemPrecio);
        ui->tableNomina->setItem(iFila, 5, itemImporte);

        iFila++;

        i++;
    }

    //
    // Obtengo los valores
    //
    if(listaNomina.count() > 0){

        dRemuneracion           = listaNomina[0].strRenumeracion.toDouble();
        dRemuneracionPE         = listaNomina[0].strRemuneracionPE.toDouble();
        dProrrateoPagasExtra    = listaNomina[0].strProrrateo.toDouble();
        dBaseCotizacion         = dRemuneracion + dProrrateoPagasExtra;
        dDeducciones            = listaNomina[0].strDeducciones.toDouble();
        dIrpf                   = listaNomina[0].strIrpf.toDouble();

        dTipoCCEmpresarial          = listaNomina[0].strTipoCCEmpresa.toDouble();
        dTipoAcEcEmpresarial        = listaNomina[0].strTipoATEPEmpresa.toDouble();
        dTipoDesempleoEmpresarial   = listaNomina[0].strTipoDesempleoEmpresa.toDouble();
        dTipoFormacionEmpresarial   = listaNomina[0].strTipoFormacionEmpresa.toDouble();
        dTipoFogasaEmpresarial      = listaNomina[0].strTipoFogasaEmpresa.toDouble();
        dtipoMeiEmpresarial         = listaNomina[0].strTipoMeiEmpresa.toDouble();

        dSumaSalario    = listaNomina[0].strSumaSalarioBruto.toDouble();;
        dSumaIrpf       = listaNomina[0].strSumaIrpf.toDouble();;
        dSumaGastos     = listaNomina[0].strSumaGastosDeducibles.toDouble();;

    }

    //
    // Relleno la base de cotizacion
    //
    ui->lblRemuneracion->setText(QLocale().toCurrencyString(dRemuneracion));
    ui->lblProrrata->setText(QLocale().toCurrencyString(dProrrateoPagasExtra));
    ui->lblTotal->setText(QLocale().toCurrencyString(dRemuneracion + dProrrateoPagasExtra));
    ui->lblBaseIrpf->setText(QLocale().toCurrencyString(dRemuneracion + dRemuneracionPE));

    //
    // Cotizaciones empresariales
    //
    ui->lblBaseSS1->setText(QLocale().toCurrencyString(dBaseCotizacion));
    ui->lblBaseSS2->setText(QLocale().toCurrencyString(dBaseCotizacion));
    ui->lblBaseSS3->setText(QLocale().toCurrencyString(dBaseCotizacion));
    ui->lblBaseSS4->setText(QLocale().toCurrencyString(dBaseCotizacion));
    ui->lblBaseSS5->setText(QLocale().toCurrencyString(dBaseCotizacion));
    ui->lblBaseSS6->setText(QLocale().toCurrencyString(dBaseCotizacion));

    ui->lblTipoCC->setText(QString::number(dTipoCCEmpresarial * 100) + " %");
    ui->lblTipoATEP->setText(QString::number(dTipoAcEcEmpresarial * 100) + " %");
    ui->lbllblTipoDesempleo->setText(QString::number(dTipoDesempleoEmpresarial * 100) + " %");
    ui->lblTipoFP->setText(QString::number(dTipoFormacionEmpresarial * 100) + " %");
    ui->lblTipoFGS->setText(QString::number(dTipoFogasaEmpresarial * 100) + " %");
    ui->lblTipoMei->setText(QString::number(dtipoMeiEmpresarial * 100) + " %");

    ui->lblCC->setText(QLocale().toCurrencyString(dBaseCotizacion * dTipoCCEmpresarial));
    ui->lblATEP->setText(QLocale().toCurrencyString(dBaseCotizacion * dTipoAcEcEmpresarial));
    ui->lblDesempleo->setText(QLocale().toCurrencyString(dBaseCotizacion * dTipoDesempleoEmpresarial));
    ui->lblFP->setText(QLocale().toCurrencyString(dBaseCotizacion * dTipoFormacionEmpresarial));
    ui->lblFGS->setText(QLocale().toCurrencyString(dBaseCotizacion * dTipoFogasaEmpresarial));
    ui->lblMei->setText(QLocale().toCurrencyString(dBaseCotizacion * dtipoMeiEmpresarial));

    //
    // Los Acumulados
    //
    ui->lblSumaSalarioBruto->setText(QLocale().toCurrencyString(dSumaSalario));
    ui->lblSumaIrpf->setText(QLocale().toCurrencyString(dSumaIrpf));
    ui->lblSumaGastosDeducibles->setText(QLocale().toCurrencyString(dSumaGastos));

    //
    // Ahora el liquido
    //
    ui->lblDevengos->setText(QLocale().toCurrencyString(dRemuneracion + dRemuneracionPE));
    ui->lblDeducciones->setText(QLocale().toCurrencyString(dDeducciones + dIrpf));
    ui->lblLiquido->setText(QLocale().toCurrencyString( dRemuneracion + dRemuneracionPE - (dDeducciones + dIrpf)));
    ui->lblPagar->setText(QLocale().toCurrencyString( dRemuneracion + dRemuneracionPE - (dDeducciones + dIrpf)));

















    //
    // Tenemos la nomina en listaNomina
    //



























}


