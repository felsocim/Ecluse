#include "porte.h"
#include <unistd.h>

Porte::Porte(QObject *parent) : QThread(parent)
{
    alarme=0;
    ouvert=0;
}

int Porte::get_ouvert(){
    return ouvert;
}

void Porte::run(){
  of();

}

void Porte::of() {
    int i=10;
    do  {
        emit transition(i);
        sleep(1);
    } while (i--);
    if ( this->ouvert )
        this->ouvert = 0;
    else
        this->ouvert = 1;
}

