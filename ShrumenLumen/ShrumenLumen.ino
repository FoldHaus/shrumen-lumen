#include <Adafruit_NeoPixel.h>

#include "MotorController.h"

// Pin Definitions
const int DIRECTION_DIGIAL_PIN = 12;
const int SPEED_PWM_PIN = 23;
const int PAD_PIN = 2;
const int NEOPIXEL_DATA_PIN = 3;

// Config Constants
const bool MOTOR_CONTROLLER_DEBUG_MODE = false;
const int LED_STRIP_LENGTH = 60;

// Color Constants
const int GREEN = 1;
const int RED = 2;

// Sequence Timings
const unsigned long extensionTime = 15000;
const unsigned long retractionTime = 15000;
const unsigned long freezeTime = 30000;
const unsigned long refreshTime = 30000;
const unsigned long sequenceTimings[4] = {
  extensionTime, 
  extensionTime + retractionTime, 
  extensionTime + retractionTime + freezeTime, 
  extensionTime + retractionTime + freezeTime + refreshTime
};

// Sequence State Variables
int padState = LOW;
bool inProgress = false;
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

void setup() {
  pinMode(PAD_PIN, INPUT);
  analogWrite(SPEED_PWM_PIN, 0);

  // Setup NeoPixel Strip & initialize all pixels to green'
  strip.begin();
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0, 255, 0);
    strip.show();
  }
}

void loop() {
  padState = digitalRead(PAD_PIN);

  if (padState == HIGH || inProgress) {
    if (!inProgress) {
      timer = millis();
    }

    // Start animation sequence    
    animate();
  }
  else {
    motorController.freeze();
    lightStrip(GREEN);
    timer = 0;
  }

  // Delay to regulate the LED animations
  delay(20);   
}

void animate() {
  inProgress = true;
  unsigned long delayTime = millis() - timer;

  // Extension Phase 
  if (delayTime <= sequenceTimings[0]) {
    motorController.extend();
  } 
  // Freeze Phase   
  else if (delayTime > sequenceTimings[0] && delayTime <= sequenceTimings[1]) {
    motorController.freeze();
  }
  // Retraction Phase   
  else if (delayTime > sequenceTimings[1] && delayTime <= sequenceTimings[2]) {
    motorController.retract();
  } 
  // Refresh Phase 
  else if (delayTime > sequenceTimings[2] && delayTime <= sequenceTimings[3]) {
    motorController.freeze();
  } 
  // End of Sequence 
  else {
    // Reset state variables
    inProgress = false;
    colorWipeTimer = 0;
    colorWipePixelNum = 0;
  }

  lightStrip(RED);
}

void lightStrip(int lightSequence) {
  if (lightSequence != currentSequence) {
    colorWipePixelNum = 0;
  }
  
  switch (lightSequence) {
    case GREEN:
      currentSequence = GREEN;
      colorWipe(0, 255, 0);
      break;
    case RED:
      currentSequence = RED;
      colorWipe(255, 15, 0);
      break;
    default:
      colorWipe(255, 0, 255);
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
