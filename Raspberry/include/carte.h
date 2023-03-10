/* Pour contenir les données sur la carte que doivent parcourir les robots */

#include "stdlib.h"
#ifndef INCLUDE_CARTE
#define L_CASE 23.6  /* coté d'une case en cm */
#define NBRE_CASE_I 9  /* nombre de lignes sur la carte */
#define NBRE_CASE_J 9  /* nombre de colonnes sur la carte */
#define NBRE_CASE (NBRE_CASE_I*NBRE_CASE_J)

struct coordones{
  int i;
  int g;
};

typedef enum direction{
  N, S, E, W
} direction_t;


typedef struct intersection{
  direction_t d1;
  direction_t d2;
  int id_ressource;
} intersection_t;

typedef struct route {
  direction_t d;
} route_t;

typedef void allee_t;

typedef union cell {
  intersection_t inter;
  route_t road;
} cell_t;

cell_t* carte[NBRE_CASE_I][NBRE_CASE_J] ;


#define ALLEE_i(i) &(cell_t){.inter={N, E, i}}
#define DEPOT_i(i) &(cell_t){.inter={S, W, i+5}}
#define ALLEE &(cell_t){.inter={W, E, 0}}
#define ROUTE(d) &(cell_t){.road={d}}

cell_t* carte[NBRE_CASE_I][NBRE_CASE_J] = {
  {NULL, NULL, ROUTE(S), ROUTE(W), ROUTE(W), NULL, NULL, NULL, NULL},
  {ALLEE, ALLEE, DEPOT_i(1), NULL, ALLEE_i(1), ALLEE, ALLEE, ALLEE, ALLEE,},
  {NULL, NULL, ROUTE(S), NULL, ROUTE(N), NULL, NULL, NULL, NULL},
  {ALLEE, ALLEE, DEPOT_i(2), NULL, ALLEE_i(2), ALLEE, ALLEE, ALLEE, ALLEE,},
  {NULL, NULL, ROUTE(S), NULL, ROUTE(N), NULL, NULL, NULL, NULL},
  {ROUTE(S), ROUTE(W), ROUTE(W), NULL, ALLEE_i(3), ALLEE, ALLEE, ALLEE, ALLEE,},
  {ROUTE(E), ROUTE(S), NULL, NULL, ROUTE(N), NULL, NULL, NULL, NULL},
  {ROUTE(S), ROUTE(W), NULL, NULL, ALLEE_i(4), ALLEE, ALLEE, ALLEE, ALLEE,},
  {ROUTE(E), ROUTE(E), ROUTE(E), ROUTE(E),ROUTE(N), NULL, NULL, NULL, NULL},
};


cell_t coordones();

struct coordones next_case(struct coordones, direction_t desire );

#define INCLUDE_CARTE
#endif
