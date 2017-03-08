#include "porte.h"
#include <unistd.h>

Porte::Porte(QObject *parent) : QThread(parent)
{
    alarme=0;
    ouvert=0;
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
    } while (i-- && !alarme);
    position = 10;
    if ( !this->alarme )
    {
        this->ouvert = !this->ouvert;
    }
}

void Porte::declancher_alarme()
{
    this->alarme = true;

    emit signaler_alarme(this->alarme);
}

void Porte::extinction_alarme()
{
    this->alarme = false;

    emit signaler_alarme(this->alarme);
}
