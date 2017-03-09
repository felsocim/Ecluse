#include "sequence.h"

sequence::sequence(QObject *parent) : QThread(parent)
{
    tps = 10;
}

void sequence::run()
{
    sleep(tps);
    emit attente_finie();
}
