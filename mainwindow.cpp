#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    porteAmont(new Porte),
    porteAval(new Porte),
    entAmont(new Signalisation),
    entAval(new Signalisation),
    sasAmont(new Signalisation),
    sasAval(new Signalisation)
    {
    ui->setupUi(this);

    //Connexion slots
    QObject::connect(ui->btnManuelSigEntAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigEntAmont()));
    QObject::connect(ui->btnManuelSigEntAval, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigEntAval()));
    QObject::connect(ui->btnManuelSigSasAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigSasAmont()));
    QObject::connect(ui->btnManuelSigSasAval, SIGNAL(clicked(bool)), this, SLOT(echangeFeuManuelSigSasAval()));


        // Porte Amont
    QObject::connect(porteAmont, SIGNAL(transition(int)), this, SLOT(echangePorteAmont(int)));
    QObject::connect(ui->btnManuelPortesAmont, SIGNAL(clicked(bool)), this, SLOT(lancementPorteAmont()));

        // Porte Aval
    QObject::connect(porteAval, SIGNAL(transition(int)), this, SLOT(echangePorteAval(int)));
    QObject::connect(ui->btnManuelPortesAval, SIGNAL(clicked(bool)), this, SLOT(lancementPorteAval()));


    }

MainWindow::~MainWindow()
{
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

void MainWindow::echangeFeuManuelSigEntAmont()
{
    this->entAmont->start();
    QPixmap image;

    if ( this->entAmont->get_couleur())
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigEntAmont->setText("VERT\nEN AMONT");
    }
    else
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigEntAmont->setText("ROUGE\n EN AMONT");
    }

    ui->aniFeuEntreeAmont->setPixmap(image);
}

void MainWindow::echangeFeuManuelSigEntAval()
{
    this->entAval->start();
    QPixmap image;

    if ( this->entAval->get_couleur())
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigEntAval->setText("VERT\nEN AMONT");
    }
    else
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigEntAval->setText("ROUGE\n EN AMONT");
    }

    ui->aniFeuEntreeAval->setPixmap(image);
}

void MainWindow::echangeFeuManuelSigSasAmont()
{
    this->sasAmont->start();
    QPixmap image;

    if ( this->sasAmont->get_couleur())
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigSasAmont->setText("VERT\nEN AMONT");
    }
    else
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigSasAmont->setText("ROUGE\n EN AMONT");
    }

    ui->aniFeuSasAmont->setPixmap(image);
}

void MainWindow::echangeFeuManuelSigSasAval()
{
    this->sasAval->start();
    QPixmap image;

    if ( this->sasAval->get_couleur())
    {
        image.load(":/EcluseAuto/feu_rouge.png");
        ui->btnManuelSigSasAval->setText("VERT\nEN AMONT");
    }
    else
    {
        image.load(":/EcluseAuto/feu_vert.png");
        ui->btnManuelSigSasAval->setText("ROUGE\n EN AMONT");
    }

    ui->aniFeuSasAval->setPixmap(image);
}

void MainWindow::lancementPorteAmont()
{
    this->porteAmont->start();
    if ( this->porteAmont->get_ouvert() )
        ui->btnManuelPortesAmont->setText("OUVRIR\nAMONT");
    else
        ui->btnManuelPortesAmont->setText("FERMER\nAMONT");
}

void MainWindow::echangePorteAmont(int value)
{
    if ( this->porteAmont->get_ouvert() )
    {
        ui->aniPorteAmont->move(250,-100-(value-10)*20);
    }
    else
    {
        ui->aniPorteAmont->move(250,100+(value-10)*20);
    }
}

void MainWindow::lancementPorteAval()
{
    this->porteAval->start();
    if ( this->porteAmont->get_ouvert() )
        ui->btnManuelPortesAval->setText("OUVRIR\nAVAL");
    else
        ui->btnManuelPortesAval->setText("FERMER\nAVAL");
}

void MainWindow::echangePorteAval(int value)
{
    if ( this->porteAval->get_ouvert() )
    {
        ui->aniPorteAval->move(580,-100-(value-10)*20);
    }
    else
    {
        ui->aniPorteAval->move(580,100+(value-10)*20);
    }
}


