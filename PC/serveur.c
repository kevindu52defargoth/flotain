#define _GNU_SOURCE
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include "gestionnaire.h"
#include "network.h"

#define IP_ANY		"0.0.0.0"


#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}
#define CHECK_T(status, msg) if (0 != (status)) { fprintf(stderr, "pthread erreur : %s\n", msg); exit(-1);}

void serialize(generic quoi, generic buffer){
  char *s = (char *)quoi;
  strcpy((char *)buffer, s);
}

void deserialize(generic quoi, generic buffer) {
  char *s = (char *)quoi;
  strcpy((char *)buffer, s);
}

void* traiterClt(void* arg) {
  socket_t  sockDial = *(socket_t *)arg;
  buffer_t buff;

//   envoyer(&sockDial, "Bienvenue\n", serialize);
  int i = 1;
  while (i) {
    recevoir(&sockDial, buff, deserialize);
    printf("recue %ld char : %s\n", strlen(buff), buff);
    int head = (int)(buff[0]);
    printf("%d\n", head);

    // ok_ready 
    if (buff[0]=='0'){
      
      printf("ça marche\n");
    }
    switch (buff[0])
    {
    case READY:
      printf("ready\n");
      break;

   
    default:
      break;
    }

    // if (buff[0] == 'T')
    //   prendre_ressource(atoi(buff+1), sockDial);
    // else if (buff[0] == 'L')
    //   liberer_ressource(atoi(buff+1), sockDial);
    // else
    i = 0;
  }
  // envoyer(&sockDial, "A+", NULL);

  CHECK(close(sockDial.fd),"-- PB close() --");

  pthread_exit(NULL);
}

int main(){
  socket_t sockEcoute;	// socket d'écoute de demande de connexion d'un client
  socket_t sockDial;		// socket de dialogue avec un client
  buffer_t buff;
  char * msg = malloc(100*sizeof(char));

//   init_gestionnaire();

  sockEcoute = creerSocketEcoute(IP_ANY, PORT_SRV);
  printf("début srv\n");
  while(1)	// daemon !
  {
    // Accepter une connexion
    sockDial = accepterClt(sockEcoute);
    // Dialoguer avec le client connecté
    pthread_t tid;
    CHECK_T(pthread_create(&tid, NULL, traiterClt, &sockDial), "Erreur création thread\n");
    pthread_detach(tid);
  }
  // Fermer la socket d'écoute
  CHECK(close(sockEcoute.fd),"-- PB close() --");
}
