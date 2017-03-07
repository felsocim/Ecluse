
#include "signalisation.h"
#include <unistd.h>

Signalisation::Signalisation(QObject *parent) : QThread(parent)
{
    this->couleur = 0;
}

int Signalisation::get_couleur(){
    return couleur;
}

void Signalisation::run()
{
    if ( this->couleur )
        this->couleur = 0;
    else
        this->couleur = 1;
}


