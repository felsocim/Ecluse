#ifndef ECLUSE_H
#define ECLUSE_H

#include <QObject>
#include "vanne.h"

class Ecluse
{
public:
    Ecluse();
private:
    Vanne vanneAmont;
    Vanne vanneAval;
};

#endif // ECLUSE_H
