#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <stdlib.h>
#include "vanne.h"
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
    Vanne * vanneAmont;
    Vanne * vanneAval;
    Porte * porteAmont;
    Porte * porteAval;
    Signalisation * entAmont;
    Signalisation * entAval;
    Signalisation * sasAmont;
    Signalisation * sasAval;
    bool urgence;

private slots:
    void etat_vanne_amont(bool etat);
    void changer_vanne_amont();
    void niveau_eau_sas_amont(int niveau_sas);
    void niveau_eau_sas_aval(int niveau_sas);
    void etat_vanne_aval(bool etat);
    void changer_vanne_aval();
    void arret_urgence();
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
