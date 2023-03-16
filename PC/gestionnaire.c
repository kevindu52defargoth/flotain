#include "gestionnaire.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK_T(status, msg) if (0 != (status)) { fprintf(stderr, "pthread erreur : %s\n", msg); exit(-1);}

#define NBRE_RESSOURCES 4
pthread_mutex_t modifier_etat;
pthread_mutex_t ressources[NBRE_RESSOURCES];

int init_gestionnaire(){
  for (int i; i < NBRE_RESSOURCES; i++){
    CHECK_T(pthread_mutex_unlock(&ressources[i]), "initialisation des mutex");
  }

  return 0;
}

void prendre_ressource(int ressource, socket_t socket){
  struct param *p = malloc(sizeof(struct param));
  pthread_t tid;
  pthread_attr_t attr;

  //attributs des threads
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  p->ressource = ressource;
  p->socket = socket;

  CHECK_T(pthread_create(&tid, &attr, (void*(*)(void*)) thread_prendre_ressource, p), "pb creation thread\n");
}

void * thread_prendre_ressource(struct param * p){
  int ressource;
  socket_t socket;

  ressource = p->ressource;
  socket = p->socket;

  printf("On prend la ressource %d\n", ressource);

  // TODO : envoyer Ack
  envoyer(&socket, "Ack\n", NULL);

  pthread_mutex_lock(&ressources[ressource]);

  // TODO : envoyer OK_RESSOURCE
  envoyer(&socket, "OK RESSOURCE\n", NULL);

  free(p);

  return 0;
}

void liberer_ressource(int ressource, socket_t socket){
  struct param * p = malloc(sizeof(struct param));
  pthread_t tid;
  pthread_attr_t attr;

  //attributs des threads
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  p->ressource = ressource;
  p->socket = socket;

  CHECK_T(pthread_create(&tid, &attr, (void*(*)(void*)) thread_liberer_ressource, p), "pb creation thread\n");
}

void * thread_liberer_ressource(struct param * p){
  int ressource;
  socket_t socket;

  ressource = p->ressource;
  socket = p->socket;

  printf("On libere la ressource %d\n", ressource);

  // TODO : envoyer Ack
  envoyer(&socket, "Ack\n", NULL);

  pthread_mutex_unlock(&ressources[ressource]);

  // TODO : envoyer OK_RESSOURCE
  envoyer(&socket, "OK RESSOURCE\n", NULL);
  free(p);

  return 0;
}
