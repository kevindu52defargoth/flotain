/* definer les vaiables pour la communication avec le gestionnaire */


typedef enum message{
  READY= '0', 
  DEMANDE_RES, 
  FREE_RES, 
  OBJ_OK,
  OBJ_DEPOT
} message_t;

// #define MAXCAR  80
// #define LOCALIP "127.0.0.1"
// #define REMOTEIP "127.0.0.1"
// #define REMOTEPORT 3000

#define IP_SRV	"0.0.0.0"
#define PORT_SRV	9007



#define CHECKERROR(var,val,msg)     if (var==val) {perror(msg); exit(1);}


#define SEND_READY() printf("function send ready"); char msg[10];sprintf(msg, "%d", READY);envoyer(&sockAppel, msg, NULL);
#define SEND_DEMANDE_RES(id_r) printf("function send res demand"); char *msg = preparer_message(DEMANDE_RES,id_r); envoyer(&sockAppel, msg, NULL);
#define SEND_FREE_RES(id_r) printf("function send free res"); char *msg = preparer_message(FREE_RES,id_r); envoyer(&sockAppel, msg, NULL);
#define SEND_OBJ_OK(id_obj) printf("function send objet ok"); char *msg = preparer_message(OBJ_OK,id_obj); envoyer(&sockAppel, msg, NULL);
#define SEND_OBJ_DEPOT() printf("function send objet depot"); char *msg = preparer_message(OBJ_DEPOT,id_obj); envoyer(&sockAppel, msg, NULL);



