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
    sasAval(new Signalisation),
    panne(new Panne)
    {
    ui->setupUi(this);

    panne->start();

    vanneAmont->setNiveauEauPas(10);
    vanneAval->setNiveauEauPas(10);
    changer_vanne_amont();

    urgence = false;

    //Vanne amont
    QObject::connect(ui->btnManuelVannesAmont, SIGNAL(clicked(bool)), this, SLOT(changer_vanne_amont()));
    QObject::connect(vanneAmont, SIGNAL(signaler_etat(bool)), this, SLOT(etat_vanne_amont(bool)));
    QObject::connect(vanneAmont, SIGNAL(signaler_niveau_eau(int)), this, SLOT(niveau_eau_sas_amont(int)));
    QObject::connect(vanneAmont, SIGNAL(signaler_fin_cycle(bool)), this, SLOT(fin_cycle_vanne_amont(bool)));

    //Vanne aval
    QObject::connect(ui->btnManuelVannesAval, SIGNAL(clicked(bool)), this, SLOT(changer_vanne_aval()));
    QObject::connect(vanneAval, SIGNAL(signaler_etat(bool)), this, SLOT(etat_vanne_aval(bool)));
    QObject::connect(vanneAval, SIGNAL(signaler_niveau_eau(int)), this, SLOT(niveau_eau_sas_aval(int)));
    QObject::connect(vanneAval, SIGNAL(signaler_fin_cycle(bool)), this, SLOT(fin_cycle_vanne_aval(bool)));

    //Etat d'urgence (mode manuel)
    QObject::connect(ui->btnArretUrgenceMan, SIGNAL(clicked(bool)), this, SLOT(arret_urgence()));

    //Panne
    QObject::connect(panne, SIGNAL(signal_panne(int)), this, SLOT(panne_aleatoire(int)));
    QObject::connect(vanneAmont, SIGNAL(signaler_alarme(bool)), this, SLOT(alarme_vanne_amont(bool)));
    QObject::connect(vanneAval, SIGNAL(signaler_alarme(bool)), this, SLOT(alarme_vanne_aval(bool)));
    QObject::connect(porteAmont, SIGNAL(signaler_alarme(bool)), this, SLOT(alarme_porte_amont(bool)));
    QObject::connect(porteAval, SIGNAL(signaler_alarme(bool)), this, SLOT(alarme_porte_aval(bool)));


    //Signalisation
    QObject::connect(ui->btnManuelSigEntAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigEntAmont()));
    QObject::connect(ui->btnManuelSigEntAval, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigEntAval()));
    QObject::connect(ui->btnManuelSigSasAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigSasAmont()));
    QObject::connect(ui->btnManuelSigSasAval, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigSasAval()));

    QObject::connect(entAmont, SIGNAL(transition(bool)), this, SLOT(feuxEntreeAmont(bool)));
    QObject::connect(entAval, SIGNAL(transition(bool)), this, SLOT(feuxEntreeAval(bool)));
    QObject::connect(sasAmont, SIGNAL(transition(bool)), this, SLOT(feuxSasAmont(bool)));
    QObject::connect(sasAval, SIGNAL(transition(bool)), this, SLOT(feuxSasAval(bool)));

    //Porte Amont
    QObject::connect(porteAmont, SIGNAL(transition(int)), this, SLOT(echangePorteAmont(int)));
    QObject::connect(ui->btnManuelPortesAmont, SIGNAL(clicked(bool)), this, SLOT(lancementPorteAmont()));
    QObject::connect(porteAmont, SIGNAL(signaler_fin_transition(bool)), this, SLOT(fin_cycle_porte_amont(bool)));

    //Porte Aval
    QObject::connect(porteAval, SIGNAL(transition(int)), this, SLOT(echangePorteAval(int)));
    QObject::connect(ui->btnManuelPortesAval, SIGNAL(clicked(bool)), this, SLOT(lancementPorteAval()));
    QObject::connect(porteAval, SIGNAL(signaler_fin_transition(bool)), this, SLOT(fin_cycle_porte_aval(bool)));
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

    panne->terminate();
    panne->wait();
    delete panne;

    delete ui;
}

void MainWindow::arret_urgence()
{
    if(!urgence)
    {
        panne->terminate();
        urgence = true;

        if(this->vanneAmont->getEtat())
            this->vanneAmont->changer_etat();
        if(this->vanneAval->getEtat())
            this->vanneAval->changer_etat();

        ui->btnManuelVannesAmont->setProperty("enabled", false);
        ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->update();

        ui->btnManuelVannesAval->setProperty("enabled", false);
        ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->update();

        this->porteAmont->bloquer_porte();
        ui->btnManuelPortesAmont->setProperty("enabled", false);
        ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->update();

        this->porteAval->bloquer_porte();
        ui->btnManuelPortesAval->setProperty("enabled", false);
        ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->update();

        ui->btnManuelSigEntAmont->setProperty("enabled", false);
        ui->btnManuelSigEntAmont->style()->unpolish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->style()->polish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->update();

        ui->btnManuelSigEntAval->setProperty("enabled", false);
        ui->btnManuelSigEntAval->style()->unpolish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->style()->polish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->update();

        ui->btnManuelSigSasAmont->setProperty("enabled", false);
        ui->btnManuelSigSasAmont->style()->unpolish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->style()->polish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->update();

        ui->btnManuelSigSasAval->setProperty("enabled", false);
        ui->btnManuelSigSasAval->style()->unpolish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->style()->polish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->update();

        ui->btnArretUrgenceMan->setProperty("urgence", true);
        ui->btnArretUrgenceMan->style()->unpolish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->style()->polish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->update();
    }
    else
    {
        urgence = false;

        panne->start();

        QPixmap image;
        image.load(":/EcluseAuto/blank.png");
        ui->aniWarning->setPixmap(image);
        ui->aniWarningText->setText("");


        this->vanneAmont->extinction_alarme();
        ui->btnManuelVannesAmont->setProperty("enabled", true);
        ui->btnManuelVannesAmont->setProperty("fermer", false);
        ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->update();
        this->vanneAval->extinction_alarme();
        ui->btnManuelVannesAval->setProperty("enabled", true);
        ui->btnManuelVannesAval->setProperty("fermer", false);
        ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->update();

        this->porteAmont->extinction_alarme();
        if(this->porteAmont->get_ouvert())
        {
            ui->btnManuelPortesAmont->setProperty("fermer", true);
        }
        else
        {
            ui->btnManuelPortesAmont->setProperty("fermer", false);
        }
        ui->btnManuelPortesAmont->setProperty("enabled", true);
        ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->update();

        this->porteAval->extinction_alarme();
        if(this->porteAval->get_ouvert())
        {
            ui->btnManuelPortesAval->setProperty("fermer", true);
        }
        else
        {
            ui->btnManuelPortesAval->setProperty("fermer", false);
        }
        ui->btnManuelPortesAval->setProperty("enabled", true);
        ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->update();

        if(this->entAmont->get_couleur())
        {
            ui->btnManuelSigEntAmont->setProperty("arret", true);
        }
        else
        {
            ui->btnManuelSigEntAmont->setProperty("arret", false);
        }
        ui->btnManuelSigEntAmont->setProperty("enabled", true);
        ui->btnManuelSigEntAmont->style()->unpolish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->style()->polish(ui->btnManuelSigEntAmont);
        ui->btnManuelSigEntAmont->update();

        if(this->entAval->get_couleur())
        {
            ui->btnManuelSigEntAval->setProperty("arret", true);
        }
        else
        {
            ui->btnManuelSigEntAval->setProperty("arret", false);
        }
        ui->btnManuelSigEntAval->setProperty("enabled", true);
        ui->btnManuelSigEntAval->style()->unpolish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->style()->polish(ui->btnManuelSigEntAval);
        ui->btnManuelSigEntAval->update();

        if(this->sasAmont->get_couleur())
        {
            ui->btnManuelSigSasAmont->setProperty("arret", true);
        }
        else
        {
            ui->btnManuelSigSasAmont->setProperty("arret", false);
        }
        ui->btnManuelSigSasAmont->setProperty("enabled", true);
        ui->btnManuelSigSasAmont->style()->unpolish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->style()->polish(ui->btnManuelSigSasAmont);
        ui->btnManuelSigSasAmont->update();

        if(this->sasAval->get_couleur())
        {
            ui->btnManuelSigSasAval->setProperty("arret", true);
        }
        else
        {
            ui->btnManuelSigSasAval->setProperty("arret", false);
        }
        ui->btnManuelSigSasAval->setProperty("enabled", true);
        ui->btnManuelSigSasAval->style()->unpolish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->style()->polish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->update();


        ui->btnArretUrgenceMan->setText("ARRÊT\nURGENCE");
        ui->btnArretUrgenceMan->setProperty("urgence", false);
        ui->btnArretUrgenceMan->style()->unpolish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->style()->polish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->update();
    }
}

void MainWindow::panne_aleatoire(int value)
{
        arret_urgence();
        panne->terminate();
        panne->wait();


        ui->btnArretUrgenceMan->setText("EXTINCTION\nALARME");
        ui->btnArretUrgenceMan->setProperty("urgence", true);
        ui->btnArretUrgenceMan->style()->unpolish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->style()->polish(ui->btnArretUrgenceMan);
        ui->btnArretUrgenceMan->update();

        printf("%d ",value);
        QTextStream out(stdout);
        out << QString("");

        switch ( value )
              {
                 case 0: // PANNE PORTE AMONT
                    this->porteAmont->declencher_alarme();
                    break;
                 case 1: // PANNE PORTE AVAL
                    this->porteAval->declencher_alarme();
                    break;
                 case 2: // PANNE VANNE AMONT
                    this->vanneAmont->declencher_alarme();
                    break;
                 case 3: // PANNE VANNE AVAL
                    this->vanneAval->declencher_alarme();
                    break;
                 default:
                    break;
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

void MainWindow::alarme_vanne_aval(bool alarme)
{
    QPixmap image;
    QPixmap warning;

    if(alarme)
    {
        image.load(":/EcluseAuto/vanne_panne.png");
        warning.load(":/EcluseAuto/warning.png");
        ui->aniVanneAvalOuverture->setPixmap(image);

        ui->aniWarning->setPixmap(warning);
        ui->aniWarningText->setText("Panne vanne aval !");


    }
    else
    {
        image.load(":/EcluseAuto/vanne_fermee.png");
        ui->aniVanneAvalOuverture->setPixmap(image);
    }
}

void MainWindow::alarme_vanne_amont(bool alarme)
{
    QPixmap image;
    QPixmap warning;

    if(alarme)
    {
        image.load(":/EcluseAuto/vanne_panne.png");
        warning.load(":/EcluseAuto/warning.png");
        ui->aniVanneAmontOuverture->setPixmap(image);

        ui->aniWarning->setPixmap(warning);
        ui->aniWarningText->setText("Panne vanne amont !");
    }
    else
    {
        image.load(":/EcluseAuto/vanne_fermee.png");
        ui->aniVanneAmontOuverture->setPixmap(image);
    }
}

void MainWindow::alarme_porte_amont(bool alarme)
{
    QPixmap image;
    QPixmap warning;

    if(alarme)
    {
        image.load(":/EcluseAuto/porte_fermee.png");
        warning.load(":/EcluseAuto/warning.png");

        ui->aniPorteAmont->setPixmap(image);

        ui->aniWarning->setPixmap(warning);
        ui->aniWarningText->setText("Panne porte amont !");
    }
    else
    {
        image.load(":/EcluseAuto/porte_fermee.png");

        ui->aniPorteAmont->setPixmap(image);
    }
}

void MainWindow::alarme_porte_aval(bool alarme)
{
    QPixmap image;
    QPixmap warning;

    if(alarme)
    {
        image.load(":/EcluseAuto/porte_fermee.png");
        warning.load(":/EcluseAuto/warning.png");

        ui->aniPorteAval->setPixmap(image);

        ui->aniWarning->setPixmap(warning);
        ui->aniWarningText->setText("Panne porte aval !");
    }
    else
    {
        image.load(":/EcluseAuto/porte_fermee.png");

        ui->aniPorteAval->setPixmap(image);
    }
}

void MainWindow::etat_vanne_amont(bool etat)
{
    QPixmap image;

    ui->btnManuelVannesAmont->setProperty("enabled", false);
    ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
    ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
    ui->btnManuelVannesAmont->update();

    ui->btnManuelVannesAval->setProperty("enabled", false);
    ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
    ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
    ui->btnManuelVannesAval->update();

    if(etat)
    {
        image.load(":/EcluseAuto/vanne_ouverte.png");
        ui->btnManuelVannesAmont->setText("AMONT\nOUVERT");
        ui->aniVanneAmontOuverture->setPixmap(image);
    }
    else
    {
        image.load(":/EcluseAuto/vanne_fermee.png");
        ui->btnManuelVannesAmont->setText("AMONT\nFERMÉ");
        ui->aniVanneAmontOuverture->setPixmap(image);
    }
}

void MainWindow::fin_cycle_vanne_amont(bool etat)
{
    if(!urgence)
    {
        ui->btnManuelVannesAval->setProperty("enabled", true);
        ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
        ui->btnManuelVannesAval->update();

        if(etat)
        {
            ui->btnManuelVannesAmont->setText("FERMER\nAMONT");
            ui->btnManuelVannesAmont->setProperty("enabled", true);
            ui->btnManuelVannesAmont->setProperty("fermer", true);
            ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
            ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
            ui->btnManuelVannesAmont->update();
        }
        else
        {
            ui->btnManuelVannesAmont->setText("OUVRIR\nAMONT");
            ui->btnManuelVannesAmont->setProperty("enabled", true);
            ui->btnManuelVannesAmont->setProperty("fermer", false);
            ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
            ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
            ui->btnManuelVannesAmont->update();
        }
    }
}

void MainWindow::etat_vanne_aval(bool etat)
{
    QPixmap image;

    ui->btnManuelVannesAval->setProperty("enabled", false);
    ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
    ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
    ui->btnManuelVannesAval->update();

    ui->btnManuelVannesAmont->setProperty("enabled", false);
    ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
    ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
    ui->btnManuelVannesAmont->update();

    if(etat)
    {
        image.load(":/EcluseAuto/vanne_ouverte.png");
        ui->btnManuelVannesAval->setText("AVAL\nOUVERT");
        ui->aniVanneAvalOuverture->setPixmap(image);
    }
    else
    {
        image.load(":/EcluseAuto/vanne_fermee.png");
        ui->btnManuelVannesAval->setText("AVAL\nFERMÉ");
        ui->aniVanneAvalOuverture->setPixmap(image);
    }
}

void MainWindow::fin_cycle_vanne_aval(bool etat)
{
    if(!urgence)
    {
        ui->btnManuelVannesAmont->setProperty("enabled", true);
        ui->btnManuelVannesAmont->style()->unpolish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->style()->polish(ui->btnManuelVannesAmont);
        ui->btnManuelVannesAmont->update();

        if(etat)
        {
            ui->btnManuelVannesAval->setText("FERMER\nAVAL");
            ui->btnManuelVannesAval->setProperty("enabled", true);
            ui->btnManuelVannesAval->setProperty("fermer", true);
            ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
            ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
            ui->btnManuelVannesAval->update();
        }
        else
        {
            ui->btnManuelVannesAval->setText("OUVRIR\nAVAL");
            ui->btnManuelVannesAval->setProperty("enabled", true);
            ui->btnManuelVannesAval->setProperty("fermer", false);
            ui->btnManuelVannesAval->style()->unpolish(ui->btnManuelVannesAval);
            ui->btnManuelVannesAval->style()->polish(ui->btnManuelVannesAval);
            ui->btnManuelVannesAval->update();
        }
    }
}

void MainWindow::echangeFeuManuelSigEntAmont()
{
    if ( this->porteAmont->get_ouvert() && (this->porteAmont->get_position() == 10))
        this->entAmont->start();
}

void MainWindow::feuxEntreeAmont(bool value)
{
    QPixmap image;

    if (value)
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
    if ( this->porteAval->get_ouvert() && (this->porteAval->get_position() == 10))
        this->entAval->start();
}

void MainWindow::feuxEntreeAval(bool value)
{
    QPixmap image;

    if (value)
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
    if ( this->porteAmont->get_ouvert() && (this->porteAmont->get_position() == 10))
    this->sasAmont->start();
}

void MainWindow::feuxSasAmont(bool value)
{
    QPixmap image;

    if (value)
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
    if ( this->porteAval->get_ouvert() && (this->porteAval->get_position() == 10) )
    this->sasAval->start();
}

void MainWindow::feuxSasAval(bool value)
{
    QPixmap image;

    if (value)
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigSasAval->setText("ROUGE\nEN AVAL");
        ui->btnManuelSigSasAval->setProperty("arret", true);
        ui->btnManuelSigSasAval->style()->unpolish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->style()->polish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->update();
    }
    else
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigSasAval->setText("VERT\nEN AVAL");
        ui->btnManuelSigSasAval->setProperty("arret", false);
        ui->btnManuelSigSasAval->style()->unpolish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->style()->polish(ui->btnManuelSigSasAval);
        ui->btnManuelSigSasAval->update();
    }

    ui->aniFeuSasAval->setPixmap(image);
}

void MainWindow::lancementPorteAmont()
{
    if ( this->vanneAmont->getNiveauEauExterieur() == this->vanneAmont->getNiveauEauSas())
    {
        this->porteAmont->start();

        ui->btnManuelPortesAmont->setProperty("enabled", false);
        ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
        ui->btnManuelPortesAmont->update();
    }
}

void MainWindow::fin_cycle_porte_amont(bool etat)
{
    if(!urgence)
    {
        if(etat)
        {
            ui->btnManuelPortesAmont->setText("FERMER\nAMONT");
            ui->btnManuelPortesAmont->setProperty("enabled", true);
            ui->btnManuelPortesAmont->setProperty("fermer", true);
            ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
            ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
            ui->btnManuelPortesAmont->update();
        }
        else
        {
            ui->btnManuelPortesAmont->setText("OUVRIR\nAMONT");
            ui->btnManuelPortesAmont->setProperty("enabled", true);
            ui->btnManuelPortesAmont->setProperty("fermer", false);
            ui->btnManuelPortesAmont->style()->unpolish(ui->btnManuelPortesAmont);
            ui->btnManuelPortesAmont->style()->polish(ui->btnManuelPortesAmont);
            ui->btnManuelPortesAmont->update();
        }
    }
}

void MainWindow::echangePorteAmont(int value)
{
    if ( this->porteAmont->get_ouvert() )
    {
        ui->aniPorteAmont->move(250,-80-(value-10)*20);
        ui->btnManuelPortesAmont->setText("AMONT\nSE FERME");
    }
    else
    {
        ui->aniPorteAmont->move(250,80+(value-10)*20);
        ui->btnManuelPortesAmont->setText("AMONT\nS'OUVRE");
    }
}

void MainWindow::lancementPorteAval()
{
    if ( this->vanneAval->getNiveauEauExterieur() == this->vanneAval->getNiveauEauSas())
    {
        this->porteAval->start();

        ui->btnManuelPortesAval->setProperty("enabled", false);
        ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
        ui->btnManuelPortesAval->update();
    }
}

void MainWindow::fin_cycle_porte_aval(bool etat)
{
    if(!urgence)
    {
        if(etat)
        {
            ui->btnManuelPortesAval->setText("FERMER\nAVAL");
            ui->btnManuelPortesAval->setProperty("enabled", true);
            ui->btnManuelPortesAval->setProperty("fermer", true);
            ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
            ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
            ui->btnManuelPortesAval->update();
        }
        else
        {
            ui->btnManuelPortesAval->setText("OUVRIR\nAVAL");
            ui->btnManuelPortesAval->setProperty("enabled", true);
            ui->btnManuelPortesAval->setProperty("fermer", false);
            ui->btnManuelPortesAval->style()->unpolish(ui->btnManuelPortesAval);
            ui->btnManuelPortesAval->style()->polish(ui->btnManuelPortesAval);
            ui->btnManuelPortesAval->update();
        }
    }
}

void MainWindow::echangePorteAval(int value)
{
    if ( this->porteAval->get_ouvert() )
    {
        ui->aniPorteAval->move(580,-80-(value-10)*20);
        ui->btnManuelPortesAval->setText("AVAL\nSE FERME");
    }
    else
    {
        ui->aniPorteAval->move(580,80+(value-10)*20);
        ui->btnManuelPortesAval->setText("AVAL\nS'OUVRE");
    }
}
