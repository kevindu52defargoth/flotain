#include "stdlib.h"
#include "stdio.h"
// #include <pthread.h>
// #include <driver_robot.h>
// #include <commons.h>
// #include <main.h>
// #include <carte.h>
#include <unistd.h>
#include"../include/network.h"
#include<string.h>
#include"../include/data.h"

 char *preparer_message(message_t head, char* info)
{    
    char* message = malloc(strlen(info) + sizeof(head) + 2); // allocate memory dynamically
    
    sprintf(message, "%d:%s", head, info);
    
    return message;
}

int main()
{   
    socket_t sockAppel;	// socket d'appel
    buffer_t buff;
    message_t head = DEMANDE_RES;
    char *info = "1.2.2";
    char *msg2 = preparer_message(head, info);
    // char *cu = "T";
    
    printf("Merged string: %s\n", msg2);
    sockAppel = connecterClt2Srv(IP_SRV, PORT_SRV);
    // envoyer(&sockAppel, cu, NULL);
    // SEND_READY();
    // SEND_DEMANDE_RES("1");
    SEND_FREE_RES("1");
    free(msg2); // free the dynamically allocated memory
}
