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
//A7 is z analog reader
Stepper stepper_a(stepsPerRevolution, 2, 3, 4, 5);
Stepper stepper_b(stepsPerRevolution, 8, 9, 10, 11);
Stepper stepper_c(stepsPerRevolution, 6, 7, 12, 13);

#define END_Z A7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  stepper_a.setSpeed(40); //slips at 60
  stepper_b.setSpeed(40);
  stepper_c.setSpeed(40); //stepper c rotates opposite to the others
  
  pinMode(END_Z, INPUT);
}

int stepsa = 0;
int stepsb = 0;
int stepsc = 0;
bool initialZConf = false;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int input = Serial.read();
    switch (input) {
      case 'x':
        if (stepsa == 7680) {
          Serial.println("max a");
          break;
        }
        Serial.println("down");
        /*stepper_a.step(-stepsPerRevolution);
        delay(100);
        stepsa -= stepsPerRevolution;*/
        stepper_a.step(-100);
        delay(100);
        stepsa -= 100;
        Serial.println(stepsa);
        break;
      case 'y':
        if (stepsb == 7680) {
          Serial.println("max b");
          break;
        }
        Serial.println("down");
        /*stepper_b.step(stepsPerRevolution);
        delay(100);
        stepsb += stepsPerRevolution;*/
        stepper_b.step(100);
        delay(100);
        stepsb += 100;
        Serial.println(stepsb);
        break;
      case 'z':
        if(stepsc==7680){
          Serial.println("max c");
          break;
        }
        Serial.println("down");
        stepper_c.step(-100);
        //stepper_c.step(stepsPerRevolution);
        delay(100);
        stepsc += 100;
        Serial.println(stepsc);
        break;
      case 'a':
        /*if (stepsa == 0) {
          Serial.println("min a");
          break;
        }*/
        Serial.println("up");
        stepper_a.step(100);
        delay(100);
        stepsa += 100;
        Serial.println(stepsa);
        break;
      case 'b':
        /*if (stepsb == 0) {
          Serial.println("min b");
          break;
        }*/
        Serial.println("up");
        /*stepper_b.step(-stepsPerRevolution);
        delay(100);
        stepsb -= stepsPerRevolution;*/
        stepper_b.step(-100);
        delay(100);
        stepsb -= 100;
        Serial.println(stepsb);
        break;
      case 'c':
        Serial.println(analogRead(END_Z));
        /*if (stepsc==0) {
          Serial.println("min c");
          initialZConf == true;
          stepsc = 0;
          break;
        }*/
        Serial.println("up");
        stepper_c.step(200);
        //stepper_c.step(-stepsPerRevolution);
        delay(100);
        stepsc -= 100;
        Serial.println(stepsc);
        break;
      case 'q':
        while (initialZConf == false) {
          Serial.print("Light Sensor: ");
          Serial.println(analogRead(END_Z));
          if (analogRead(END_Z) < 100 ) {
            Serial.println("min c");
            initialZConf == true;
            stepsc = 0;
            break;
          }
          stepper_c.step(10);
        }
    }//end of switch statement
  }
}
