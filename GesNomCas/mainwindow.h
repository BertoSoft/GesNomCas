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
    QString nombrePrograma = "GesNomCas V 1.0";
    QLabel  *lblTexto       = new QLabel();
    QLabel  *lblHora        = new QLabel();
    QLabel  *lblFecha       = new QLabel();

    //
    // Funciones Públicas
    //
    void initUi();
    void initSplash(QSplashScreen *splash, QProgressBar *progress);
    void initBarraEstado();
    void initLogin();
    void initReloj();
    void toLogin();
    void toRegistro();
    bool existeData();
    bool existeDb();
    void refrescaReloj();
    void salir();

protected:

    bool eventFilter(QObject *obj, QEvent *ev);

private slots:
    void on_actionSalir_triggered();

    void on_actionImportar_Archivo_de_Datos_triggered();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
