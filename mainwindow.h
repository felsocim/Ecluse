#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <stdlib.h>
#include "vanne.h"

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
    bool urgence;

private slots:
    void etat_vanne_amont(bool etat);
    void changer_vanne_amont();
    void niveau_eau_sas_amont(int niveau_sas);
    void niveau_eau_sas_aval(int niveau_sas);
    void etat_vanne_aval(bool etat);
    void changer_vanne_aval();
    void arret_urgence();
};

#endif // MAINWINDOW_H
