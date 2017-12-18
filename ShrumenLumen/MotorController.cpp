#include "Arduino.h"
#include "MotorController.h"

/*
   Stop:
    Analog - 0
   Extend:
    Analog - 255
    Digital - LOW
   Retract:
    Analog - 255
    Digital - HIGH
*/

MotorController::MotorController(int directionPin, int pwmPin, bool debugMode = false) {
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  _directionPin = directionPin;
  _pwmPin = pwmPin;
  _debugMode = debugMode;
}

void MotorController::freeze() {
  analogWrite(_pwmPin, 0);

  if(_debugMode) {
    Serial.println("Freeze");
  }
}

void MotorController::extend() {
  digitalWrite(_directionPin, LOW);
  analogWrite(_pwmPin, 255);
  
  if(_debugMode) {
    Serial.println("Extend");
  }
}

void MotorController::retract() {
  digitalWrite(_directionPin, HIGH);
  analogWrite(_pwmPin, 255);
  
  if(_debugMode) {
    Serial.println("Retract");
  }
}


