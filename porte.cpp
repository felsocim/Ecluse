#include "porte.h"
#include <unistd.h>

Porte::Porte(QObject *parent) : QThread(parent)
{
    bloquer=false;
    alarme=false;
    ouvert=false;
    position = 10;
}

int Porte::get_ouvert(){
    return ouvert;
}


void Porte::run(){
    of();
    emit signaler_fin_transition(this->ouvert);
}

void Porte::of() {
    int i=position;
    do  {
        emit transition(i);
        sleep(1);
    } while (i-- && !bloquer);
        position = 10;
    if ( !this->alarme )
    {
        this->ouvert = !this->ouvert;
    }
}

void Porte::declencher_alarme()
{
    this->alarme = true;

    emit signaler_alarme(this->alarme);
}

void Porte::bloquer_porte()
{
    this->bloquer=true;
}

void Porte::debloquer_porte()
{
    this->bloquer=false;
}

void Porte::extinction_alarme()
{
    this->alarme = false;
    debloquer_porte();
    emit signaler_alarme(this->alarme);
}
