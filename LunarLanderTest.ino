#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

Stepper stepper_x(stepsPerRevolution, 2,3,4,5);
Stepper stepper_y(stepsPerRevolution, 8,9,10,11);
Stepper stepper_z(stepsPerRevolution, 6,7,12,13);

#define JOY_X A1
#define JOY_Y A0

#define BUTTON_0 A2
#define BUTTON_1 A3
#define BUTTON_2 A4
#define BUTTON_3 A5
#define BUTTON_4 A6



void setup()
{
  Serial.begin(115200);

  // set the speed at 60 rpm:
  stepper_x.setSpeed(80);
  stepper_y.setSpeed(80);
  stepper_z.setSpeed(80);

  
  // put your setup code here, to run once:
  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);

  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
 
}

int prev_x = 0;
int prev_y = 0;
int prev_z = 0;

void loop()
{
  
  // put your main code here, to run repeatedly:
  int joyx = analogRead(JOY_X);
  int joyy = analogRead(JOY_Y);

  bool but0 = digitalRead(BUTTON_0);  
  bool but1 = digitalRead(BUTTON_1);  
  bool but2 = digitalRead(BUTTON_2);  
  bool but3 = digitalRead(BUTTON_3);  

//  Serial.print(joyx);
//  Serial.print("  ");
//  Serial.print(joyy);
//  Serial.print("  ");
//  Serial.print(but0);
//  Serial.print("  ");
//  Serial.print(but1);
//  Serial.print("  ");
//  Serial.print(but2);
//  Serial.print("  ");
//  Serial.print(but3);
//  Serial.println("  ");


 if(but0 == LOW)
 {
    stepper_x.step(joyy/2 - prev_x);
    prev_x = joyy/2;
 }
 else
 {
   stepper_y.step(joyy/2 - prev_y);
   prev_y = joyy/2;
 }
 
 stepper_z.step(joyx/2 - prev_z);
 prev_z = joyx/2;

}


//
//
//void loop22() {
//  // step one revolution  in one direction:
//  Serial.println("clockwise");
//  myStepper.step(stepsPerRevolution);
//  delay(500);
//
//  // step one revolution in the other direction:
//  Serial.println("counterclockwise");
//  myStepper.step(-stepsPerRevolution);
//  delay(500);
//}



