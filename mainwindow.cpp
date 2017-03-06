#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connexion slots
    QObject::connect(ui->btnManuelSigEntAmont, SIGNAL(clicked(bool)), this, SLOT(echangeFeu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::echangeFeu()
{
    QPushButton * sender = (QPushButton *) QObject::sender();

    QPixmap image;
    image.load(":/EcluseAuto/feu_vert.png");

    ui->aniFeuEntreeAmont->setPixmap(image);
}
