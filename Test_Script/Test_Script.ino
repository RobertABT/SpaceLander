#include <Stepper.h>
//angle 5.625
//32:1 gearbox
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution
// for your motor
//drum radius =14mm (given)
//drum circumference = 18.9mm=radius of 9.45mm (measured)
//Circumference=2*pi*r=59.37mm
//mm per step = 59.37mm/512=0.1159mm/step
//1metre/7680 steps = 0.1302mm/step

Stepper stepper_a(stepsPerRevolution, 2,3,4,5);
Stepper stepper_b(stepsPerRevolution, 8,9,10,11);
Stepper stepper_c(stepsPerRevolution, 6,7,12,13);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  stepper_a.setSpeed(40); //slips at 60
  stepper_b.setSpeed(40);
  stepper_c.setSpeed(40);
}
int stepsa = 0;
int stepsb = 0;
int stepsc = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int input = Serial.read();
    switch(input){
      case 'x':
        if(stepsa==7680){
          Serial.println("max a");
          break;
        }
        Serial.println("clockwise");
        stepper_a.step(stepsPerRevolution);
        delay(100);
        stepsa+=stepsPerRevolution;
        Serial.println(stepsa);
        break;
      case 'y':
        if(stepsb==7680){
          Serial.println("max b");
          break;
        }
        Serial.println("clockwise");
        stepper_b.step(stepsPerRevolution);
        delay(100);
        stepsb+=stepsPerRevolution;
        Serial.println(stepsb);
        break;
      case 'z':
        if(stepsc==7680){
          Serial.println("max c");
          break;
        }
        Serial.println("clockwise");
        stepper_c.step(stepsPerRevolution);
        delay(100);
        stepsc+=stepsPerRevolution;
        Serial.println(stepsc);
        break;
      case 'a':
        if(stepsa==0){
          Serial.println("min a");
          break;
        }
        Serial.println("anti-clockwise");
        stepper_a.step(-stepsPerRevolution);
        delay(100);
        stepsa-=stepsPerRevolution;
        Serial.println(stepsa);
        break;
      case 'b':
        /*if(stepsb==0){
          Serial.println("min b");
          break;
        }*/
        Serial.println("anti-clockwise");
        stepper_b.step(-stepsPerRevolution);
        delay(100);
        stepsb-=stepsPerRevolution;
        Serial.println(stepsb);
        break;
      case 'c':
        if(stepsc==0){
          Serial.println("min c");
          break;
        }
        Serial.println("anti-clockwise");
        stepper_c.step(-stepsPerRevolution);
        delay(100);
        stepsc-=stepsPerRevolution;
        Serial.println(stepsc);
        break;
      
    }
  }
}
