#ifndef SIGNALISATION_H
#define SIGNALISATION_H



#include <QThread>

class Signalisation : public QThread
{
     Q_OBJECT
public:
    explicit Signalisation(QObject *parent = 0);
    int get_couleur();

protected:
    void run();

protected:
    bool couleur; // 1 vert 0 rouge

signals:
    void transition(int value);

/*private slots:
    void of(); // ouverture ou fermeture de la porte*/
};



#endif // PORTE_H
