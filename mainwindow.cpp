#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    vanneAmont(new Vanne),
    vanneAval(new Vanne),
    porteAmont(new Porte),
    porteAval(new Porte),
    entAmont(new Signalisation),
    entAval(new Signalisation),
    sasAmont(new Signalisation),
    sasAval(new Signalisation)
{
    ui->setupUi(this);

    vanneAmont->setNiveauEauPas(10);
    vanneAval->setNiveauEauPas(10);

    urgence = false;

    //Vannes
    QObject::connect(ui->btnManuelVannesAmont, SIGNAL(clicked(bool)), this, SLOT(changer_vanne_amont()));
    QObject::connect(vanneAmont, SIGNAL(signaler_etat(bool)), this, SLOT(etat_vanne_amont(bool)));
    QObject::connect(vanneAmont, SIGNAL(signaler_niveau_eau(int)), this, SLOT(niveau_eau_sas_amont(int)));
    QObject::connect(ui->btnManuelVannesAval, SIGNAL(clicked(bool)), this, SLOT(changer_vanne_aval()));
    QObject::connect(vanneAval, SIGNAL(signaler_etat(bool)), this, SLOT(etat_vanne_aval(bool)));
    QObject::connect(vanneAval, SIGNAL(signaler_niveau_eau(int)), this, SLOT(niveau_eau_sas_aval(int)));

    //Etat d'urgence (mode manuel)
    QObject::connect(ui->btnArretUrgenceMan, SIGNAL(clicked(bool)), this, SLOT(arret_urgence()));

    //Signalisation
    QObject::connect(ui->btnManuelSigEntAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigEntAmont()));
    QObject::connect(ui->btnManuelSigEntAval, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigEntAval()));
    QObject::connect(ui->btnManuelSigSasAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigSasAmont()));
    QObject::connect(ui->btnManuelSigSasAval, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigSasAval()));

    //Porte Amont
    QObject::connect(porteAmont, SIGNAL(transition(int)), this, SLOT(echangePorteAmont(int)));
    QObject::connect(ui->btnManuelPortesAmont, SIGNAL(clicked(bool)), this, SLOT(lancementPorteAmont()));

    //Porte Aval
    QObject::connect(porteAval, SIGNAL(transition(int)), this, SLOT(echangePorteAval(int)));
    QObject::connect(ui->btnManuelPortesAval, SIGNAL(clicked(bool)), this, SLOT(lancementPorteAval()));
}

MainWindow::~MainWindow()
{
    vanneAmont->terminate();
    vanneAmont->wait();
    delete vanneAmont;

    vanneAval->terminate();
    vanneAval->wait();
    delete vanneAval;

    porteAmont->terminate();
    porteAmont->wait();
    delete porteAmont;

    porteAval->terminate();
    porteAval->wait();
    delete porteAval;

    entAmont->terminate();
    entAmont->wait();
    delete entAmont;

    entAval->terminate();
    entAval->wait();
    delete entAval;

    sasAmont->terminate();
    sasAmont->wait();
    delete sasAmont;

    sasAval->terminate();
    sasAval->wait();
    delete sasAval;

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
    ui->aniNiveauSas->move(ui->aniNiveauSas->x(), ui->aniNiveauSas->y() - abs(ui->aniNiveauSas->height() - niveau_sas));
    ui->aniNiveauSas->resize(ui->aniNiveauSas->width(), niveau_sas);
}

void MainWindow::niveau_eau_sas_aval(int niveau_sas)
{
    ui->aniNiveauSas->move(ui->aniNiveauSas->x(), ui->aniNiveauSas->y() + abs(ui->aniNiveauSas->height() - niveau_sas));
    ui->aniNiveauSas->resize(ui->aniNiveauSas->width(), niveau_sas);
}

void MainWindow::changer_vanne_amont()
{
    if(vanneAval->getEtat())
    {
        vanneAmont->setNiveauEauExterieur(ui->aniNiveauAmont->height() / 2);
    }
    else
    {
        vanneAmont->setNiveauEauExterieur(ui->aniNiveauAmont->height());
    }

    vanneAmont->setNiveauEauSas(ui->aniNiveauSas->height());

    this->vanneAmont->start();
}

void MainWindow::changer_vanne_aval()
{
    if(vanneAmont->getEtat())
    {
        vanneAval->setNiveauEauExterieur(ui->aniNiveauAmont->height() / 2);
    }
    else
    {
        vanneAval->setNiveauEauExterieur(ui->aniNiveauAval->height());
    }

    vanneAval->setNiveauEauSas(ui->aniNiveauSas->height());

    this->vanneAval->start();
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

void MainWindow::echangeFeuManuelSigEntAmont()
{
    this->entAmont->start();
    QPixmap image;

    if ( this->entAmont->get_couleur())
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigEntAmont->setText("ROUGE\nEN AMONT");
        ui->btnManuelSigEntAmont->setProperty("arret", true);
        ui->btnManuelSigEntAmont->style()->unpolish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->style()->polish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->update();
    }
    else
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigEntAmont->setText("VERT\nEN AMONT");
        ui->btnManuelSigEntAmont->setProperty("arret", false);
        ui->btnManuelSigEntAmont->style()->unpolish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->style()->polish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->update();
    }

    ui->aniFeuEntreeAmont->setPixmap(image);
}

void MainWindow::echangeFeuManuelSigEntAval()
{
    this->entAval->start();
    QPixmap image;

    if ( this->entAval->get_couleur())
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigEntAval->setText("ROUGE\nEN AVAL");
        ui->btnManuelSigEntAval->setProperty("arret", true);
        ui->btnManuelSigEntAval->style()->unpolish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->style()->polish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->update();
    }
    else
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigEntAval->setText("VERT\nEN AVAL");
        ui->btnManuelSigEntAval->setProperty("arret", false);
        ui->btnManuelSigEntAval->style()->unpolish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->style()->polish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->update();
    }

    ui->aniFeuEntreeAval->setPixmap(image);
}

void MainWindow::echangeFeuManuelSigSasAmont()
{
    this->sasAmont->start();
    QPixmap image;

    if ( this->sasAmont->get_couleur())
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigSasAmont->setText("ROUGE\nEN AMONT");
        ui->btnManuelSigSasAmont->setProperty("arret", true);
        ui->btnManuelSigSasAmont->style()->unpolish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->style()->polish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->update();
    }
    else
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigSasAmont->setText("VERT\nEN AMONT");
        ui->btnManuelSigSasAmont->setProperty("arret", false);
        ui->btnManuelSigSasAmont->style()->unpolish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->style()->polish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->update();
    }

    ui->aniFeuSasAmont->setPixmap(image);
}

void MainWindow::echangeFeuManuelSigSasAval()
{
    this->sasAval->start();
    QPixmap image;

    if ( this->sasAval->get_couleur())
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigSasAval->setText("ROUGE\nEN AVAL");
        ui->btnManuelSigSasAval->setProperty("fermer", true);
        ui->btnManuelSigSasAval->style()->unpolish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->style()->polish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->update();
    }
    else
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigSasAval->setText("VERT\nEN AVAL");
        ui->btnManuelSigSasAval->setProperty("fermer", false);
        ui->btnManuelSigSasAval->style()->unpolish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->style()->polish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->update();
    }

    ui->aniFeuSasAval->setPixmap(image);
}

void MainWindow::lancementPorteAmont()
{
    this->porteAmont->start();
    if ( this->porteAmont->get_ouvert() )
    {
        ui->btnManuelPortesAmont->setText("FERMER\nAMONT");
        ui->btnManuelPortesAmont->setProperty("fermer", true);
        ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->update();
    }
    else
    {
        ui->btnManuelPortesAmont->setText("OUVRIR\nAMONT");
        ui->btnManuelPortesAmont->setProperty("fermer", false);
        ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->update();
    }
}

void MainWindow::echangePorteAmont(int value)
{
    if ( this->porteAmont->get_ouvert() )
    {
        ui->aniPorteAmont->move(250,-120-(value-10)*20);
    }
    else
    {
        ui->aniPorteAmont->move(250,120+(value-10)*20);
    }
}

void MainWindow::lancementPorteAval()
{
    this->porteAval->start();
    if ( this->porteAmont->get_ouvert() )
    {
        ui->btnManuelPortesAval->setText("FERMER\nAVAL");
        ui->btnManuelPortesAval->setProperty("fermer", true);
        ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->update();
    }
    else
    {
        ui->btnManuelPortesAval->setText("OUVRIR\nAVAL");
        ui->btnManuelPortesAval->setProperty("fermer", false);
        ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->update();
    }
}

void MainWindow::echangePorteAval(int value)
{
    if ( this->porteAval->get_ouvert() )
    {
        ui->aniPorteAval->move(580,-120-(value-10)*20);
    }
    else
    {
        ui->aniPorteAval->move(580,120+(value-10)*20);
    }
}
