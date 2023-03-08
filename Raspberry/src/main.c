#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include <driver_robot.h>
#include <commons.h>
#include <main.h>

enum STATE {
  WAINTING_ZONE,
  AWAITING_ORDER,
  ON_THE_ROAD,
  WAITING_FOR_INTERSECTION,
  IN_ALLEY,
  PICKING_UP,
  UNLOADING,
};

int state;
pthread_mutex_t screen;
int main(int argc, char **argv){
  pthread_mutex_unlock(&screen);
  PRINT("hello world");
}
