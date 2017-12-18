#include "MotorController.h"

// Pin Definitions
int directionDigitalPin = 12;
int speedPWMPin = 23;
const int padPin = 2;
const int ledPin =  13;

// Animation Timings
long extensionTime = 15000;
long retractionTime = 15000;
long freezeTime = 30000;
long refreshTime = 30000;

//Config Constants
bool debugMode = true;

// State Variables
int padState = 0;

// Class Instantiations
MotorController motorController(directionDigitalPin, speedPWMPin, debugMode);

void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(padPin, INPUT);  
  analogWrite(speedPWMPin, 0); 
}

void loop() {
  padState = digitalRead(padPin);

  if (padState == HIGH) {         
    digitalWrite(ledPin, HIGH); 
    animate();
  } 
  else {
    digitalWrite(ledPin, LOW); 
    motorController.freeze();
  }
}

void animate() { 
  motorController.extend(); 
  digitalWrite(ledPin, HIGH); 
  delay(extensionTime);
  
  motorController.freeze(); 
  digitalWrite(ledPin, LOW); 
  delay(freezeTime);
  
  motorController.retract();
  digitalWrite(ledPin, HIGH); 
  delay(retractionTime);

  motorController.freeze();
  digitalWrite(ledPin, LOW); 
  delay(refreshTime);
}
