
#include "panne.h"
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QTextStream>

Panne::Panne(QObject *parent) : QThread(parent)
{}


void Panne::run(){
  thread_panne();

}

void Panne::thread_panne() {
    while (1)
    {
    int nombre_aleatoire = 0;
    int nombre_aleatoire2 = 0;
    srand(time(NULL));

    nombre_aleatoire = rand()%(100-0); // 0 à 9
    printf("%d ",nombre_aleatoire);


    QTextStream out(stdout);
    out << QString("");
    sleep(1);

    if ( nombre_aleatoire == 9)
    {
        nombre_aleatoire2 = rand()%(4-0); // 0 à 3

        emit signal_panne(nombre_aleatoire2);
        return;
    }
    }

}
