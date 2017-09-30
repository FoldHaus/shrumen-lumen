#include "MotorController.h"

// Pin Definitions
int directionDigitalPin = PIN_A8;
int speedPWMPin = PIN_A9;

// Class Instantiations
MotorController motorController(directionDigitalPin, speedPWMPin);

void setup() {
  analogWrite(speedPWMPin, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  motorController.extend();
}
