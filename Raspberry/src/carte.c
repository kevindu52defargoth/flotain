#include <carte.h>


struct coordones next_case(struct coordones coord, direction_t desire )
{
switch (desire)
{
case N:
    coord.i +=  1;
    break;
case S:
    coord.i -= 1;
    break;
case E:
    coord.g += 1;
    break;
case W:
    coord.g -= 1;
    break;

default:
    break;
}
    

}

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
