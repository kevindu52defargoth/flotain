

typedef enum message{
  READY='0', 
  DEMANDE_RES='1', 
  FREE_RES='2', 
  OBJ_OK='3',
  OBJ_DEPOT='4'
} message_t;

// #define MAXCAR  80
// #define LOCALIP "127.0.0.1"
// #define REMOTEIP "127.0.0.1"
// #define REMOTEPORT 3000

#define IP_SRV	"0.0.0.0"
#define PORT_SRV	8005



#define CHECKERROR(var,val,msg)     if (var==val) {perror(msg); exit(1);}


#define SEND_READY() printf("function send ready"END_OBJ("1.1.2");); char msg[10];sprintf(msg, "%d", READY);envoyer(&sockAppel, msg, NULL);
#define SEND_DEMANDE_RES(id_r) printf("function send res demand"); char msg[10]; msg = preparer_message(DEMANDE_RES,id_r); envoyer(&sockAppel, msg, NULL);
#define SEND_FREE_RES(id_r) printf("function send free res"); char *msg = preparer_message(FREE_RES,id_r); envoyer(&sockAppel, msg, NULL);
#define SEND_OBJ_OK(id_obj) printf("function send objet ok"); char *msg = preparer_message(OBJ_OK,id_obj); envoyer(&sockAppel, msg, NULL);
#define SEND_OBJ_DEPOT() printf("function send objet depot"); char *msg = preparer_message(OBJ_DEPOT,id_obj); envoyer(&sockAppel, msg, NULL);


#define SEND_OBJ(id_obj) printf("function send OBJ %s\n",id_obj);
#define SEND_RES(id_r) printf("function send res %s\n",id_r); prendre_ressource(atoi(id_r), sockDial);
#define FREE_RES(id_r) printf("function FREE res %s\n",id_r); liberer_ressource(atoi(id_r), sockDial);
#define STAT_OBJ_OK(id_obj) printf("Objet %s was catched \n",id_obj);
#define STAT_OBJ_DEPOT(id_obj) printf("Objet %s was released for delivery \n",id_obj);
