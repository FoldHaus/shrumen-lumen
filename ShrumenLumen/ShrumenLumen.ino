#include "MotorController.h"

// Pin Definitions
int directionDigitalPin = 12;
int speedPWMPin = 23;
const int padPin = 2;
const int ledPin =  13;

// Other Variable Definitions
int padState = 0;

// Class Instantiations
MotorController motorController(directionDigitalPin, speedPWMPin);

void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(padPin, INPUT);  
  
  analogWrite(speedPWMPin, 0); 
}

void loop() {
  padState = digitalRead(padPin);

  if (padState == HIGH) {         
    digitalWrite(ledPin, HIGH); 
    motorController.extend(); 
    
  } 
  else {
    digitalWrite(ledPin, LOW); 
    motorController.retract();
  }
}
