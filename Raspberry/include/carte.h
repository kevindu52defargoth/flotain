/* Pour contenir les données sur la carte que doivent parcourir les robots */

#define L_CASE 23.6  /* coté d'une case en cm */
#define NBRE_CASE_I 9  /* nombre de lignes sur la carte */*
#define NBRE_CASE_J 9  /* nombre de colonnes sur la carte */

enum direction_t {
  N, S, E, W
};

struct intersection_t {
  direction_t d1;
  direction_t d2;
  int id_ressource;
};

struct route_t {
  direction_t d;
};

union cell_t {
  intersection_t inter;
  route_t road;
};
