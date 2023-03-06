# flotain

Contient les codes pour le projet de gestion d'un entrepôt avec une flotte de robots.

## Modélisation et choix techniques

## Structure du projet

```
.
├── Arduino
│   └── Flotain_moteur
│       ├── Flotain_moteur.ino
│       └── Functions_motor.ino
├── PC
├── Raspberry
│   ├── bin
│   ├── include
│   │   └── driver_robot.h
│   ├── makefile
│   └── src
│       ├── driver_robot.c
│       └── main.c
└── README.md
```

`PC` contient les codes à faire tourner sur l'ordinateur qui contrôle le système.

`Raspberry` contient les codes à faire tourner sur le megapi des robots.

`Arduino` contient les codes à téléversé sur les arduino des robots afin de contrôler les moteurs.

### Raspberry

### PC

## Get started

### Raspberry

Pour compiler les codes dans le dossier `Raspberry`, on peut faire
```bash
make
```

Cela créera des fichiers objets `.o` dans le dossier `bin`, et l'exécutable `./main`.

