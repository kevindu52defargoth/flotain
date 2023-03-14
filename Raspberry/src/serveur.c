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
#include <data.h>

int main(){
    socket_t sockEcoute;	// socket d'écoute de demande de connexion d'un client
	socket_t sockDial;		// socket de dialogue avec un client
	buffer_t buff;
	
	// sockEcoute est une variable externe
	sockEcoute = creerSocketEcoute(adrIP, port);
	while(1)	// daemon !
	{
		// Accepter une connexion
		sockDial = accepterClt(sockEcoute);
		// Dialoguer avec le client connecté
		recevoir(&sockDial,buff, NULL);
		envoyer(&sockDial,"Salut", NULL);
		// Fermer la socket d'écoute
		CHECK(close(sockDial.fd),"-- PB close() --");
    }
}