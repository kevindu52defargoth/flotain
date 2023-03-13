/* definer les vaiables pour la communication avec le gestionnaire */


typedef enum message{
  READY, DEMANDE_RES, FREE_RES, OBJ_OK,OBJ_DEPOT
} message_t;

#define MAXCAR  80
#define LOCALIP "127.0.0.1"
#define REMOTEIP "127.0.0.1"
#define REMOTEPORT 3000

#define CHECKERROR(var,val,msg)     if (var==val) {perror(msg); exit(1);}
