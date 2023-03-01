#define PORT1_NE1 31
#define PORT1_NE2 18

#define PORT2_NE1 38
#define PORT2_NE2 19

#define PORT1_PWM 12
#define PORT1_BI1 35
#define PORT1_BI2 34

#define PORT2_PWM 8
#define PORT2_BI1 36
#define PORT2_BI2 37

#define trigger A12
#define echo A12

#define MAXPWM 190


#define Usat 4


void turn(float degree, float sens) {
  setMotor1ByTension(sens*3);
  setMotor2ByTension(-sens*3);
  delay(4*degree/90);
  setMotor1ByTension(0);
  setMotor2ByTension(0);
}
