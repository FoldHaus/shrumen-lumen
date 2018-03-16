#include <Adafruit_NeoPixel.h>
#include <ArduinoLog.h>

#include "MotorController.h"

#define LOGLEVEL LOG_LEVEL_SILENT

// Pin Definitions
const int DIRECTION_DIGIAL_PIN = 12;
const int SPEED_PWM_PIN = 23;
const int PAD_PIN = 2;
const int NEOPIXEL_DATA_PIN = 3;

// Config Constants
const bool MOTOR_CONTROLLER_DEBUG_MODE = false;
const int LED_STRIP_LENGTH = 95;
const unsigned long STARTUP_RETRACTION_PERIOD = 30000;

// Color Constants
const int GREEN_WIPE = 1;
const int RED_WIPE = 2;
const int BLUE_WIPE = 3;
const int GREEN_IMMEDIATE = 4;
const int RED_IMMEDIATE = 5;
const int BLUE_IMMEDIATE = 6;

// Sequence Timings
const unsigned long EXTENSION_TIME = 25000;
const unsigned long TOP_FREEZE_TIME = 15000;
const unsigned long RETRACTION_TIME = 25000;
const unsigned long BOTTOM_FREEZE_TIME = 15000;
const unsigned long EXTENSION_SEQUENCE_TIMINGS[2] = {
  EXTENSION_TIME,
  EXTENSION_TIME + TOP_FREEZE_TIME,
};
const unsigned long RETRACTION_SEQUENCE_TIMINGS[2] = {
  RETRACTION_TIME,
  RETRACTION_TIME + BOTTOM_FREEZE_TIME,
};

// Sequence State Variables,
int padState = LOW;
bool inProgress = false; // Tracks if a sequence is currently happening.
bool isExtended = false; // These are set after the corresponding sequence ends,
bool isRetracted = true; // and remain set until the following sequence are done.
unsigned long timer = 0; // Variable used for calculating asyc delays.

// Animation Constants
const int COLORWIPE_LOOPS_PER_INCREMENT = 2;

// LED Animation State Variables for Async Animations
int currentSequence = GREEN_WIPE;
unsigned long int rainbowCount = 0;
unsigned long int colorWipeTimer = 0;
unsigned long int colorWipePixelNum = 0;

// A delay is calculated to set our ColorWipe animation to require the full
// animationTimePeriod to complete. Since the ColorWipe sets a pixel every other
// interation of the loop, the math is as follows (for example):
// 78 ms/loop * 2 loops/NeoPixel * 95 NeoPixels = 15000ms.
unsigned long animationTimePeriod = TOP_FREEZE_TIME;
float programLoopDelay = animationTimePeriod / (COLORWIPE_LOOPS_PER_INCREMENT * LED_STRIP_LENGTH);

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

  strip.begin();

  // Setup NeoPixel Strip & initialize all pixels to blue.
  // This marks the initial reset period, during which the Shrumen return to a
  // retracted state.
  lightStrip(BLUE_IMMEDIATE);

  // Retract all of the Shrumen for 30 seconds (more than enough for full
  // retraction).
  motorController.retract();
  delay(STARTUP_RETRACTION_PERIOD);
  motorController.freeze();

  // Set all pixels to green once the installation is ready to go again.
  lightStrip(GREEN_IMMEDIATE);
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

  programLoopDelay = animationTimePeriod / (COLORWIPE_LOOPS_PER_INCREMENT * LED_STRIP_LENGTH);
  delay(programLoopDelay);
}

void extensionAnimation() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;
  // Extension Phase
  if (delayTime <= EXTENSION_SEQUENCE_TIMINGS[0]) {
    lightStrip(RED_IMMEDIATE);
    motorController.extend();
    Log.notice("SHRUMEN MOVEMENT: EXTENDING"CR);
  }
  // Freeze Phase
  else if (delayTime > EXTENSION_SEQUENCE_TIMINGS[0] && delayTime <= EXTENSION_SEQUENCE_TIMINGS[1]) {
    // Caution - make sure timing is sufficient for linear actuator and light sequence
    animationTimePeriod = TOP_FREEZE_TIME;
    lightStrip(GREEN_WIPE);
    motorController.freeze();
    Log.notice("SHRUMEN MOVEMENT: FREEZE TOP"CR);
  }
  // End of Sequence
  else {
    Log.notice("----------------------------------------- END OF EXTENSION SEQUENCE"CR);
    // Reset state variables
    inProgress = false;
    isExtended = true;
    isRetracted = false;
    resetColorWipe();
  }
}

void retractionAnimation() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;
  // Retraction Phase
  if (delayTime <= RETRACTION_SEQUENCE_TIMINGS[0]) {
    lightStrip(RED_IMMEDIATE);
    motorController.retract();
    Log.notice("SHRUMEN MOVEMENT: RETRACTING"CR);
  }
  // Refresh Phase
  else if (delayTime > RETRACTION_SEQUENCE_TIMINGS[0] && delayTime <= RETRACTION_SEQUENCE_TIMINGS[1]) {
    // Caution - make sure timing is sufficient for linear actuator and light sequence
    motorController.freeze();
    animationTimePeriod = BOTTOM_FREEZE_TIME;
    lightStrip(GREEN_WIPE);
    Log.notice("SHRUMEN MOVEMENT: FREEZE BOTTOM"CR);
  }
  // End of Sequence
  else {
    Log.notice("----------------------------------------- END OF RETRACTION SEQUENCE"CR);
    // Reset state variables
    inProgress = false;
    isRetracted = true;
    isExtended = false;
    resetColorWipe();
  }
}

void resetColorWipe() {
  colorWipeTimer = 0;
  colorWipePixelNum = 0;
}

void lightStrip(int lightSequence) {
  if (lightSequence != currentSequence) {
    colorWipePixelNum = 0;
  }

  switch (lightSequence) {
    case GREEN_WIPE:
      currentSequence = GREEN_WIPE;
      colorWipe(0, 180, 20);
      break;
    case RED_WIPE:
      currentSequence = RED_WIPE;
      colorWipe(244, 18, 2);
      break;
    case BLUE_WIPE:
      currentSequence = BLUE_WIPE;
      colorWipe(0, 0, 255);
      break;
    case GREEN_IMMEDIATE:
      if (currentSequence == GREEN_IMMEDIATE) {
        break;
      }
      currentSequence = GREEN_IMMEDIATE;
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 180, 20);
        strip.show();
      }
      break;
    case RED_IMMEDIATE:
      if (currentSequence == RED_IMMEDIATE) {
        break;
      }
      currentSequence = RED_IMMEDIATE;
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 244, 18, 2);
        strip.show();
      }
      break;
    case BLUE_IMMEDIATE:
      if (currentSequence == BLUE_IMMEDIATE) {
        break;
      }
      currentSequence = BLUE_IMMEDIATE;
      for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 255);
        strip.show();
      }
      break;
    default:
      colorWipe(0, 180, 20);
      break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t r, uint32_t g, uint32_t b) {
  if (colorWipeTimer % COLORWIPE_LOOPS_PER_INCREMENT == 0) {
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
