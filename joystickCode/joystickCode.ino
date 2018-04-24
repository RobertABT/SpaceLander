#include <Stepper.h>
//angle 5.625
//32:1 gearbox
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution
const int movement = 256;
const int gravityVal = 4;
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

//defining IR sensors
#define END_A A5
#define END_B A6
#define END_C A7
//defing joystick
#define JOY_X A1
#define JOY_Y A0
//defining buttons
#define BUTTON_0 A2
#define BUTTON_1 A3
#define BUTTON_2 A4

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

//initialise counters
int stepsa = 0;
int stepsb = 0;
int stepsc = 0;
bool initialAConf = false;
bool initialBConf = false;
bool initialCConf = false;

int joyX = 500; //resting is 520
int joyY = 500; //resting is 507
int result[2]={500,500}; //global as arrays cant be function results
int lastRead[2]={500,500};
int diff[2]={0,0}

void joyRead(){
  for(int i=0;i<10;i++){
    joyX += analogRead(JOY_X);
    joyY += analogRead(JOY_Y);
  }
  result[0] = joyX/10;
  result[1] = joyY/10;
  diff[0] = result[0] - lastRead[0]
  diff[1] = result[0] - lastRead[0]
  lastRead[0] = result[0]
  lastRead[0] = result[1]
}

int endRead(char x) { //returns IR sensor value
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
    joyRead();
    Serial.print(stepsa);
    Serial.println(",");
    Serial.print(stepsb);
    Serial.println(",");
    Serial.print(stepsc);
    Serial.println(",");
    Serial.print(diff[0]);
    Serial.println(",");
    Serial.print(diff[1]);
    Serial.println(",");
    Serial.println('*');
  }
  gravity();
}

void gravity(){
        stepper_a.step(gravityVal);
        stepper_b.step(gravityVal);
        stepper_c.step(-gravityVal);
        stepsa += (gravityVal);
        stepsb += (gravityVal);
        stepsc += (gravityVal);
        delay(100);
}
