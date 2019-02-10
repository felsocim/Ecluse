# Écluse

Interface de contrôle pour un système d'écluse.

## À propos

Dans le cadre des cours d'interfaces homme-machine, nous avons développer une maquette d'interface de contrôle pour une écluse utilisant de simples animations graphiques pour simuler le fonctionnement de l'interface. Cette dernière comporte un mode automatique destinés aux utilisateurs normaux et un mode manuel pour les administrateurs. Des pannes du système sont simulées également.

## Fonctionnement

### Mode automatique

Au moment où le bateau arrive devant l'écluse les signalisations sont rouges et les portes sont généralement fermées. Il se peut que la porte soit ouverte par le fait qu'un autre navire soit passé récemment. Tant que la signalisation est rouge le navire ne peut pas entrer dans l'écluse. Le​ navire​ se​ trouve devant​ à l'entrée​ de l'écluse,​ devant​ les​ signalisations​ qui sont rouges. La démarche se fait en deux étapes :

1. La personne doit choisir son sens de transfert ( montant / avalant ). Lors de l'appuie, mise à niveau du niveau d'eau et ouverture de la porte. La signalisation à
l'entrée passe au vert indiquant que le navire peut entrer dans l'écluse.
2. Le navire est dans le sas, la personne retourne aux commandes et appuie sur le bouton permettant d'équilibrer le niveau d'eau. La porte derrière se ferme et la mise à
niveau s'effectue. La porte devant s'ouvre et la signalisation dans le sas passe au vert.

Le navire peut donc finalement quitter l'écluse. À tout moment, l'utilisateur peut interrompre la manœuvre en appuyant sur le bouton d'arrêt d'urgence comme indiqué dans les spécifications. L'utilisateur pourra suivre l'avancement en direct sur la partie supérieure de l'écran.

### Mode manuel

L'authentification se fait à l'aide d'une carte qui est fourni à l'employé responsable de l'écluse (pas implémenté pour le moment). L'interface permettra de contrôler chaque élément de l'écluse. Comme dans le mode automatique, l'utilisateur pourra suivre l'avancement sur la partie supérieur de l'écran.

Le mécanisme d'ouverture et de fermeture des vannes et des portes se fait grâce à des boutons qui sont associés à chaque partie de l'écluse :

- Porte en amont
- Porte en aval
- Vanne en amont
- Vanne en aval

Les boutons seront grisés pendant les cycles pour empêcher l'utilisateur de faire une mauvaise manœuvre. Par exemple, l'ouverture de porte est impossible tant que les niveaux d'eau ne sont pas égaux de part et d'autre.

## Lancement

Le projet a été réalisé à l'aide du framework Qt(R). La compilation peut être effectuée soit directement via le logiciel Qt(R) Creator ou en générant le fichier *Makefile* avec **qmake**, puis en lançant la compilation.

## Auteurs

[Marek Felsoci](mailto:marek.felsoci@etu.unistra.fr) et Arnaud Pinsun, étudiants à l'[Université de Strasbourg](http://www.unistra.fr).