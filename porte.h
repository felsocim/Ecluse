#ifndef PORTE_H
#define PORTE_H

#include <QThread>

class Porte : public QThread
{
     Q_OBJECT
public:
    explicit Porte(QObject *parent = 0);
    int get_ouvert();
    void declencher_alarme();
    void extinction_alarme();
    void bloquer_porte();
    void debloquer_porte();

protected:
    void run();

protected:
    bool alarme;
    bool ouvert;
    bool bloquer;
    int position;

signals:
    void transition(int value);
    void signaler_fin_transition(bool etat);
    void signaler_alarme(bool alarme);


private slots:
    void of(); // ouverture ou fermeture de la porte

};



#endif // PORTE_H
