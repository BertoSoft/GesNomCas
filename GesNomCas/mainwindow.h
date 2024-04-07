#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplashScreen>
#include <QProgressBar>
#include <QLabel>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);        
    ~MainWindow();

    //
    // Controles Globales
    //
    QLabel  *lblTexto       = new QLabel();
    QLabel  *lblHora        = new QLabel();
    QLabel  *lblFecha       = new QLabel();

    //
    // Funciones Públicas
    //
    void initUi();
    void initSplash(QSplashScreen *splash, QProgressBar *progress);
    void initBarraEstado();
    void compruebaActions();
    void initLogin();
    void initReloj();
    void toLogin();
    void toRegistro();
    bool existeData();
    void refrescaReloj();
    void salir();

protected:

    bool eventFilter(QObject *obj, QEvent *ev);

private slots:

    void on_actionSalir_triggered();

    void on_actionImportar_Archivo_de_Datos_triggered();

    void on_actionImportar_Archivo_de_Incidencias_triggered();

    void on_actionExportar_Archivo_de_Datos_triggered();

    void on_actionExportar_Archivo_de_Incidencias_triggered();

    void on_actionDatos_Personales_triggered();

    void on_actionDatos_Centro_Trabajo_triggered();

    void on_actionDatos_Empleado_triggered();

    void on_actionRegistro_Unidades_N_mina_triggered();

    void on_actionRegistro_D_as_Festivos_triggered();

    void on_actionRegistro_Vacaciones_triggered();

    void on_actionCalendario_Laboral_triggered();

    void on_actionCrear_N_mina_triggered();

    void on_actionCargar_Nomina_triggered();

    void on_actionModificar_Incidencias_triggered();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
