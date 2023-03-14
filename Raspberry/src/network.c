#include "stdlib.h"
#include "stdio.h"
// #include <pthread.h>
// #include <driver_robot.h>
// #include <commons.h>
// #include <main.h>
// #include <carte.h>
#include <unistd.h>
#include<C:\Users\ADERALDO\Desktop\Parcours\Flotte\Flotte\flotain\Raspberry\include\network.h>
#include<string.h>

void preparer_message(message_t head, char* info)
{  
                         
    /* this function takes two arguments to stardize 
       the message into the protocol created   {head.info}
    */

                         
    char message[strlen(info) + sizeof(head) + 2];  /* make sure the buffer is large enough to hold the converted string
                                                     the + 2 is for the colon and null terminator) */ 
    
    sprintf(message, "%d:%s", head, info);          //merging into the format required to the protocol


    // printf("Merged string: %s\n", message);

}


// void preparer_message(message_t head, char info)
int main()
{   
    message_t head = DEMANDE_RES;
    char *info = "1.2.2";
    preparer_message(head, info);
}




void evoyer()
{
  
}
