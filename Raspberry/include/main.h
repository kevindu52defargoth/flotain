#include "carte.h"

/**
 * Cette fonction fait en sorte que le robot suive le chemin passé en argument
 * @param c les coordonnées de départ
 * @param sorties le chemin à suivre
 * @param nbreDirections la taille du chemin
 * @return les coordonnées à la fin de la navigation
 */
struct coordones navigation(struct coordones c, int * sorties, int nbreDirections);

/** construit le chemin entre la zone de départ et l'emplacement de l'objet à aller chercher.
 * On peut ensuite passer ce chemin à navigation
 * @param numeroAlle
 * @param numeroObjet avec numeroAlle définissent l'objet à aller chercher
 * @param chemin int * où placer le chemin
 * @param lenChemin int * où placer la taille du chemin
 * @return 0 si tout s'est bien passé
 */
int construire_chemin_to_objet(int numeroAlle, int numeroObjet, int *chemin, int * lenChemin);

/**
 * construit le chemin entre l'emplacement de l'objet et le dépôt où le placer
 */
int construire_chemin_from_object_to_depot(int numeroDepot, int numeroAlle, int numeroObjet, int *chemin, int * lenChemin);

/**
 * construit le chemin entre le dépot et le début de la file d'attente
 */
int construire_chemin_from_depot_to_repos(int numeroDepot, int *chemin, int * lenChemin);

/**
 * fait le trajet entre le début de la queue et la zone de départ
 */
struct coordones faire_la_queue(struct coordones c);

/* macro pour éviter les cases NULL*/
#define CHECK_CASE_FOR_NULL  \
if (cellule == NULL) { /* Le robot ne devrait pas sortir de la route */  \
  fprintf(stderr, "Perdu en %d, %d\n", c.i, c.g);  \
  return (struct coordones){-1, -1};  \
}

#define CHECK_COORD_FOR_INVALID  \
  if (coordones_courantes.i == -1 && coordones_courantes.g == -1){  \
    printf("\e[31m" "PERDU" "\e[0m");  \
  }

/* macros pour vérifier les entrées des construire_chemin_* */
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
