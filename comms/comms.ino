#include <Stepper.h>
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution

Stepper stepper_a(stepsPerRevolution, 2, 3, 4, 5);

#define END_A A5

void setup() {
  Serial.begin(115200); // set the baud rate
  stepper_a.setSpeed(40); //slips at 60
  Serial.println("Ready"); // print "Ready" once
}


void loop() {
  char inByte = ' ';
  if (Serial.available()) { // only send data back if data has been sent
    char inByte = Serial.read(); // read the incoming data
    if(inByte=='x'){
      stepper_a.step(50);
    }
    Serial.print("This is a test: ");
    Serial.println("355"); // send the data back in a new line so that it is not all one long line
  }
  delay(100); // delay for 1/10 of a second
}
