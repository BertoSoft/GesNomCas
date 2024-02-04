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
    QString nombre_programa = "GesNomCas V 1.0";
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
    void toLogin();
    void toRegistro();
    bool existeData();
    bool existeDb();
    bool crearDb(QString ruta_db);
    void refrescaReloj();
    void salir();

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
