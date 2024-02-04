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
    // Funciones Públicas
    //
    void initUi();
    void initSplash(QSplashScreen *splash, QProgressBar *progress);
    void initBarraEstado();
    void initLogin();
    bool existeData();
    bool existeDb();
    bool crearDb(QString ruta_db);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
