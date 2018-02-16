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

void loop() {
  // put your main code here, to run repeatedly:
  int roughJoyX = analogRead(JOY_X);
  int roughJoyY = analogRead(JOY_Y);
  int maxTurns = 16; //(100cm of string/6cm travel per turn)
  //failed test of exponential moving average
  /*int diffX = roughJoyX-joyX;
  int diffY = roughJoyY-joyY;
  float snapX = snapCurve(diffX*snapMultiplier);
  float snapY = snapCurve(diffY*snapMultiplier);
  joyX = (roughJoyX-joyX)*snapX;
  joyY = (roughJoyY-joyY)*snapY;
  if ((valY+joyY) <= (maxTurns*512){
    valY+=joyY;
    stepper_Y.step(joyY);
  }
  */
  
  Serial.print("Rough Value of X: ");
  Serial.println(roughJoyX);
  Serial.print("Rough Value of Y: ");
  Serial.println(roughJoyY);
  /*Serial.print("Value of X: ");
  Serial.println(joyX);
  Serial.print("Value of Y: ");
  Serial.println(joyY);*/
  delay(1000);
  
}


/*// should take input and minimise random noise in it by creating a hyperbola (then removing asymptote, and inverting the hyperabola)
float snapCurve(float x){
  float y = (1-(1/(x+1)))*2; //multiplied by 2 so above a certain thresold it is guaranteed to move
  if(y>1){
    return 1;
  }else{
    return y;
  }
}
*/
