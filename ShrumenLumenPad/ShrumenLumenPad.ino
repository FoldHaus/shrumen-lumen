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
const unsigned long extensionTime = 45000;
const unsigned long retractionTime = 15000;
const unsigned long freezeTime = 15000;
const unsigned long refreshTime = 15000;
const unsigned long extensionSequenceTimings[2] = {
  extensionTime,
  extensionTime + freezeTime,
};
const unsigned long retractionSequenceTimings[2] = {
  retractionTime,
  retractionTime + refreshTime,
};

// Sequence State Variables,
int padState = LOW;
// Tracks if a sequence (extension or retraction) is currently happening
bool inProgress = false;
// These are set after the corresponding sequence ends, and remain set until the
// following sequence is complete.
bool isExtended = false;
bool isRetracted = true;
// Variable used for calculating asyc delays
unsigned long timer = 0;

// LED Animation State Variables
// Async animations functions need state variable counters
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

  // Setup NeoPixel Strip & initialize all pixels to blue.
  // This marks the initial reset period, during which the Shrumen return to a
  // retracted state.
  strip.begin();
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 0, 255);
    strip.show();
  }

  // Retract all of the Shrumen for 30 seconds (more than enough for full
  // retraction).
  motorController.retract();
  delay(30000);
  motorController.freeze();

  // Set all pixels to green once the installation is ready to go again.
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
    if (isRetracted) {
      extensionAnimation();
    } else if (isExtended) {
      retractionAnimation();
    }
  }
  else {
    motorController.freeze();
    timer = 0;
  }

  // A delay of 76 is chosen to set our animations at a 15 second interval. For
  // ColorWipe, we need to light 95 NeoPixels across a 15 second interval. Since
  // the ColorWipe sets a pixel every other interation of the loop, the math is
  // as follows: 76 ms/loop * 2 loops/NeoPixel * 95 NeoPixels = 14400ms (roughly
  // 15 seconds.)
  delay(76);
}

void extensionAnimation() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;

  // Extension Phase
  if (delayTime <= extensionSequenceTimings[0]) {
    // Caution - make sure timing is sufficient for linear actuator and light sequence
    lightStrip(RED);
    motorController.extend();
    Log.notice("SHRUMEN MOVEMENT: EXTENDING"CR);
  }
  // Freeze Phase
  else if (delayTime > extensionSequenceTimings[0] && delayTime <= extensionSequenceTimings[1]) {
    lightStrip(GREEN);
    motorController.freeze();
    Log.notice("SHRUMEN MOVEMENT: FREEZE TOP"CR);
  }
  // End of Sequence
  else {
    Log.notice("----------------------------------------- END OF EXTENSION SEQUENCE"CR);
    // Reset state variables
    colorWipeTimer = 0;
    colorWipePixelNum = 0;
    inProgress = false;
    isExtended = true;
    isRetracted = false;
  }
}

void retractionAnimation() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;

  // Retraction Phase
  if (delayTime <= retractionSequenceTimings[0]) {
    lightStrip(RED);
    motorController.retract();
    Log.notice("SHRUMEN MOVEMENT: RETRACTING"CR);
  }
  // Refresh Phase
  else if (delayTime > retractionSequenceTimings[0] && delayTime <= retractionSequenceTimings[1]) {
    // Caution - make sure timing is sufficient for linear actuator and light sequence
    motorController.freeze();
    lightStrip(GREEN);
    Log.notice("SHRUMEN MOVEMENT: FREEZE BOTTOM"CR);
  }
  // End of Sequence
  else {
    Log.notice("----------------------------------------- END OF RETRACTION SEQUENCE"CR);
    // Reset state variables
    colorWipeTimer = 0;
    colorWipePixelNum = 0;
    inProgress = false;
    isRetracted = true;
    isExtended = false;
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
