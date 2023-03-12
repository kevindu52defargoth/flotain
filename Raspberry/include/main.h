#include "carte.h"

int navigation(struct coordones c, int * sorties, int nbreDirections);

int construire_chemin_to_objet(int numeroAlle, int numeroObjet, int *chemin, int * lenChemin);

int construire_chemin_from_object_to_depot(int numeroDepot, int numeroAlle, int numeroObjet, int *chemin, int * lenChemin);

int construire_chemin_from_depot_to_repos(int numeroDepot, int *chemin, int * lenChemin);
