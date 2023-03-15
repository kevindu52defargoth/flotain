#include <pthread.h>
#include "data.h"

struct param{
  socket_t socket;
  int ressource;
};

int init_gestionnaire();

void prendre_ressource(int ressource, socket_t socket);

void * thread_prendre_ressource(struct param * p);

void liberer_ressource(int ressource, socket_t socket);

void * thread_liberer_ressource(struct param * p);
