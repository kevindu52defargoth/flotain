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



#define Kp 0.06
#define Ki 0.05
#define Tech 0.1

#define Usat 9

float lastError=0;
float lastU=0;



unsigned long lastTick = 0;
#define PERIODE 100 //en millisecondes

char command[3];


void setup() {
  // put your setup code here, to run once:
  InitMotors();
  delay(3);
  Serial.begin(9600);
  // turn(1080, -1);
}

void loop() {
  //tickHorloge();
  if (Serial.available() > 0 ){
   // String data = Serial.readStringUntil('\n');

   int data = Serial.read();
   Serial.print("You sent me: ");
   Serial.println(data);
   setCommand(data);
  }
  

  

  delay(1000);
}


// void addMessage(str data){
//   String data = Serial.readStringUntil('\n');
//   Serial.print("You sent me: ");
//   Serial.println(data);

// }

void setCommand(int data){
  
  // msg_acept = true;
  Serial.println(data);
  
  switch(data){
    case 0:
      Serial.println("Derriere");
      break;
    case 1:     // turn left function 
      Serial.println("Turn");
      turn(1080,-1);
      break;
    case 2:     // add the forward function
      Serial.println("Forward");
      break;
    case 3:     // add the turn right function
      Serial.println("Droite");
      break;
    case 4:     // to send data to the pi; in this case, we're sending the information from the ultrasonic sensor
      send_distance();

    case 6 ... 255:     // turn + angle 
      int angle, sign;
      if (data > 126){
        
        angle = treat_angle(data);
        sign = -1;
      }
      else 
        angle = data;
        sign = 1;
      // turn(angle);

      Serial.println("turn + angle");
      
      break;
    default:
      Serial.println("Rien");
      break;
  }

}

int treat_angle(int angle){
 
  angle -= 180;
  return angle; 
}
void send_distance(){
  char myString[10];
  Serial.println(dtostrf(distance_capteur(), 6, 2, myString));
}

void tickHorloge(){
  if(lastTick+PERIODE<millis()){
    lastTick=millis();

    //executer du code ici
    updatePID(200);   
  }
}

void InitMotors()
{
  pinMode(PORT1_BI1,OUTPUT);
  pinMode(PORT1_BI2,OUTPUT);
  pinMode(PORT1_PWM,OUTPUT);

  pinMode(PORT2_BI1,OUTPUT);
  pinMode(PORT2_BI2,OUTPUT);
  pinMode(PORT2_PWM,OUTPUT);
}


void setMotor(int motorSpeed,int sens, int MOT_BI1,int MOT_BI2,int MOT_PWMB){
  digitalWrite(MOT_PWMB, LOW); //pause
  delayMicroseconds(3);
  
  digitalWrite(MOT_BI1, sens); //set sens
  digitalWrite(MOT_BI2, (1-sens)); 

  delayMicroseconds(3);
  analogWrite(MOT_PWMB, motorSpeed);
}

void setMotorByTension(float u, int MOT_BI1,int MOT_BI2,int MOT_PWMB){
  int sens=0;
  float signe;
  int motorSpeed;
  u=constrain(u, -Usat, Usat);
  if(u>=0){
    sens=1;
    signe=1.0;
  }else{
    sens=0;
    signe=-1.0;
  }
  
  motorSpeed=(int)(signe*255.0*u/12.0);
  setMotor(motorSpeed, sens, MOT_BI1,MOT_BI2, MOT_PWMB);
}

void setMotor1ByTension(float u){
  setMotorByTension(u, PORT1_BI1, PORT1_BI2, PORT1_PWM);
}

void setMotor2ByTension(float u){
  setMotorByTension(u, PORT2_BI1, PORT2_BI2, PORT2_PWM);
}

float distance_capteur(){
  pinMode(A12,OUTPUT);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  pinMode(A12,INPUT);
  long measure = pulseIn(echo, HIGH, 500000);

  return measure * 343.0 / (2.0 * 1000.0);
}

void updatePID(float command){ //command en mm
  float newError = command - distance_capteur();
  
  float newU = lastU + Kp*(newError-lastError)+Ki*Tech*lastError;
  newU=constrain(newU, -Usat, Usat);
  //Serial.println((String)(newU) + " V");
  
  Serial.println((String)(newError) + " mm  ___ "+(String)(newU) + " V");
  
  setMotor1ByTension(newU);
  setMotor2ByTension(-newU);
  
  lastError=newError;
  lastU=newU;
}

void turn() {
  digitalWrite(PORT1_BI1,0);
  digitalWrite(PORT1_BI2,1);
  analogWrite(PORT1_PWM,100);
  delay(3000);
  digitalWrite(PORT1_BI1,1);
  digitalWrite(PORT1_BI2,0);
  delay(3000);
  analogWrite(PORT1_PWM,0);
  delay(3000);
}

void test_capteur(){
  int startTime=micros();
  pinMode(A12,OUTPUT);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  
  
  pinMode(A12,INPUT);
  long measure = pulseIn(echo, HIGH, 500000);

  float distance = measure * 343.0 / (2.0 * 1000.0);

  int endTime=micros();
  
  Serial.println((String)(distance) + " mm");
  //Serial.println((String)(endTime-startTime) + " µs");
  delay(1000);
}
