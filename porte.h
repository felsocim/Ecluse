#ifndef PORTE_H
#define PORTE_H

#include <QThread>

class Porte : public QThread
{
     Q_OBJECT
public:
    explicit Porte(QObject *parent = 0);
    int get_ouvert();

protected:
    void run();

protected:
    bool alarme;
    bool ouvert;

signals:
    void transition(int value);

private slots:
    void of(); // ouverture ou fermeture de la porte
};



#endif // PORTE_H
