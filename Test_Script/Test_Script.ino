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

Stepper stepper_x(stepsPerRevolution, 2,3,4,5);
Stepper stepper_y(stepsPerRevolution, 8,9,10,11);
Stepper stepper_z(stepsPerRevolution, 6,7,12,13);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  stepper_x.setSpeed(40); //slips at 60
  stepper_y.setSpeed(40);
  stepper_z.setSpeed(40);
}
int stepsx = 0;
int stepsy = 0;
int stepsz = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int input = Serial.read();
    switch(input){
      case 'x':
        if(stepsx==7680){
          Serial.println("max x");
          break;
        }
        Serial.println("clockwise");
        stepper_x.step(stepsPerRevolution);
        delay(100);
        stepsx+=stepsPerRevolution;
        Serial.println(stepsx);
        break;
      case 'y':
        if(stepsy==7680){
          Serial.println("max y");
          break;
        }
        Serial.println("clockwise");
        stepper_y.step(stepsPerRevolution);
        delay(100);
        stepsy+=stepsPerRevolution;
        Serial.println(stepsy);
        break;
      case 'z':
        if(stepsz==7680){
          Serial.println("max z");
          break;
        }
        Serial.println("clockwise");
        stepper_z.step(stepsPerRevolution);
        delay(100);
        stepsz+=stepsPerRevolution;
        Serial.println(stepsz);
        break;
      case 'a':
        if(stepsx==0){
          Serial.println("min x");
          break;
        }
        Serial.println("anti-clockwise");
        stepper_x.step(-stepsPerRevolution);
        delay(100);
        stepsx-=stepsPerRevolution;
        Serial.println(stepsx);
        break;
      case 'b':
        if(stepsy==0){
          Serial.println("min y");
          break;
        }
        Serial.println("anti-clockwise");
        stepper_y.step(-stepsPerRevolution);
        delay(100);
        stepsy-=stepsPerRevolution;
        Serial.println(stepsy);
        break;
      case 'c':
        if(stepsz==0){
          Serial.println("min z");
          break;
        }
        Serial.println("anti-clockwise");
        stepper_z.step(-stepsPerRevolution);
        delay(100);
        stepsz-=stepsPerRevolution;
        Serial.println(stepsz);
        break;
      
    }
  }
}
