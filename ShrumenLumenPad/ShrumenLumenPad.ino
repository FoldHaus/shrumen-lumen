#include <Adafruit_NeoPixel.h>
#include <ArduinoLog.h>

#include "MotorController.h"

#define LOGLEVEL LOG_LEVEL_DEBUG

// Pin Definitions
const int DIRECTION_DIGIAL_PIN = 12;
const int SPEED_PWM_PIN = 23;
const int PAD_PIN = 2;
const int NEOPIXEL_DATA_PIN = 3;

// Config Constants
const bool MOTOR_CONTROLLER_DEBUG_MODE = false;
const int LED_STRIP_LENGTH = 95;

// Color Constants
const int GREEN = 1;
const int RED = 2;
const int BLUE = 3;

// Sequence Timings
const unsigned long extensionTime = 15000;
const unsigned long retractionTime = 15000;
const unsigned long freezeTime = 40000;
const unsigned long refreshTime = 15000;
const unsigned long sequenceTimings[4] = {
  extensionTime,
  extensionTime + freezeTime,
  extensionTime + freezeTime + retractionTime,
  extensionTime + freezeTime + retractionTime + refreshTime,
};

// Sequence State Variables
int padState = LOW;
bool inProgress = false;open .

unsigned long timer = 0;

// LED Animation State Variables
// (Async animations functions need state variable counters)
int currentSequence = GREEN;
unsigned long int rainbowCount = 0;
unsigned long int colorWipeTimer = 0;
unsigned long int colorWipePixelNum = 0;

// Class Instantiations
Adafruit_NeoPixel strip = Adafruit_NeoPixel(
                            LED_STRIP_LENGTH,
                            NEOPIXEL_DATA_PIN
                          );
MotorController motorController(
  DIRECTION_DIGIAL_PIN,
  SPEED_PWM_PIN,
  MOTOR_CONTROLLER_DEBUG_MODE
);

void printTimestamp(Print* _logOutput) {
  char c[12];
  int m = sprintf(c, "%10lu ", millis());
  _logOutput->print(c);
}

void printNewline(Print* _logOutput) {
  _logOutput->print('\n');
}

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(0));

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  //Start logging

  Log.notice(F(CR "******************************************" CR));
  Log.notice(  "***          SHRUMEN LUMEN - PAD                " CR);
  Log.notice(F("******************* ")); Log.notice("*********************** " CR);

  pinMode(PAD_PIN, INPUT);
  pinMode(PAD_PIN, INPUT_PULLDOWN);
  analogWrite(SPEED_PWM_PIN, 0);

  // Setup NeoPixel Strip & initialize all pixels to green'
  strip.begin();
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 255, 0);
    strip.show();
  }
}

void loop() {
  padState = digitalRead(PAD_PIN);
  Log.verbose("PAD STATE: %T || inProgress: %T"CR, padState, inProgress);

  if (padState == HIGH || inProgress) {
    if (!inProgress) {
      timer = millis();
    }
    // Start animation sequence
    animate();
  }
  else {
    motorController.freeze();
    timer = 0;
  }
  delay(76);
}

void animate() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;

  // Extension Phase
  if (delayTime <= sequenceTimings[0]) {
    // Caution - make sure timing is sufficient for linear actuator and light sequence
    lightStrip(RED);
    motorController.extend();
    Log.notice("SHRUMEN MOVEMENT: EXTENDING"CR);
  }
  // Freeze Phase
  else if (delayTime > sequenceTimings[0] && delayTime <= sequenceTimings[1]) {
    motorController.freeze();
    Log.notice("SHRUMEN MOVEMENT: FREEZE TOP"CR);
  }
  // Retraction Phase
  else if (delayTime > sequenceTimings[1] && delayTime <= sequenceTimings[2]) {
    motorController.retract();
    Log.notice("SHRUMEN MOVEMENT: RETRACTING"CR);
  }
  // Refresh Phase
  else if (delayTime > sequenceTimings[2] && delayTime <= sequenceTimings[3]) {
    // Caution - make sure timing is sufficient for linear actuator and light sequence
    motorController.freeze();
    lightStrip(GREEN);
    Log.notice("SHRUMEN MOVEMENT: FREEZE BOTTOM"CR);
  }
  // End of Sequence
  else {
    Log.notice("----------------------------------------- END OF SEQUENCE"CR);
    // Reset state variables
    colorWipeTimer = 0;
    colorWipePixelNum = 0;
    inProgress = false;
  }
}

void lightStrip(int lightSequence) {
  if (lightSequence != currentSequence) {
    colorWipePixelNum = 0;
  }

  switch (lightSequence) {
    case GREEN:
      currentSequence = GREEN;
      colorWipe(0, 180, 20);
      break;
    case RED:
      currentSequence = RED;
      colorWipe(244, 18, 2);
      break;
    case BLUE:
      currentSequence = BLUE;
      colorWipe(0, 0, 255);
      break;
    default:
      colorWipe(0, 180, 20);
      break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t r, uint32_t g, uint32_t b) {
  if (colorWipeTimer % 2 == 0) {
    strip.setPixelColor(
      colorWipePixelNum % strip.numPixels(), 
      r, 
      g,
      b
    );
    strip.show();

    colorWipePixelNum += 1;
  }

  colorWipeTimer += 1;
}
