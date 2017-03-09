#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <unistd.h>

class sequence : public QThread
{
    Q_OBJECT
public:
    explicit sequence(QObject *parent = 0);
    void run();
    int tps;
signals:
    void attente_finie();
};

#endif // SEQUENCE_H
