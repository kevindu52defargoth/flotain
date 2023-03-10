/* Pour contenir les données sur la carte que doivent parcourir les robots */

#include "stdlib.h"
#ifndef INCLUDE_CARTE
#define L_CASE 23.6  /* coté d'une case en cm */
#define NBRE_CASE_I 9  /* nombre de lignes sur la carte */
#define NBRE_CASE_J 9  /* nombre de colonnes sur la carte */
#define NBRE_CASE (NBRE_CASE_I*NBRE_CASE_J)
#define NBRE_ALLEE 4
#define NBRE_OBJ 4
#define NBRE_DEPOT 2
#define MAX_CHEMIN 10

struct coordones{
  int i;
  int g;
}; 

struct coordonesreel{
  int x;
  int y;
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

typedef struct cell {
  union {
    intersection_t inter;
    route_t road;
  };
  int type;
} cell_t;

#define is_intersection(cell) (cell->type == 1)
#define is_route(cell)(cell->type == 2)


extern cell_t* carte[NBRE_CASE_I][NBRE_CASE_J];

/**
 * transforme les coordonées (i, j) d'une case en les coordonnées (x, y) de son centre
 * @param coordones_tableau les coordonnées de la case
 * @return (x, y) dans le repère physique
 */
struct coordonesreel coordones_trad(struct coordones coordones_tableau);

/**
 * Donne la prochaine case à partir de la case où l'on est et d'une direction
 *
 * @param c coordonnées de la case où l'on se trouve
 * @param desire direction dans laquelle on veut aller
 * @return case de destination
 */
struct coordones next_case(struct coordones c, direction_t desire );


extern struct coordones coord_repos;
#define INCLUDE_CARTE
#endif
