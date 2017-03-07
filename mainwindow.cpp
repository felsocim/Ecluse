#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    vanneAmont(new Vanne),
    vanneAval(new Vanne)
{
    ui->setupUi(this);

    vanneAmont->setNiveauEauExterieur(ui->aniNiveauAmont->height());
    vanneAmont->setNiveauEauPas(5);

    vanneAval->setNiveauEauExterieur(ui->aniNiveauAval->height());
    vanneAval->setNiveauEauPas(5);

    urgence = false;

    //Connexion slots
    QObject::connect(ui->btnManuelVannesAmont, SIGNAL(clicked(bool)), this, SLOT(changer_vanne_amont()));
    QObject::connect(vanneAmont, SIGNAL(signaler_etat(bool)), this, SLOT(etat_vanne_amont(bool)));
    QObject::connect(vanneAmont, SIGNAL(signaler_niveau_eau(int)), this, SLOT(niveau_eau_sas_amont(int)));

    QObject::connect(ui->btnManuelVannesAval, SIGNAL(clicked(bool)), this, SLOT(changer_vanne_aval()));
    QObject::connect(vanneAval, SIGNAL(signaler_etat(bool)), this, SLOT(etat_vanne_aval(bool)));
    QObject::connect(vanneAval, SIGNAL(signaler_niveau_eau(int)), this, SLOT(niveau_eau_sas_aval(int)));

    QObject::connect(ui->btnArretUrgenceMan, SIGNAL(clicked(bool)), this, SLOT(arret_urgence()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::arret_urgence()
{
    if(!urgence)
    {
        urgence = true;

        this->vanneAmont->declancher_alarme();
        this->vanneAval->declancher_alarme();

        ui->btnArretUrgenceMan->setText("EXTINCTION\nALARME");
        ui->btnArretUrgenceMan->setProperty("urgence", true);
        ui->btnArretUrgenceMan->style()->unpolish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->style()->polish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->update();
    }
    else
    {
        urgence = false;

        this->vanneAmont->extinction_alarme();
        this->vanneAval->extinction_alarme();

        ui->btnArretUrgenceMan->setText("ARRÊT\nURGENCE");
        ui->btnArretUrgenceMan->setProperty("urgence", false);
        ui->btnArretUrgenceMan->style()->unpolish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->style()->polish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->update();
    }
}

void MainWindow::niveau_eau_sas_amont(int niveau_sas)
{
    ui->aniNiveauSas->move(ui->aniNiveauSas->x(), ui->aniNiveauSas->y() + abs(ui->aniNiveauSas->height() - niveau_sas));
    ui->aniNiveauSas->resize(ui->aniNiveauSas->width(), niveau_sas);
}

void MainWindow::niveau_eau_sas_aval(int niveau_sas)
{
    ui->aniNiveauSas->move(ui->aniNiveauSas->x(), ui->aniNiveauSas->y() - abs(ui->aniNiveauSas->height() - niveau_sas));
    ui->aniNiveauSas->resize(ui->aniNiveauSas->width(), niveau_sas);
}

void MainWindow::changer_vanne_amont()
{
    vanneAmont->setNiveauEauSas(ui->aniNiveauSas->height());

    if(this->vanneAmont->isRunning())
    {
        this->vanneAmont->changer_etat();
    }
    else
    {
        this->vanneAmont->start();
    }
}

void MainWindow::changer_vanne_aval()
{
    vanneAval->setNiveauEauSas(ui->aniNiveauSas->height());

    if(this->vanneAval->isRunning())
    {
        this->vanneAval->changer_etat();
    }
    else
    {
        this->vanneAval->start();
    }
}

void MainWindow::etat_vanne_amont(bool etat)
{
    QPixmap image;

    if(etat)
    {
        image.load(":/EcluseAuto/vanne_ouverte.png");
        ui->btnManuelVannesAmont->setText("FERMER\nAMONT");
        ui->btnManuelVannesAmont->setProperty("fermer", true);
        ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->update();
        ui->aniVanneAmontOuverture->setPixmap(image);
    }
    else
    {
        image.load(":/EcluseAuto/vanne_fermee.png");
        ui->btnManuelVannesAmont->setText("OUVRIR\nAMONT");
        ui->btnManuelVannesAmont->setProperty("fermer", false);
        ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->update();
        ui->aniVanneAmontOuverture->setPixmap(image);
    }
}

void MainWindow::etat_vanne_aval(bool etat)
{
    QPixmap image;

    if(etat)
    {
        image.load(":/EcluseAuto/vanne_ouverte.png");
        ui->btnManuelVannesAval->setText("FERMER\nAVAL");
        ui->btnManuelVannesAval->setProperty("fermer", true);
        ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->update();
        ui->aniVanneAvalOuverture->setPixmap(image);
    }
    else
    {
        image.load(":/EcluseAuto/vanne_fermee.png");
        ui->btnManuelVannesAval->setText("OUVRIR\nAVAL");
        ui->btnManuelVannesAval->setProperty("fermer", false);
        ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->update();
        ui->aniVanneAvalOuverture->setPixmap(image);
    }
}
