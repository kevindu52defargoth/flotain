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