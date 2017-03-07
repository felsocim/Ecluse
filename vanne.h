#ifndef VANNE_H
#define VANNE_H

#include <QObject>
#include <QThread>
#include <QTimer>

class Vanne : public QThread
{
    Q_OBJECT
public:
    explicit Vanne(QObject * parent = 0);
protected:
    void run();
    bool etat;
    bool alarme;
    int niveau_eau_exterieur;
    int niveau_eau_sas;
    int niveau_eau_pas;
public:
    void setNiveauEauExterieur(int niveau);
    void setNiveauEauSas(int niveau);
    void setNiveauEauPas(int pas);
    int getNiveauEauExterieur();
    int getNiveauEauSas();
public slots:
    void changer_etat();
    void declancher_alarme();
    void extinction_alarme();
    void remise_a_niveau();
signals:
    void signaler_alarme(bool alarme);
    void signaler_etat(bool etat);
    void signaler_niveau_eau(int niveau_sas);
};

#endif // VANNE_H
