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
    bool couleur; // TRUE vert, FALSE rouge

signals:
    void transition(bool value);
};

#endif
