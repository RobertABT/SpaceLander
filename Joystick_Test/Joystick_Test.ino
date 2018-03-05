#include <Stepper.h>

float snapMultiplier = 0.07;
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution
// for your motor

Stepper stepper_x(stepsPerRevolution, 2,3,4,5);
Stepper stepper_y(stepsPerRevolution, 8,9,10,11);
Stepper stepper_z(stepsPerRevolution, 6,7,12,13);

#define JOY_X A1
#define JOY_Y A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // set the speed at 60 rpm:
  stepper_x.setSpeed(40); //slips at 60
  stepper_y.setSpeed(40);
  stepper_z.setSpeed(40);

  
  // put your setup code here, to run once:
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
}

//these can in future be set by reed switches
int valX = 0;
int valY = 0;
int valZ = 0;
int joyX = 500; //resting is 520
int joyY = 500; //resting is 507
int result[2]={0,0}; //global as arrays cant be function results
int lastRead[2]={0,0};

void loop() {
  // put your main code here, to run repeatedly:
  int maxTurns = 16; //(100cm of string/6cm travel per turn)
  //failed test of exponential moving average
  joyRead();
  Serial.print("Value of X: ");
  Serial.println(result[0]);
  Serial.print("Value of Y: ");
  Serial.println(result[1]);
  Serial.print("Diff X: ");
  Serial.println(result[0]-lastRead[0]);
  Serial.print("Diff Y: ");
  Serial.println(result[1]-lastRead[1]);
  lastRead[0] = result[0];
  lastRead[1] = result[1];
  delay(1000);
    
}

void joyRead(){
  int joyX=0;
  int joyY=0;
  for(int i=0;i<10;i++){
    joyX += analogRead(JOY_X);
    joyY += analogRead(JOY_Y);
    delay(20);
  }
  result[0] = joyX/10;
  result[1] = joyY/10;
}


