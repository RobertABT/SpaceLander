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
//A7 is C analog reader
Stepper stepper_a(stepsPerRevolution, 2, 3, 4, 5);
Stepper stepper_b(stepsPerRevolution, 8, 9, 10, 11);
Stepper stepper_c(stepsPerRevolution, 6, 7, 12, 13);

#define END_A A5
#define END_B A6
#define END_C A7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  stepper_a.setSpeed(40); //slips at 60
  stepper_b.setSpeed(40);
  stepper_c.setSpeed(40); //stepper c rotates opposite to the others

  pinMode(END_A, INPUT);
  pinMode(END_B, INPUT);
  pinMode(END_C, INPUT);
  Serial.println("Ready"); // print "Ready" once
}

int stepsa = 0;
int stepsb = 0;
int stepsc = 0;
bool initialAConf = false;
bool initialBConf = false;
bool initialCConf = false;


int endRead(char x) {
  int output = 5;
  switch (x) {
    case 'a':
      for (int i = 0; i < 20; i++) {
        output += analogRead(END_A);
        delay(5);
      }
      output = (output / 20); //low is under 100
      break;
    case 'b':
      for (int i = 0; i < 20; i++) {
        output += analogRead(END_B);
        delay(5);
      }
      output = (output / 20); //low is under 550
      break;
    case 'c':
      output = analogRead(END_C); //low is under 100
      break;
  }
  return output;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char input = Serial.read();
    switch (input) {
      case 'x':
        if (stepsa == 7680) {
          Serial.println("max a");
          break;
        }
        //Serial.println("down");
        stepper_a.step(stepsPerRevolution);
        stepsa += stepsPerRevolution;
        break;
      case 'y':
        if (stepsb == 7680) {
          Serial.println("max b");
          break;
        }
        stepper_b.step(stepsPerRevolution);
        stepsb += stepsPerRevolution;
        break;
      case 'z':
        if (stepsc == 7680) {
          Serial.println("max c");
          break;
        }
        stepper_c.step(-stepsPerRevolution);
        stepsc = stepsPerRevolution;
        break;
      case 'a':
        stepper_a.step(-100);
        stepsa -= 100;
        break;
      case 'b':
        stepper_b.step(-100);
        stepsb -= 100;
        break;
      case 'c':
        stepper_c.step(100);
        stepsc -= 100;
        break;
      case 'u':
        stepper_a.step(-(stepsPerRevolution / 2));
        stepper_b.step(-(stepsPerRevolution / 2));
        stepper_c.step((stepsPerRevolution / 2));
        delay(100);

        stepsa -= stepsPerRevolution;
        stepsb -= stepsPerRevolution;
        stepsc -= stepsPerRevolution;
        Serial.println('up');
        break;
      case 'q':
        delay(50);
        while (initialAConf == false) {
          int aRead = endRead('a');
          if (aRead < 150 ) {
            Serial.println("min a");
            initialAConf = true;
            stepsc = 0;
          }
          stepper_a.step(-10);
        }
        while (initialBConf == false) {
          int bRead = endRead('b');
          if (bRead < 550 ) {
            Serial.println("min b");
            initialBConf = true;
            stepsc = 0;
          }
          stepper_b.step(-10);
        }
        while (initialCConf == false) {
          int cRead = endRead('c');
          if (cRead < 100 ) {
            Serial.println("min c");
            initialCConf = true;
            stepsc = 0;
          }
          stepper_c.step(10);
        }
    }//end of switch statement
    //delay(100);
    Serial.println(stepsa);
    Serial.println(stepsb);
    Serial.println(stepsc);
    Serial.println('*');

  }
}

