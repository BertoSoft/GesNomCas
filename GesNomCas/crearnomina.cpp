#include "crearnomina.h"
#include "ui_crearnomina.h"

#include "precrearnomina.h"
#include "funcaux.h"

#include <QDate>
#include <QLocale>

CrearNomina::CrearNomina(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CrearNomina){

    ui->setupUi(this);

    initTable();
    initUi();
}

CrearNomina::~CrearNomina(){

    delete ui;
}

void CrearNomina::initTable(){

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

void CrearNomina::initUi(){
    QDate                   qdFecha;
    QString                 str;
    FuncAux::DatosEmpleado  datosEmpleado;
    QList<DatosNomina>      listaNomina;
    int                     i                           = 0;
    int                     iFila                       = 0;
    double                  dTipoCCEmpresarial          = 0.236;
    double                  dTipoAcEcEmpresarial        = 0.0715;
    double                  dTipoDesempleoEmpresarial   = 0.055;
    double                  dTipoFormacionEmpresarial   = 0.006;
    double                  dTipoFogasaEmpresarial      = 0.002;
    double                  dtipoMeiEmpresarial         = 0.0058;

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

    ui->lblDiasTotales->setText(strDiasTotales);

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
    // Ahora relleno la nomina
    //
    listaNomina = getListaNomina();

    i       = 0;
    iFila   = 0;
    while (i < listaNomina.count()) {
        if(listaNomina[i].cantidad.toDouble() >= 0.0){
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
        }

        i++;
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
    ui->lblSumaSalarioBruto->setText(QLocale().toCurrencyString(FuncAux().getAcumuladoSalarioBruto(strAno)));
    ui->lblSumaIrpf->setText(QLocale().toCurrencyString(FuncAux().getAcumuladoIrpf(strAno)));
    ui->lblSumaGastosDeducibles->setText(QLocale().toCurrencyString(FuncAux().getAcumuladoGastosDeducibles(strAno)));

    //
    // Ahora el liquido
    //
    ui->lblDevengos->setText(QLocale().toCurrencyString(dRemuneracion + dRemuneracionPE));
    ui->lblDeducciones->setText(QLocale().toCurrencyString(dDeducciones + dIrpf));
    ui->lblLiquido->setText(QLocale().toCurrencyString( dRemuneracion + dRemuneracionPE - (dDeducciones + dIrpf)));
    ui->lblPagar->setText(QLocale().toCurrencyString( dRemuneracion + dRemuneracionPE - (dDeducciones + dIrpf)));

}

void CrearNomina::salir(){

    this->close();
}

QList<CrearNomina::DatosNomina> CrearNomina::getListaNomina(){
    DatosNomina                         lineaNomina;
    QList<DatosNomina>                  listaNomina;
    FuncAux::DatosRetribuciones         datos;
    double                              dCantidad;
    double                              dPrecio;
    double                              dImporte = 0.0;
    QString                             str;
    QDate                               qdFecha;

    //
    // Devengos
    //
    lineaNomina.codigo          = "";
    lineaNomina.clave           = "";
    lineaNomina.denominacion    = "DEVENGOS";
    lineaNomina.cantidad        = "";
    lineaNomina.precio          = "";
    lineaNomina.importe         = "";

    listaNomina.append(lineaNomina);

    //
    // Si es paga extra colocamos el periodo del mes
    //
    if(strMes == "Febrero" || strMes == "Junio" || strMes == "Diciembre"){
        qdFecha.setDate(strAno.toInt(), FuncAux().strMesToInt(strMes), 1);
        str = "De ";
        str.append(FuncAux().dateToFechaCorta(qdFecha));
        qdFecha.setDate(qdFecha.year(), qdFecha.month(), qdFecha.daysInMonth());
        str.append(" a ");
        str.append(FuncAux().dateToFechaCorta(qdFecha));

        lineaNomina.codigo          = "";
        lineaNomina.clave           = "";
        lineaNomina.denominacion    = str;
        lineaNomina.cantidad        = "";
        lineaNomina.precio          = "";
        lineaNomina.importe         = "";

        listaNomina.append(lineaNomina);
    }

    //
    // Salario base
    //
    datos       = getRetribucion("5.00");

    dCantidad   = strDiasTotales.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Antiguedad
    //
    datos       = getRetribucion("6.00");

    dCantidad   = strDiasTotales.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Transportes
    //
    datos       = getRetribucion("10.00");

    dCantidad   = strTransportes.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Asistencias
    //
    datos       = getRetribucion("30.00");

    dCantidad   = strAsistencias.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Turnucidad
    //
    datos       = getRetribucion("70.00");

    dCantidad   = strTurnicidad.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Hed
    //
    datos       = getRetribucion("80.00");

    dCantidad   = strHed.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Hen
    //
    datos       = getRetribucion("81.00");

    dCantidad   = strHen.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Hef
    //
    datos       = getRetribucion("82.00");

    dCantidad   = strHef.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Toxicos
    //
    datos       = getRetribucion("90.00");

    dCantidad   = strToxicos.toDouble();
    dPrecio     = datos.cuantia.toDouble();
    dImporte    = dCantidad * dPrecio;

    if(dImporte == 0.0){dCantidad = -1;}

    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = QString::number(dCantidad);
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dRemuneracion += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Si es paga extra febrero
    //
    if(strMes == "Febrero"){
        qdFecha.setDate(strAno.toInt(), 1, 1);
        str = "De  ";
        str.append(FuncAux().dateToFechaCorta(qdFecha));
        str.append("  a  ");
        qdFecha.setDate(strAno.toInt(), 12, 31);
        str.append(str);

        lineaNomina.codigo          = "";
        lineaNomina.clave           = "";
        lineaNomina.denominacion    = str;
        lineaNomina.cantidad        = "";
        lineaNomina.precio          = "";
        lineaNomina.importe         = "";

        listaNomina.append(lineaNomina);
    }

    //
    // Si es paga extra Junio
    //
    if(strMes == "Junio"){
        qdFecha.setDate(strAno.toInt(), 1, 1);
        str = "De  ";
        str.append(FuncAux().dateToFechaCorta(qdFecha));
        str.append("  a  ");
        qdFecha.setDate(strAno.toInt(), 6, 30);
        str.append(str);

        lineaNomina.codigo          = "";
        lineaNomina.clave           = "";
        lineaNomina.denominacion    = str;
        lineaNomina.cantidad        = "";
        lineaNomina.precio          = "";
        lineaNomina.importe         = "";

        listaNomina.append(lineaNomina);
    }

    //
    // Si es paga extra Diciembre
    //
    if(strMes == "Diciembre"){
        qdFecha.setDate(strAno.toInt(), 7, 1);
        str = "De  ";
        str.append(FuncAux().dateToFechaCorta(qdFecha));
        str.append("  a  ");
        qdFecha.setDate(strAno.toInt(), 12, 31);
        str.append(str);

        lineaNomina.codigo          = "";
        lineaNomina.clave           = "";
        lineaNomina.denominacion    = str;
        lineaNomina.cantidad        = "";
        lineaNomina.precio          = "";
        lineaNomina.importe         = "";

        listaNomina.append(lineaNomina);
    }

    //
    // Ahora las lineas de Paga extra, empezando por salario base PE
    //
    if(strMes == "Febrero"){
        datos = getRetribucion("503.50");
    }
    if(strMes == "Junio"){
        datos = getRetribucion("507.50");
    }
    if(strMes == "Diciembre"){
        datos = getRetribucion("512.50");
    }

    if(strMes == "Febrero" || strMes == "Junio" || strMes == "Diciembre"){

        dCantidad   = 30.00;
        dPrecio     = datos.cuantia.toDouble();
        dImporte    = dCantidad * dPrecio;

        lineaNomina.codigo          = datos.codigo;
        lineaNomina.clave           = datos.clave;
        lineaNomina.denominacion    = datos.denominacion;
        lineaNomina.cantidad        = QString::number(dCantidad);
        lineaNomina.precio          = QString::number(dPrecio);
        lineaNomina.importe         = QString::number(dImporte, 'f', 2);

        dRemuneracionPE += dImporte;
        listaNomina.append(lineaNomina);

    }

    //
    // Antiguedad PagaExtra
    //
    if(strMes == "Febrero"){
        datos = getRetribucion("503.60");
    }
    if(strMes == "Junio"){
        datos = getRetribucion("507.60");
    }
    if(strMes == "Diciembre"){
        datos = getRetribucion("512.60");
    }

    if(strMes == "Febrero" || strMes == "Junio" || strMes == "Diciembre"){

        dCantidad   = 30.00;
        dPrecio     = datos.cuantia.toDouble();
        dImporte    = dCantidad * dPrecio;

        lineaNomina.codigo          = datos.codigo;
        lineaNomina.clave           = datos.clave;
        lineaNomina.denominacion    = datos.denominacion;
        lineaNomina.cantidad        = QString::number(dCantidad);
        lineaNomina.precio          = QString::number(dPrecio);
        lineaNomina.importe         = QString::number(dImporte, 'f', 2);

        dRemuneracionPE += dImporte;
        listaNomina.append(lineaNomina);

    }

    //
    // Bolsa Vacaciones Paga extra
    //
    if(strMes == "Febrero"){
        datos = getRetribucion("503.70");
    }
    if(strMes == "Junio"){
        datos = getRetribucion("507.70");
    }
    if(strMes == "Diciembre"){
        datos = getRetribucion("512.70");
    }

    if(strMes == "Febrero" || strMes == "Junio" || strMes == "Diciembre"){

        dCantidad   = 30.00;
        dPrecio     = datos.cuantia.toDouble();
        dImporte    = dCantidad * dPrecio;

        lineaNomina.codigo          = datos.codigo;
        lineaNomina.clave           = datos.clave;
        lineaNomina.denominacion    = datos.denominacion;
        lineaNomina.cantidad        = QString::number(dCantidad);
        lineaNomina.precio          = QString::number(dPrecio);
        lineaNomina.importe         = QString::number(dImporte, 'f', 2);

        dRemuneracionPE += dImporte;
        listaNomina.append(lineaNomina);

    }

    //
    // Claculamos la base de cotización
    //
    dProrrateoPagasExtra = strCteProrrateo.toDouble() * strDiasTotales.toDouble();
    dBaseCotizacion = dRemuneracion + dProrrateoPagasExtra;

    //
    // Linea en blanco solo si no es paga extra
    //
    lineaNomina.codigo          = "";
    lineaNomina.clave           = "";
    lineaNomina.denominacion    = "";
    lineaNomina.cantidad        = "";
    lineaNomina.precio          = "";
    lineaNomina.importe         = "";

    listaNomina.append(lineaNomina);

    //
    // Deducciones
    //
    lineaNomina.codigo          = "";
    lineaNomina.clave           = "";
    lineaNomina.denominacion    = "DEDUCCIONES";
    lineaNomina.cantidad        = "";
    lineaNomina.precio          = "";
    lineaNomina.importe         = "";

    listaNomina.append(lineaNomina);

    //
    // Contingencias comunes
    //
    datos       = getRetribucion("900.00");

    dCantidad   = datos.cuantia.toDouble() * 0.01;
    dPrecio     = dBaseCotizacion;
    dImporte    = dCantidad * dPrecio;


    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = datos.cuantia + " %";
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dDeducciones += dImporte;
    listaNomina.append(lineaNomina);

    //
    // MEI
    //
    datos       = getRetribucion("900.02");

    dCantidad   = datos.cuantia.toDouble() * 0.01;
    dPrecio     = dBaseCotizacion;
    dImporte    = dCantidad * dPrecio;


    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = datos.cuantia + " %";
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dDeducciones += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Desempleo
    //
    datos       = getRetribucion("901.00");

    dCantidad   = datos.cuantia.toDouble() * 0.01;
    dPrecio     = dBaseCotizacion;
    dImporte    = dCantidad * dPrecio;


    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = datos.cuantia + " %";
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dDeducciones += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Formación
    //
    datos       = getRetribucion("902.00");

    dCantidad   = datos.cuantia.toDouble() * 0.01;
    dPrecio     = dBaseCotizacion;
    dImporte    = dCantidad * dPrecio;


    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = datos.cuantia + " %";
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dDeducciones += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Retencion IRPF
    //
    datos       = getRetribucion("911.00");

    dCantidad   = datos.cuantia.toDouble() * 0.01;
    dPrecio     = dRemuneracion;
    dImporte    = dCantidad * dPrecio;


    lineaNomina.codigo          = datos.codigo;
    lineaNomina.clave           = datos.clave;
    lineaNomina.denominacion    = datos.denominacion;
    lineaNomina.cantidad        = datos.cuantia + " %";
    lineaNomina.precio          = QString::number(dPrecio);
    lineaNomina.importe         = QString::number(dImporte, 'f', 2);

    dIrpf += dImporte;
    listaNomina.append(lineaNomina);

    //
    // Retencion IRPF, Pagas Extras
    //
    if(dRemuneracionPE > 0){

        datos       = getRetribucion("911.00");

        dCantidad   = datos.cuantia.toDouble() * 0.01;
        dPrecio     = dRemuneracionPE;
        dImporte    = dCantidad * dPrecio;


        lineaNomina.codigo          = datos.codigo;
        lineaNomina.clave           = datos.clave;
        lineaNomina.denominacion    = datos.denominacion;
        lineaNomina.cantidad        = datos.cuantia + " %";
        lineaNomina.precio          = QString::number(dPrecio);
        lineaNomina.importe         = QString::number(dImporte, 'f', 2);

        dIrpf += dImporte;
        listaNomina.append(lineaNomina);
    }

    return listaNomina;
}

FuncAux::DatosRetribuciones CrearNomina::getRetribucion(QString strCodigo){
    QList<FuncAux::DatosRetribuciones>  listaRetribuciones;
    FuncAux::DatosRetribuciones         datos;
    int                                 i               = 0;
    listaRetribuciones = FuncAux().getAllRetribuciones();

    while (i< listaRetribuciones.count()) {
        if(listaRetribuciones[i].codigo == strCodigo){

            datos.clave         = listaRetribuciones[i].clave;
            datos.codigo        = listaRetribuciones[i].codigo;
            datos.denominacion  = listaRetribuciones[i].denominacion;
            datos.cuantia       = listaRetribuciones[i].cuantia;

            i = listaRetribuciones.count();
        }
        i++;
    }

    return datos;
}

void CrearNomina::on_btnCancelar_clicked(){

    salir();
}

