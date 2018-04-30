#include <Stepper.h>
//angle 5.625
//32:1 gearbox
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution for your motor
const int movement = 256;
const int gravityVal = 4;
const int stringMax = 4096
//drum radius =14mm (given)
//drum circumference = 18.9mm=radius of 9.45mm (measured)
//Circumference=2*pi*r=59.37mm
//mm per step = 59.37mm/512=0.1159mm/step
//1metre/7680 steps = 0.1302mm/step
//A7 is C analog reader
Stepper stepper_a(stepsPerRevolution, 2, 3, 4, 5);
Stepper stepper_b(stepsPerRevolution, 8, 9, 10, 11);
Stepper stepper_c(stepsPerRevolution, 6, 7, 12, 13);

//these pins are used by the IR sensors
#define END_A A5
#define END_B A6
#define END_C A7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  stepper_a.setSpeed(40); //slips at 60
  stepper_b.setSpeed(40);
  stepper_c.setSpeed(40); //stepper c rotates opposite to the others
  
  //set IR sensors as inputs
  pinMode(END_A, INPUT);
  pinMode(END_B, INPUT);
  pinMode(END_C, INPUT);
  Serial.println("Ready"); // print "Ready" once
}
//initialises with current point as "top" point
//if you need to move above this use the no_endstops.ino 
int stepsa = 0;
int stepsb = 0;
int stepsc = 0;
bool initialAConf = false;
bool initialBConf = false;
bool initialCConf = false;


int endRead(char x) { //IR read for steppers A B and C, attempting to sense white tipex on black string
  int output = 5;
  switch (x) {
    case 'a': //due to inconsistencies on some of the sensors, reading and averaging the value is required
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
    char input = Serial.read(); //use character from serial as switch for movement
    switch (input) {
      case 'x':
        if (stepsa == stringMax) { //limits amount that steppers can move out, adjust for your display height
          Serial.println("max a");
          break;
        }
        stepper_a.step(movement); //move half a turn 
        stepsa += movement; //add half a turn to the step counter
        break;
      case 'y':
        if (stepsb == stringMax) {
          Serial.println("max b");
          break;
        }
        stepper_b.step(movement);
        stepsb += movement;
        break;
      case 'z':
        if (stepsc == stringMax) {
          Serial.println("max c");
          break;
        }
        stepper_c.step(-movement); //motor c turn in the opposite direction to the others
        stepsc += movement;
        break;
      case 'a':
        if (stepsa == 0) {//this software endstop prevents the string 
          Serial.println("min a");
          break;
        }
        stepper_a.step(-movement);
        stepsa -= movement;
        break;
      case 'b':
        if (stepsb == 0) {
          Serial.println("min b");
          break;
        }
        stepper_b.step(-movement);
        stepsb -= movement;
        break;
      case 'c':
        if (stepsc == 0) {
          Serial.print("min c");
          break;
        }
        stepper_c.step(movement);
        stepsc -= movement;
        break;
      case 'u':
        if (stepsa <= 0 || stepsb <= 0 || stepsc <= 0) {
          Serial.print("at the top");
          break;
        }
        stepper_a.step(-movement);
        stepper_b.step(-movement);
        stepper_c.step(movement);
        stepsa -= movement;
        stepsb -= movement;
        stepsc -= movement;
        break;
      case 'd':
        if (stepsa == stringMax || stepsb == stringMax || stepsc == stringMax) {
          Serial.print("at the bottom");
          break;
        }
        stepper_a.step(movement);
        stepper_b.step(movement);
        stepper_c.step(-movement);
        delay(100);
        stepsa += movement;
        stepsb += movement;
        stepsc += movement;
        break;
      case 'q': 
        //configuration case, which requires the IR sensors to be properly calibrated
        //if the IR sensors arent tripping reliably as white string goes past 
        //this method *should not* be run as it will over-tighten the system
        initialAConf == false;
        initialBConf == false;
        initialCConf == false;
        while (initialAConf == false) {
          int aRead = endRead('a');
          //Serial.println(aRead);
          if (aRead < 150 ) {
            Serial.println("min a");
            initialAConf = true;
            stepsc = 0;
          }
          stepper_a.step(-10);
        }
        while (initialBConf == false) {
          //Serial.print("Light Sensor: ");
          int bRead = endRead('b');
          //Serial.println(bRead);
          if (bRead < 550 ) {//a lot of bounce on this sensor
            Serial.println("min b");
            initialBConf = true;
            stepsc = 0;
          }
          stepper_b.step(-10);
        }
        while (initialCConf == false) {
          //Serial.print("Light Sensor: ");
          int cRead = endRead('c');
          //Serial.println(cRead);
          if (cRead < 100 ) {
            Serial.println("min c");
            initialCConf = true;
            stepsc = 0;
          }
          stepper_c.step(10);
        }
    }//end of switch statement
    //send step data in a format that the python program can read in
    Serial.print(stepsa);
    Serial.println(",");
    Serial.print(stepsb);
    Serial.println(",");
    Serial.print(stepsc);
    Serial.println(",");
    Serial.println('*');
  }
  gravity();
}

void gravity(){// calling this function moves all of the strings down a little bit
        stepper_a.step(gravityVal);
        stepper_b.step(gravityVal);
        stepper_c.step(-gravityVal);
        stepsa += (gravityVal);
        stepsb += (gravityVal);
        stepsc += (gravityVal);
        delay(100);
}
