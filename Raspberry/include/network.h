/* definer les vaiables pour la communication avec le gestionnaire */


typedef enum message{
  READY, 
  DEMANDE_RES, 
  FREE_RES, 
  OBJ_OK,
  OBJ_DEPOT
} message_t;

#define MAXCAR  80
#define LOCALIP "127.0.0.1"
#define REMOTEIP "127.0.0.1"
#define REMOTEPORT 3000

#define CHECKERROR(var,val,msg)     if (var==val) {perror(msg); exit(1);}


#define SEND_READY() printf("function send ready")
#define SEND_DEMANDE_RES() printf("function send res demand")
#define SEND_FREE_RES() printf("function send free res")
#define SEND_OBJ_OK() printf("function send objet ok")
#define SEND_OBJ_DEPOT() printf("function send objet depot")



