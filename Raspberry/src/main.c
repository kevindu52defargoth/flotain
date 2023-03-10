#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include <driver_robot.h>
#include <commons.h>
#include <main.h>
#include <carte.h>
#include <unistd.h>

#define RANDOM(min, max) (min) + rand() % ((max) - (min) + 1)

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
