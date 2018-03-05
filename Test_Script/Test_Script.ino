#include <Stepper.h>
//angle 5.625
//32:1 gearbox
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution
// for your motor
//drum radius =14mm (given)
//drum circumference = 18.9mm=radius of 9.45mm (measured)
//Circumference=2*pi*r=59.37mm

Stepper stepper_x(stepsPerRevolution, 2,3,4,5);
Stepper stepper_y(stepsPerRevolution, 8,9,10,11);
Stepper stepper_z(stepsPerRevolution, 6,7,12,13);

int stepCount = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  stepper_x.setSpeed(40); //slips at 60
  stepper_y.setSpeed(40);
  stepper_z.setSpeed(40);
}
int turnx = 0;
int turny = 0;
int turnz = 0;
void loop() {
  // put your main code here, to run repeatedly:
  /*stepper_z.step(20);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount+=5;
  delay(1000);
  */
  if (Serial.available() > 0) {
    int input = Serial.read();
    switch(input){
      case 'x':
        turnx+=1;
        Serial.println("clockwise");
        stepper_x.step(stepsPerRevolution);
        delay(1000);
        Serial.println(turnx);
        break;
      case 'y':
        turny+=1;
        Serial.println("clockwise");
        stepper_y.step(stepsPerRevolution);
        delay(1000);
        Serial.println(turny);
        break;
      case 'z':
        turnz+=1;
        Serial.println("clockwise");
        stepper_z.step(stepsPerRevolution);
        delay(1000);
        Serial.println(turnz);
        break;
      case 'a':
        turnx-=1;
        Serial.println("anti-clockwise");
        stepper_x.step(-stepsPerRevolution);
        delay(1000);
        Serial.println(turnx);
        break;
      case 'b':
        turny-=1;
        Serial.println("anti-clockwise");
        stepper_y.step(-stepsPerRevolution);
        delay(1000);
        Serial.println(turny);
        break;
      case 'c':
        turnz-=1;
        Serial.println("anti-clockwise");
        stepper_z.step(-stepsPerRevolution);
        delay(1000);
        Serial.println(turnz);
        break;
      
    }
    

  /*// step one revolution in the other direction:
  Serial.println("counterclockwise");
  stepper_z.step(-stepsPerRevolution);
  delay(500);
  */
  }
}
