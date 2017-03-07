#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "porte.h"
#include "signalisation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Porte *porteAmont;
    Porte *porteAval;
    Signalisation *entAmont;
    Signalisation *entAval;
    Signalisation *sasAmont;
    Signalisation *sasAval;


private slots:
    void echangeFeuManuelSigEntAmont();
    void echangeFeuManuelSigEntAval();
    void echangeFeuManuelSigSasAmont();
    void echangeFeuManuelSigSasAval();
    void lancementPorteAmont();
    void lancementPorteAval();
    void echangePorteAmont(int);
    void echangePorteAval(int);
};

#endif // MAINWINDOW_H
