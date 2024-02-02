#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplashScreen>
#include <QProgressBar>

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
    // Funciones
    //
    void inicio();
    void iniciarSplash(QSplashScreen *splash, QProgressBar *progress);
    bool existeData();
    void crearData();
    bool existeDbGesNomCas();
    void crearDb();
    void cerrarSplash(QSplashScreen *splash);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
