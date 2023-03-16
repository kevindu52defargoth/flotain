#include "stdlib.h"
#include "stdio.h"
#include <unistd.h>
#include <network.h>
#include <string.h>
#include <data.h>

#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}

int main(){
	socket_t sockEcoute;	// socket d'écoute de demande de connexion d'un client
	socket_t sockDial;		// socket de dialogue avec un client
	buffer_t buff;
	
	// sockEcoute est une variable externe
	sockEcoute = creerSocketEcoute("0.0.0.0", 9092);
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
