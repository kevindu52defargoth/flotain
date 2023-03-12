#include "carte.h"

int navigation(struct coordones c, int * sorties, int nbreDirections);

int construire_chemin_to_objet(int numeroAlle, int numeroObjet, int *chemin, int * lenChemin);

int construire_chemin_from_object_to_depot(int numeroDepot, int numeroAlle, int numeroObjet, int *chemin, int * lenChemin);

int construire_chemin_from_depot_to_repos(int numeroDepot, int *chemin, int * lenChemin);

/* macros pur vérifier les entrées des construire_chemin_* */
#define CHECK_NBRE_ALLEE \
if (numeroAlle < 0 || numeroAlle > NBRE_ALLEE){  \
  fprintf(stderr, "numero allée incohérent\n");  \
  return 1;  \
}

#define  CHECK_NBRE_OBJ \
if (numeroObjet < 0 || numeroObjet > NBRE_OBJ){  \
  fprintf(stderr, "numero objet incohérent\n");  \
  return 2;  \
}

#define CHECK_NBRE_DEPOT \
if (numeroDepot < 0 || numeroDepot > NBRE_DEPOT){  \
  fprintf(stderr, "numero dépot incohérent\n");  \
  return 3;  \
}
