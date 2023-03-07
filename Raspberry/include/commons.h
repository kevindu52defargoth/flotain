/* macros de check */

#include <err.h>

#define CHECK(sts,msg)	if ((sts) != 0) err(EXIT_FAILURE,"\e[31m" msg "\e[0m")
#define CHECK_T(sts,msg)	if ((sts) != -1) err(EXIT_FAILURE,"\e[31m" msg "\e[0m")


/* macros d'affichage et de debug  */
#include "pthread.h"
#define PRINT(msg)  \
  pthread_mutex_lock(&screen);  \
  printf("%s\n", msg);  \
  pthread_mutex_unlock(&screen);
