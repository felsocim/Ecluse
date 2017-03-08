#ifndef PANNE_H
#define PANNE_H


#include <QThread>

class Panne : public QThread
{
     Q_OBJECT
public:
    explicit Panne(QObject *parent = 0);

protected:
    void run();


signals:
    void signal_panne(int value);

private slots:
    void thread_panne(); // genere aleatoirement des pannes
};


#endif // PANNE_H

