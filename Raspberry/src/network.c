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
// #include <data.h>

 char *preparer_message(message_t head, char* info)
{    
    char* message = malloc(strlen(info) + sizeof(head) + 2); // allocate memory dynamically
    
    sprintf(message, "%d:%s", head, info);
    
    return message;
}

int main()
{   
    message_t head = DEMANDE_RES;
    char *info = "1.2.2";
    char *msg = preparer_message(head, info);

    printf("Merged string: %s\n", msg);

    free(msg); // free the dynamically allocated memory
}