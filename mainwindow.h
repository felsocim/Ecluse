#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <stdlib.h>
#include "vanne.h"
#include "porte.h"
#include "signalisation.h"
#include "panne.h"
#include "sequence.h"
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

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
    Panne * panne;
    bool urgence;
    bool maintenance;
    void basculerManuel(bool etat);
    sequence * timer;
    sequence * timer2;
    sequence * timer3;
    sequence * timer4;
    sequence * timer5;
    sequence * timer6;

private slots:
    void etat_vanne_amont(bool etat);
    void changer_vanne_amont();
    void niveau_eau_sas_amont(int niveau_sas);
    void niveau_eau_sas_aval(int niveau_sas);
    void etat_vanne_aval(bool etat);
    void alarme_vanne_amont(bool alarme);
    void alarme_vanne_aval(bool alarme);
    void alarme_porte_amont(bool alarme);
    void alarme_porte_aval(bool alarme);
    void changer_vanne_aval();
    void arret_urgence();
    void panne_aleatoire(int value);
    void echangeFeuManuelSigEntAmont();
    void echangeFeuManuelSigEntAval();
    void echangeFeuManuelSigSasAmont();
    void echangeFeuManuelSigSasAval();
    void lancementPorteAmont();
    void lancementPorteAval();
    void echangePorteAmont(int);
    void echangePorteAval(int);
    void fin_cycle_porte_amont(bool etat);
    void fin_cycle_porte_aval(bool etat);
    void fin_cycle_vanne_amont(bool etat);
    void fin_cycle_vanne_aval(bool etat);
    void feuxEntreeAmont(bool value);
    void feuxSasAmont(bool value);
    void feuxEntreeAval(bool value);
    void feuxSasAval(bool value);

    void echangeModes();
    void autoMontant();


    void auto_remise_a_niveau();
    void auto_ouvrir_porte_amont();
    void auto_changement_etape();
    void auto_fermer_porte_amont();
    void auto_remise_a_niveau2();
    void auto_ouvrir_porte_aval();
    void auto_signal_sas_aval();
};

#endif // MAINWINDOW_H
