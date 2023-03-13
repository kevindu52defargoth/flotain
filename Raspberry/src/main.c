#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include <driver_robot.h>
#include <commons.h>
#include <main.h>
#include <carte.h>
#include <unistd.h>
#include<network.h>

#define RANDOM(min, max) (min) + rand() % ((max) - (min) + 1)


#define SEND_READY() printf("function send ready")
#define SEND_DEMANDE_RES() printf("function send res demand")
#define SEND_FREE_RES() printf("function send free res")
#define SEND_OBJ_OK() printf("function send objet ok")
#define SEND_OBJ_DEPOT() printf("function send objet depot")



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

  int sd1; //descripteur de socket de dialogue
  struct sockaddr_in addrServ, addrCli;
  char buff[MAXCAR+1];
  int erreur, nbcar;
  int adrlg=sizeof(struct sockaddr_in);

  // Creation de la socket 
  sd1=socket(AF_INET, SOCK_STREAM, 0);

  CHECKERROR(sd1,-1, "Creation fail !!!\n");

  //Etape2 - Adressage du destinataire

  addrServ.sin_family=AF_INET;
  addrServ.sin_port = htons(REMOTEPORT);
  addrServ.sin_addr.s_addr = inet_addr(REMOTEIP);

 // Etape 3 - demande d'ouverture de connexion sd1
  CHECK(connect(sd1, (const struct sockaddr *)&addrServ,
                sizeof(struct sockaddr_in)), "Probleme connection\n");

  printf("OK connect sd1\n");


  
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
