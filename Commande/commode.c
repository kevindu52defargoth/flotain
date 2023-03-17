#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#include <string.h>
#include <fcntl.h>
#include <termios.h>

#include "marvelmind.h"
#include "commode.h"
#include "matraque.h"
#include "serial_client.h"

#define Kp 0.06
#define Ki 0.05
#define Tech 0.1
#define Umax 3

int fd;

static sem_t *sem;
void semCallback(){
	sem_post(sem);
}

bool terminateProgram=false;

void CtrlHandler(int signum)
{
	close(fd);
	terminateProgram=true;
}

float oldx[2] = {0.1, 0.1};


char buffer[255];
char command_buf[10];


float u = 0;
float u_angle = 0;
float err = 5;
float err_angle = 0;

int main() {
	
	
	//Init
	struct MarvelmindHedge * hedge=createMarvelmindHedge ();
		if (hedge==NULL)
		{
			puts ("Error: Unable to create MarvelmindHedge");
			return -1;
		}
	const char * ttyFileName;
	ttyFileName = DEFAULT_TTY_FILENAME;
	hedge->ttyFileName=ttyFileName;
    hedge->verbose=true; // show errors and warnings
    hedge->anyInputPacketCallback= semCallback;
    startMarvelmindHedge (hedge);
	
	signal (SIGINT, CtrlHandler);
    signal (SIGQUIT, CtrlHandler);
	
	sem = sem_open(DATA_INPUT_SEMAPHORE, O_CREAT, 0777, 0);
	
	//serial init
	fd = serial_ouvert();
	
	
	//Commande
	
	int i = 0;
	
	float *data;
	//float xhat[2] = {0, 0};
	//float u[2] = {0.5, 0.5};
	//float P[2][2] = {{0, 0}, {0, 0}};
	float z[2] = {0, 0};

	float angle = 0;
	float deltaT = 0.17;
	
	printFusionIMUFromMarvelmindHedge(hedge, true);
	
	while (!terminateProgram){

		clock_t start_time = clock();

		
		//printf("[%f, %f]\n", data[0], data[1]);
		
		//fusion(xhat, P, u, z);	

		if (i%5 == 0){
			data = FusionIMU_data(hedge, false);

			z[0] = data[0];
			z[1] = data[1];
			commode(0.5, 0.5, z, true);
			i = 1;
		} else {
			float vect0[] = {0, 10};
			float vect1[] = {oldx[0]*10-z[0]*10, oldx[1]*10-z[1]*10};
			if (vect1[0] == vect1[1] == 0){
				vect1[0] = 0.01;
				vect1[1] = 0.01;
			}
			angle = angle + err_angle;

			z[0] = data[0] + deltaT*0.0031*(u-2.7/1.5*u_angle*sin(3.14/180*angle));
			z[1] = data[0] + deltaT*0.0031*(u+2.7/1.5*u_angle*cos(3.14/180*angle));
			commode(0.5, 0.5, z, true);
			i++;
		}
		printf("Odo/Marv = [%f, %f, %f] Marv = [%f, %f]\n", z[0], z[1], angle, data[0], data[1]);

		clock_t end_time = clock();
		double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

		//printf("Temps pris: %lf second\n", elapsed_time);
	}
	
	
	
	stopMarvelmindHedge (hedge);
    destroyMarvelmindHedge (hedge);

	close(fd);
	
	return 0;
}


float constrain(float U, float maxi, float mini) {
	return fminf(fmaxf(U, mini), maxi);
}


float pid_dist(float last_U, float old_err_dist, float new_err_dist) {
	float newU;
	newU = last_U + Kp*10* (new_err_dist - old_err_dist) + Ki*50*Tech*old_err_dist;
	newU = constrain(newU, Umax, -Umax);
	return newU;
}

float pid_angle(float last_U, float old_err_dist, float new_err_dist) {
	float newU;
	newU = last_U + Kp/5* (new_err_dist - old_err_dist) + Ki/3*Tech*old_err_dist;
	newU = constrain(newU, Umax, -Umax);
	return newU;
}

float get_angle(float vect1[2], float vect2[2]){
	float angle;
	float sign;
	angle = 180/3.14*acos((vect1[0]*vect2[0] + vect1[1]*vect2[1])/(sqrtf(vect1[0]*vect1[0] + vect1[1]*vect1[1])*sqrtf(vect2[0]*vect2[0] + vect2[1]*vect2[1])));
	sign = vect1[0]*vect2[1]-vect1[1]*vect2[0];
	if (sign > 0)
		return angle;
	return -angle;
}




void commode(float x, float y, float * data, bool turn) {
	float r;
	float new_err_angle;
	
	r = sqrtf((x-data[0])*(x-data[0]) + (y-data[1])*(y-data[1]));
	if (r < 0.2) {
		//send semaph
		printf("Arrivé à la case\n");
		send_tensions(0, 0, fd);
	} else {
	
		u = pid_dist(u, err, r);
		err = r;

		if (turn) {
			float r2;
			r2 = sqrtf((oldx[0]-data[0])*(oldx[0]-data[0]) + (oldx[1]-data[1])*(oldx[1]-data[1]));

			if (r2 < 0.1) {
				new_err_angle = 0;
				u_angle = u_angle*0.3;
			} else {
				float vect2[] = {data[0]*10-oldx[0]*10, data[1]*10-oldx[1]*10};
				float vect3[] = {x*10-data[0]*10, y*10-data[1]*10};
				new_err_angle = get_angle(vect3, vect2);
				u_angle = pid_angle(u_angle, err_angle, new_err_angle);
			}


			err_angle = new_err_angle;



			//printf("angle = %f\n", new_err_angle);



			oldx[0] = data[0];
			oldx[1] = data[1];
			//printf("tension1 = %f\n", u_angle);


		}
		//printf("tensionGauche = %f\n", u-u_angle);
		//send u1 = u + u_angle
		//printf("tensionDroite = %f\n", +u-u_angle);
		//send u2 = u - u_angle
		//send_tensions(u+u_angle, u-u_angle, fd);
		send_tensions(u-u_angle, -u-u_angle, fd);
	}
}
