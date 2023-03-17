#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include <commons.h>
#include <main.h>
#include <carte.h>
#include <unistd.h>
#include<network.h>

#define RANDOM(min, max) (min) + rand() % ((max) - (min) + 1)

/* macros temporaire pour le test */
#define avancer_case(c) sleep(RANDOM(1, 2));printf("on va en %d, %d\n", c.i, c.g)



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

  int * chemin1, * chemin2, * chemin3;
  int lenChemin1, lenChemin2, lenChemin3;
  struct coordones coordones_courantes = coord_repos;

  // ouverture d'une connection avec le serveur du gestionnaire

 //  int sd1; //descripteur de socket de dialogue
 //  struct sockaddr_in addrServ, addrCli;
 //  char buff[MAXCAR+1];
 //  int erreur, nbcar;
 //  int adrlg=sizeof(struct sockaddr_in);
 //
 //  // Creation de la socket
 //  sd1=socket(AF_INET, SOCK_STREAM, 0);
 //
 //  CHECKERROR(sd1,-1, "Creation fail !!!\n");
 //
 //  //Etape2 - Adressage du destinataire
 //
 //  addrServ.sin_family=AF_INET;
 //  addrServ.sin_port = htons(REMOTEPORT);
 //  addrServ.sin_addr.s_addr = inet_addr(REMOTEIP);
 //
 // // Etape 3 - demande d'ouverture de connexion sd1
 //  CHECK(connect(sd1, (const struct sockaddr *)&addrServ,
 //                sizeof(struct sockaddr_in)), "Probleme connection\n");

  while(1){
    // on envoie au gestionnaire que l'on attend un ordre
    state = AWAITING_ORDER;

    // on attend un ordre

    // on convertit l'ordre en chemins à suivre
    chemin1 = malloc(MAX_CHEMIN * sizeof(int));
    CHECK(construire_chemin_to_objet(1, 2, chemin1, &lenChemin1), "objet ou dépôt invalide");

    chemin2 = malloc(MAX_CHEMIN * sizeof(int));
    CHECK(construire_chemin_from_object_to_depot(1, 1, 2, chemin2, &lenChemin2), "objet ou dépôt invalide");

    chemin3 = malloc(MAX_CHEMIN * sizeof(int));
    CHECK(construire_chemin_from_depot_to_repos(1, chemin3, &lenChemin3), "objet ou dépôt invalide");

    // navigation vers l'objet
    state = ON_THE_ROAD;
    coordones_courantes = navigation(coord_repos, chemin1, lenChemin1);
    CHECK_COORD_FOR_INVALID;

    //on arrive à l'objet
    state = PICKING_UP;

    printf("On prend l'objet 😉\n");
    sleep(RANDOM(1, 20));
        // on simule la prise de l'objet

    // navigation vers le dépôt
    state = ON_THE_ROAD;
    coordones_courantes = navigation(coordones_courantes, chemin2, lenChemin2);
    CHECK_COORD_FOR_INVALID;

    //on arrive au dépôt
    state = UNLOADING;

    printf("On dépose l'objet 😉\n");
    sleep(RANDOM(1, 10));
        // on simule le dépôt de l'objet

    // navigation vers la zone d'attente
    state = ON_THE_ROAD;
    coordones_courantes =  navigation(coordones_courantes, chemin3, lenChemin3);
    CHECK_COORD_FOR_INVALID;
    // on reste probablement bloqué dans la zone d'attente derrière un autre robot
    state = WAINTING_ZONE;
    coordones_courantes = faire_la_queue(coordones_courantes);
    CHECK_COORD_FOR_INVALID;
  }
}


int construire_chemin_to_objet(int numeroAlle, int numeroObjet, int *chemin, int * lenChemin){
  CHECK_NBRE_ALLEE;
  CHECK_NBRE_OBJ;

  int i = 0;
  for (int j = 0; j < numeroAlle; j++){
    chemin[j] = 1;
  }
  chemin[numeroAlle] = 2;
  i += numeroAlle + 1;

  for (int j = 0; j < numeroObjet; j++)
    chemin[i + j] = 2;
  i += numeroObjet;

  *lenChemin = i;
#ifdef _DEBUG_
  printf("chemin from to object: ");
  for (int j = 0; j < i; j++) {
    printf("%d\t", chemin[j]);
  }
  printf("\nlenChemin : %d\n", i);
#endif

  return 0;
}

int construire_chemin_from_object_to_depot(int numeroDepot, int numeroAlle, int numeroObjet, int *chemin, int * lenChemin){
  CHECK_NBRE_ALLEE;
  CHECK_NBRE_OBJ;
  CHECK_NBRE_DEPOT;

  int i = 0;
  for(int j = 0; j< numeroObjet; j++)
    chemin[j] = 1;
  i += numeroObjet;

  for (int j = numeroAlle; j < NBRE_ALLEE; j++) {
    chemin[i] = 1;
    i++;
  }

  for(int j = 0; j< numeroDepot; j++)
    chemin[i + j] = 1;
  i += numeroDepot + 1;
  chemin[i - 1] = 2;

  *lenChemin = i;
#ifdef _DEBUG_
  printf("chemin from object to depot : ");
  for (int j = 0; j < i; j++) {
    printf("%d\t", chemin[j]);
  }
  printf("\nlenChemin : %d\n", i);
#endif

  return 0;
}

int construire_chemin_from_depot_to_repos(int numeroDepot, int *chemin, int * lenChemin){
  CHECK_NBRE_DEPOT;

  int i = 0;
  chemin[i] = 2;
  i++;

  for(int j = numeroDepot; j < NBRE_DEPOT; j++){
    chemin[i + j - 1] = 1;
    i++;
  }

  *lenChemin = i;
#ifdef _DEBUG_
  printf("chemin from depot : ");
  for (int j = 0; j < i; j++){
    printf("%d\t", chemin[j]);
  }
  printf("\nlenChemin : %d\n",i);
#endif

  return 0;
}

struct coordones navigation(struct coordones c, int * sorties, int nbreDirections){
  cell_t * cellule = carte[c.i][c.g];
  struct coordones next_c;
  int index = 0;

  while(index < nbreDirections){
    CHECK_CASE_FOR_NULL;

    if (is_route(cellule)){ // S'il s'agit d'une route, on la suit
#ifdef _DEBUG_
      printf("route ");
#endif
      next_c = next_case(c, cellule->road.d);
      avancer_case(next_c);  // on déplace le robot ASKIP
      c = next_c;
      cellule = carte[c.i][c.g];

    } else if (is_intersection(cellule)){ // S'il s'agit d'une intersection, on suit le plan
#ifdef _DEBUG_
      printf("intersection ");
#endif
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
#ifdef _DEBUG_
  printf("fin nav\n");
#endif

  return c;
}

struct coordones faire_la_queue(struct coordones c) {
  cell_t *cellule;
  struct coordones next_c;
  cellule = carte[c.i][c.g];

  while (c.i != coord_repos.i || c.g != coord_repos.g) {
    CHECK_CASE_FOR_NULL;
#ifdef _DEBUG_
    printf("route ");
#endif
    next_c = next_case(c, cellule->road.d);
    avancer_case(next_c); // on déplace le robot ASKIP
    c = next_c;
    cellule = carte[c.i][c.g];
  }
  return c;
}
