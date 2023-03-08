/* Pour contenir les données sur la carte que doivent parcourir les robots */

#define L_CASE 23.6  /* coté d'une case en cm */
#define NBRE_CASE_I 9  /* nombre de lignes sur la carte */
#define NBRE_CASE_J 9  /* nombre de colonnes sur la carte */
#define NBRE_CASE (NBRE_CASE_I*NBRE_CASE_J)

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
