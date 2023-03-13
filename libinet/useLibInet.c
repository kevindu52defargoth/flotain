/**
 *	\file		useLibInet.c
 *	\brief		Exemple d'utilisation de la librairie libinet.a
 *	\author		Samir El Khattabi
 *	\date		3 mars 2023
 *	\version	1.0
 */
#include <libgen.h>
#include "data.h"
/*
*****************************************************************************************
 *	\note		D E F I N I T I O N   DES   C O N S T A N T E S
 */
/**
 *	\def		IP_ANY
 *	\brief		Adresse IP par défaut du serveur
 */
#define IP_ANY		"0.0.0.0"
/**
 *	\def		PORT_SRV
 *	\brief		Numéro de port par défaut du serveur
 */
#define PORT_SRV	50000
/*
*****************************************************************************************
 *	\note		D E C L A R A T I O N   DES   V A R I A B L E S    G L O B A L E S
 */
/**
 *	\var		progName
 *	\brief		Nom de l'exécutable : libnet nécessite cette variable qui pointe sur argargv[0]
 */
char *progName;
/*
*****************************************************************************************
 *	\note		I M P L E M E N T A T I O N   DES   F O N C T I O N S
 */
/**
 *	\fn			void client (char *adrIP, int port)
 *	\brief		lance un client STREAM connecté à l'adresse applicative adrIP:port 
 *	\param 		adrIP : adresse IP du serveur à connecter
 *	\param 		port : port du serveur à connecter
 */
void client (char *adrIP, int port) {
	socket_t sockAppel;	// socket d'appel
	buffer_t buff;

	// Créer une connexion avec le serveur
	sockAppel = connecterClt2Srv (adrIP, port);
	// Dialoguer avec le serveur
	envoyer(&sockAppel,"Hi", NULL);
	recevoir(&sockAppel,buff, NULL);
	PAUSE("Fin du client");
	// Fermer la socket d'appel
	CHECK(shutdown(sockAppel.fd, SHUT_WR),"-- PB shutdown() --");
}
/**
 *	\fn				void serveur (char *adrIP, int port)
 *	\brief			lance un serveur STREAM en écoute sur l'adresse applicative adrIP:port
 *	\param 			adrIP : adresse IP du serveur à metrre en écoute
 *	\param 			port : port d'écoute
 */
void serveur (char *adrIP, int port) {
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
	// Fermer la socket d'écoute
	CHECK(close(sockEcoute.fd),"-- PB close() --");
}
/**
 *	\fn				int main(int argc, char** argv)
 *	\brief			Programme principal d'un serveur STREAM ou d'un client STREAM
 *					avec un protocole simple : envoi d'un message/réception d'un message
 *	\note			La compilation se fait avec -DCLIENT pour générer un client et -DSERVER pour un serveur
 *	\param 			argc : nombre d'aguments de laligne de commande
 *	\param 			argv : arguments de la commande en ligne
 *					Cas d'un serveur : adresse IP du serveur à metrre en écoute & port d'écoute
 *					Cas d'un client : adresse IP du serveur à connecter & port d'écoute du serveur
 */
int main(int argc, char** argv) {
	progName = argv[0];
#ifdef CLIENT
	if (argc<3) {
		fprintf(stderr,"usage : %s @IP port\n", basename(progName));
		 /*exit(-1);*/ 
		fprintf(stderr,"lancement du client [PID:%d] connecté à l'adresse applicative [%s:%d]\n", 
				getpid(), IP_ANY, PORT_SRV);
		client(IP_ANY, PORT_SRV);
	}
	else {
		fprintf(stderr,"lancement du client [PID:%d] connecté à l'adresse applicative [%s:%d]\n",
			getpid(), argv[1], atoi(argv[2]));
		client(argv[1], atoi(argv[2]));
	}
#endif

#ifdef SERVER
	if (argc<3) {
		fprintf(stderr, "usage: %s @IP port\n", basename(progName));
		/*exit(-1);*/
		fprintf(stderr,"lancement du serveur [PID:%d] sur l'adresse applicative [%s:%d]\n",
			getpid(), IP_ANY, PORT_SRV);
		serveur(IP_ANY, PORT_SRV);
	}
	else {
		fprintf(stderr,"lancement du client [PID:%d] sur l'adresse applicative [%s:%d]\n",
			getpid(), argv[1], atoi(argv[2]));
		serveur(argv[1], atoi(argv[2]));
	}
#endif	
	return 0;
}

