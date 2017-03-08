#include "vanne.h"

Vanne::Vanne(QObject * parent) : QThread(parent)
{
    this->etat = false;
    this->alarme = false;
}

void Vanne::run()
{
    if(this->alarme)
    {
        return;
    }

    changer_etat();

    while(niveau_eau_exterieur != niveau_eau_sas && this->etat)
    {
        remise_a_niveau();
        emit signaler_niveau_eau(niveau_eau_sas);
        sleep(1);
    }

    emit signaler_fin_cycle(this->etat);
}

bool Vanne::getEtat()
{
    return this->etat;
}

void Vanne::changer_etat()
{
    this->etat = !this->etat;
    emit signaler_etat(this->etat);
}

void Vanne::declencher_alarme()
{
    this->alarme = true;
    this->etat = false;
    emit signaler_etat(this->etat);
    emit signaler_alarme(this->alarme);
}

void Vanne::extinction_alarme()
{
    this->alarme = false;

    emit signaler_alarme(this->alarme);
}

void Vanne::setNiveauEauPas(int pas)
{
    this->niveau_eau_pas = pas;
}

void Vanne::setNiveauEauExterieur(int niveau)
{
    this->niveau_eau_exterieur = niveau;
}

void Vanne::setNiveauEauSas(int niveau)
{
    this->niveau_eau_sas = niveau;
}

int Vanne::getNiveauEauExterieur()
{
    return this->niveau_eau_exterieur;
}

int Vanne::getNiveauEauSas()
{
    return this->niveau_eau_sas;
}

void Vanne::remise_a_niveau()
{
    if(niveau_eau_sas > niveau_eau_exterieur)
    {
        niveau_eau_sas -= niveau_eau_pas;
    }
    else
    {
        niveau_eau_sas += niveau_eau_pas;
    }
}
