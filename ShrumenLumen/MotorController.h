/*
  MotorController.h - Library for extension and retractions
  of the linear actuator used for Shrumen Lumen.
*/
#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

class MotorController {
  public:
    MotorController(int directionPin, int pwmPin);
    void extend();
    void retract();
    void freeze();
  private:
    int _directionPin;
    int _pwmPin;
};


#endif

