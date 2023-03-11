#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include <driver_robot.h>
#include <commons.h>
#include <main.h>
#include <carte.h>
#include <unistd.h>

#define RANDOM(min, max) (min) + rand() % ((max) - (min) + 1)

/* macros temporaire pour le test */
#define avancer_case(c) sleep(RANDOM(1, 2)); printf("on va en %d, %d\n", c.i, c.g)

enum STATE {
  WAINTING_ZONE,
  AWAITING_ORDER,
  ON_THE_ROAD,
  WAITING_FOR_INTERSECTION,
  PICKING_UP,
  UNLOADING,
  LOST,
  OBSTACLE,
};

int state;
pthread_mutex_t screen;
int main(int argc, char **argv){
  pthread_mutex_unlock(&screen);
  PRINT("hello world");

  // ouverture d'une connection avec le serveur du gestionnaire

  while(1){
    // on envoie au gestionnaire que l'on attend un ordre
    state = AWAITING_ORDER;

    // on attend un ordre

    // on convertit l'ordre en chemins à suivre

    // navigation vers l'objet
    state = ON_THE_ROAD;

    //on arrive à l'objet
    state = PICKING_UP;

    sleep(RANDOM(1, 20));
        // on simule la prise de l'objet

    // navigation vers le dépôt
    state = ON_THE_ROAD;

    //on arrive au dépôt
    state = UNLOADING;

    sleep(RANDOM(1, 10));
        // on simule le dépôt de l'objet

    // navigation vers la zone de départ
    state = ON_THE_ROAD;
    // on reste probablement bloqué dans la zone d'attente derrière un autre robot
    state = WAINTING_ZONE;
  }
}

int navigation(struct coordones c, int * sorties, int nbreDirections){
  cell_t * cellule = carte[c.i][c.g];
  struct coordones next_c;
  int index = 0;

  while(index < nbreDirections){
    if (cellule == NULL){    // Le robot ne devrait pas sortir de la route
      printf("Perdu en %d, %d\n", c.i, c.g);
      return 1;

    } else if (cellule->road.d){ // S'il s'agit d'une route, on la suit
      next_c = next_case(c, cellule->road.d);
      avancer_case(next_c);  // on déplace le robot ASKIP
      c = next_c;
      cellule = carte[c.i][c.g];

    } else if (cellule->inter.d1){ // S'il s'agit d'une intersection, on suit le plan
      if (sorties[index] == 1)
        next_c = next_case(c, cellule->inter.d1);
      else
        next_c = next_case(c, cellule->inter.d2);
      index++;
      avancer_case(next_c);  // on déplace le robot ASKIP
      c = next_c;
      cellule = carte[c.i][c.g];
    }
  }
  return 0;
}
