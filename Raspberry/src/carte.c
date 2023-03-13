#include <carte.h>


struct coordones next_case(struct coordones coord, direction desire )
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
    coord.g -= 1
    break;

default:
    break;
}
    

}


struct coordonesreel coordones_trad(struct coordones coordones_tableau){

    struct coordonesreel coordonestrad;

    coordonestrad.x = L_CASE * (coordones_tableau.i - 1/2 ); 
    
    coordonestrad.y = L_CASE * (coordones_tableau.G - 1/2 );
}
